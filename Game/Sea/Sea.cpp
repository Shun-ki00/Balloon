#include "pch.h"
#include "Game/Sea/Sea.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"


Sea::Sea()
	:
	m_inputLayout{},
	m_vertexShader{},
	m_hullShader{},
	m_domainShader{},
	m_pixelShader{},
	m_texture{},
	m_blendState{},
	m_depthStencilState{},
	m_rasterizerState{}
{
	m_commonResources = CommonResources::GetInstance();
	m_resources       = Resources::GetInstance();
	m_commonStates    = CommonResources::GetInstance()->GetCommonStates();
	m_context         = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	m_device          = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
}


void Sea::Initialize()
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	m_states = std::make_unique<DirectX::DX11::CommonStates>(device);

	// �V�F�[�_�[���擾����
	m_vertexShader = m_resources->GetShaderResources()->GetVertexShader(VS_ID::Sea_VS);
	m_hullShader   = m_resources->GetShaderResources()->GetHullShader(HS_ID::Sea_HS);
	m_domainShader = m_resources->GetShaderResources()->GetDomainShader(DS_ID::Sea_DS);
	m_pixelShader  = m_resources->GetShaderResources()->GetPixelShader(PS_ID::Sea_PS);
	// �C���v�b�g���C�A�E�g���擾
	m_inputLayout = m_resources->GetShaderResources()->GetSeaInputLayout();

	// �e�N�X�`�����擾����
	m_texture = m_resources->GetTextureResources()->GetTexture(TextureKeyID::Sea);
	m_NormalTexture = m_resources->GetTextureResources()->GetTexture(TextureKeyID::Wood);
	m_CubeTexture = m_resources->GetTextureResources()->GetTexture(TextureKeyID::CubeMap);


	this->CreateConstantBuffer();

	// ���_�f�[�^���`�i4�̐���_�j
	const float SIZE = 30.0f;

	const int GRID_X = 8;
	const int GRID_Z = 4;
	const int VERTEX_COUNT = GRID_X * GRID_Z;

	DirectX::VertexPositionTexture vertex[VERTEX_COUNT];

	for (int z = 0; z < GRID_Z; ++z)
	{
		for (int x = 0; x < GRID_X; ++x)
		{
			int index = z * GRID_X + x;
			float fx = -SIZE + (2 * SIZE) * (float)x / (GRID_X - 1);
			float fz = SIZE - (2 * SIZE) * (float)z / (GRID_Z - 1);
			vertex[index] = {
				DirectX::XMFLOAT3(fx, 0.0f, fz),
				DirectX::XMFLOAT2((float)x / (GRID_X - 1), (float)z / (GRID_Z - 1))
			};
		}
	}


	// ���_�o�b�t�@�̐���
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(DirectX::VertexPositionTexture) * _countof(vertex); // ���_�f�[�^�S�̂̃T�C�Y
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;

	// ���_�f�[�^�̏�����
	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = vertex;

	device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);

	// �u�����h�X�e�[�g�̍쐬
	CreateBlendState(device);
	// �[�x�X�e���V���X�e�[�g�̍쐬
	CreateDepthStencilState(device);
	// ���X�^���C�U�[�X�e�[�g�̍쐬
	CreateRasterizerState(device);

	// �ו��x
	m_index = 1.0f;
	// �^�C��������
	m_time = 0.0f;
}

void Sea::Render()
{
	// �^�C�}�[�̍X�V
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();
	m_time += elapsedTime;
	// �ו��x�ݒ�
	m_index = 40.0f;

	// ���[���h�s��쐬
	DirectX::SimpleMath::Matrix world = 
		DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3::Down * 20);

	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B
	ConstBuffer cbuff;
	cbuff.matView = m_commonResources->GetViewMatrix().Transpose();
	cbuff.matProj = m_commonResources->GetProjectionMatrix().Transpose();
	cbuff.matWorld = world.Transpose();
	cbuff.TessellationFactor = DirectX::SimpleMath::Vector4(m_index, m_time, 2.0f, 0.0f);

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	m_context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// ���̓��C�A�E�g��ݒ�
	m_context->IASetInputLayout(m_inputLayout);

	// ���_�o�b�t�@��ݒ�
	ID3D11Buffer* buffers[] = { m_vertexBuffer.Get() };
	UINT stride[] = { sizeof(DirectX::VertexPositionTexture) };
	UINT offset[] = { 0 };
	m_context->IASetVertexBuffers(0, 1, buffers, stride, offset);

	//	�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[2] = { m_constantBuffer.Get() , m_waveConstantBuffer.Get()};
	// �X���b�g1����3�Ɉꊇ�o�C���h
	m_context->VSSetConstantBuffers(0, 2, cb);
	m_context->HSSetConstantBuffers(0, 2, cb);
	m_context->DSSetConstantBuffers(0, 2, cb);
	m_context->PSSetConstantBuffers(0, 2, cb);

	// �T���v���[�X�e�[�g���s�N�Z���V�F�[�_�[�ɐݒ�
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	m_context->PSSetSamplers(0, 1, sampler);

	// �u�����h�X�e�[�g��ݒ� (�������`��p)
	//m_context->OMSetBlendState(m_blendState.Get(), nullptr, 0xFFFFFFFF);

	// �v���~�e�B�u�g�|���W�[��ݒ�
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST);

	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	m_context->OMSetDepthStencilState(m_states->DepthDefault(), 0);
	// ���X�^���C�U�[�X�e�[�g�̐ݒ�
	m_context->RSSetState(m_rasterizerState.Get());


	//	�V�F�[�_���Z�b�g����
	m_context->VSSetShader(m_vertexShader, nullptr, 0);
	m_context->HSSetShader(m_hullShader, nullptr, 0);
	m_context->DSSetShader(m_domainShader, nullptr, 0);
	m_context->PSSetShader(m_pixelShader, nullptr, 0);

	// �e�N�X�`���̐ݒ�
	std::vector<ID3D11ShaderResourceView*> tex = {
		m_texture,
		m_NormalTexture,
		m_CubeTexture,
	};

	m_context->VSSetShaderResources(0, (UINT)tex.size(), tex.data());
	m_context->PSSetShaderResources(0, (UINT)tex.size(), tex.data());

	// �`��R�[��
	m_context->Draw(32, 0);

	//	�V�F�[�_�̓o�^���������Ă���
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->HSSetShader(nullptr, nullptr, 0);
	m_context->DSSetShader(nullptr, nullptr, 0);
	m_context->PSSetShader(nullptr, nullptr, 0);

	// �e�N�X�`�����\�[�X�����
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	m_context->PSSetShaderResources(0, 1, nullsrv);
}

void Sea::CreateConstantBuffer()
{
	//	�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(ConstBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	m_device->CreateBuffer(&desc, nullptr, m_constantBuffer.ReleaseAndGetAddressOf());

	WaveParams waveParams =
	{
		// ��g�i���U���E�����j
		1.0f, -0.85f,  0.55f, 1.8f,   // active, dirX, dirZ, amplitude
		12.0f, 2.5f, 0.75f, 0.0f,     // waveLength, speed, qRatio, pad

		// ���g�i�΍R�����E���U���j
		1.0f, 0.6f, -0.6f, 0.9f,
		6.0f, 2.0f, 0.55f, 0.0f,

		// �הg�i�s�����g�j
		1.0f, 0.3f, -1.0f, 0.45f,
		2.2f, 1.8f, 0.65f, 0.0f
	};


	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(WaveParams);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	m_device->CreateBuffer(&desc, nullptr, &m_waveConstantBuffer);

	m_context->UpdateSubresource(m_waveConstantBuffer.Get(), 0, nullptr, &waveParams, 0, 0);

}



/// <summary>
/// �u�����h�X�e�[�g�̍쐬
/// </summary>
/// <param name="device">�f�o�C�X</param>
void Sea::CreateBlendState(ID3D11Device1* device)
{
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = FALSE;  // �J�o���b�W���A���t�@�Ɋ�Â��ėL��������
	blendDesc.IndependentBlendEnable = FALSE; // �����̃����_�[�^�[�Q�b�g��Ɨ����Đݒ肷��

	D3D11_RENDER_TARGET_BLEND_DESC rtBlendDesc = {};
	rtBlendDesc.BlendEnable = TRUE;              // �u�����h��L����
	rtBlendDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;        // �\�[�X�̃A���t�@
	rtBlendDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;    // �t�A���t�@
	rtBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;           // ���Z�u�����h
	rtBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;              // �A���t�@�l�̃\�[�X
	rtBlendDesc.DestBlendAlpha = D3D11_BLEND_ZERO;             // �A���t�@�l�̃f�X�e�B�l�[�V����
	rtBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;           // �A���t�@�l�̉��Z
	rtBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // RGBA�S�Ă�L��

	blendDesc.RenderTarget[0] = rtBlendDesc;

	// �J�X�^���u�����h�X�e�[�g���쐬

	device->CreateBlendState(&blendDesc, &m_blendState);
}

/// <summary>
/// �[�x�X�e���V���X�e�[�g�̍쐬
/// </summary>
/// <param name="device">�f�o�C�X</param>
void Sea::CreateDepthStencilState(ID3D11Device1* device)
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = TRUE;                          // �[�x�e�X�g��L����
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // �[�x�o�b�t�@�̏������݂�L����
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;      // �[�x�e�X�g���� (�������ꍇ�̂ݕ`��)
	depthStencilDesc.StencilEnable = FALSE;                       // �X�e���V���e�X�g�𖳌���

	// �[�x�X�e���V���X�e�[�g���쐬
	device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
}

/// <summary>
/// ���X�^���C�U�[�X�e�[�g�̍쐬
/// </summary>
/// <param name="device">�f�o�C�X</param>
void Sea::CreateRasterizerState(ID3D11Device1* device)
{
	D3D11_RASTERIZER_DESC rasterDesc = {};
	rasterDesc.FillMode = D3D11_FILL_WIREFRAME;      // �h��Ԃ� (�܂��� D3D11_FILL_WIREFRAME)D3D11_FILL_SOLID
	rasterDesc.CullMode = D3D11_CULL_FRONT;       // �J�����O�Ȃ� (�܂��� D3D11_CULL_FRONT / D3D11_CULL_BACK)
	rasterDesc.FrontCounterClockwise = FALSE;    // ���v���̒��_������\�ʂƂ��ĔF��
	rasterDesc.DepthClipEnable = TRUE;           // �[�x�N���b�s���O��L����
	// ���X�^���C�U�[�X�e�[�g�̍쐬
	device->CreateRasterizerState(&rasterDesc, &m_rasterizerState);
}