#include "pch.h"
#include "Game/Sea/Sea.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include "Game/Buffers/ConstantBuffer.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Sea::Sea()
	:
	m_inputLayout{},
	m_vertexShader{},
	m_hullShader{},
	m_domainShader{},
	m_pixelShader{},
	m_texture{},
	m_color{}
{
	m_commonResources = CommonResources::GetInstance();
	m_resources       = Resources::GetInstance();
	m_commonStates    = CommonResources::GetInstance()->GetCommonStates();
	m_context         = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	m_device          = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
}

/// <summary>
/// ����������
/// </summary>
void Sea::Initialize()
{
	// �V�F�[�_�[���擾����
	m_vertexShader = m_resources->GetShaderResources()->GetVertexShader(VS_ID::Sea_VS);
	m_hullShader   = m_resources->GetShaderResources()->GetHullShader(HS_ID::Sea_HS);
	m_domainShader = m_resources->GetShaderResources()->GetDomainShader(DS_ID::Sea_DS);
	m_pixelShader  = m_resources->GetShaderResources()->GetPixelShader(PS_ID::Sea_PS);
	// �C���v�b�g���C�A�E�g���擾
	m_inputLayout = m_resources->GetShaderResources()->GetSeaInputLayout();

	// �e�N�X�`�����擾����
	m_texture = m_resources->GetTextureResources()->GetTexture(TextureKeyID::Sea);

	// ���ԑ���p�̃G�C���A�X
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = Clock::time_point;
	using Duration = std::chrono::duration<float>;

	// --- �v�Z�J�n ---
	TimePoint startTime = Clock::now();

	// �V���h�E�}�b�v�p�̃T���v���[���쐬����
	D3D11_SAMPLER_DESC samplerDesc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
	samplerDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS;
	DX::ThrowIfFailed(
		m_device->CreateSamplerState(&samplerDesc, m_shadowMapSampler.ReleaseAndGetAddressOf())
	);

	// �萔�o�b�t�@�I�u�W�F�N�g�̍쐬
	m_constantLightBuffer = std::make_unique<ConstantBuffer<DirectionalLightBuffer>>();
	m_constantLightBuffer->Initialize(m_device);

	// ���_�o�b�t�@�̍쐬
	this->CreateVertexBuffer();
	// �C���X�^���X�f�[�^�̍쐬
	this->CreateInstanceData();
	// �萔�o�b�t�@�̍쐬
	this->CreateConstBuffer();


	// --- �v�Z�I�� ---
	TimePoint endTime = Clock::now();
	Duration elapsed = endTime - startTime;

	// �v�Z���Ԃ��擾
	m_time = elapsed.count();

	// �F��ݒ�
	m_color = DirectX::SimpleMath::Vector4::One;

	// �^�C��������
	m_time = 0.0f;
}

/// <summary>
/// �`�揈��
/// </summary>
void Sea::Render(ID3D11ShaderResourceView* shadowMap)
{
	// �^�C�}�[�̍X�V
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();
	m_time += elapsedTime;

	// ���[���h�s��쐬
	DirectX::SimpleMath::Matrix world = 
		DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3::Down * 20.0f);

	DirectX::SimpleMath::Vector3 position = m_commonResources->GetCameraTransform()->GetLocalPosition();

	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B
	TransformConstBuffer buffer;
	buffer.matView = m_commonResources->GetViewMatrix().Transpose();
	buffer.matProj = m_commonResources->GetProjectionMatrix().Transpose();
	buffer.matWorld = world.Transpose();
	buffer.cameraPosition = { position.x , position.y , position.z ,0.0f };
	buffer.TessellationFactor = DirectX::SimpleMath::Vector4(0.0f, m_time, 2.0f, 0.0f);
	buffer.color = m_color;
	// �萔�o�b�t�@�̍X�V
	m_transformBuffer->Update(m_context, buffer);

	// ���̓��C�A�E�g��ݒ�
	m_context->IASetInputLayout(m_inputLayout);

	// �u�����h�X�e�[�g��ݒ� (�������`��p)
	m_context->OMSetBlendState(m_commonStates->NonPremultiplied(), nullptr, 0xFFFFFFFF);
	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	m_context->OMSetDepthStencilState(m_commonStates->DepthRead(), 0);
	// ���X�^���C�U�[�X�e�[�g�̐ݒ�
	m_context->RSSetState(m_commonStates->CullCounterClockwise());

	// ���_�o�b�t�@��ݒ�
	ID3D11Buffer* buffers[] = { m_vertexBuffer.Get() };
	UINT stride[] = { sizeof(DirectX::VertexPositionTexture) };
	UINT offset[] = { 0 };
	m_context->IASetVertexBuffers(0, 1, buffers, stride, offset);

	// �v���~�e�B�u�g�|���W�[�i�O�p�`���X�g�j
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);

	//	�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[4] = { m_transformBuffer->GetBuffer() , m_seaNoiseBuffer->GetBuffer() ,m_gerstnerWaveBuffer->GetBuffer(),m_constantLightBuffer->GetBuffer()};
	// �X���b�g1����3�Ɉꊇ�o�C���h
	m_context->VSSetConstantBuffers(0, 4, cb);
	m_context->HSSetConstantBuffers(0, 4, cb);
	m_context->DSSetConstantBuffers(0, 4, cb);
	m_context->PSSetConstantBuffers(0, 4, cb);
	
	// �T���v���[�X�e�[�g���s�N�Z���V�F�[�_�[�ɐݒ�
	ID3D11SamplerState* sampler[2] = { m_commonStates->AnisotropicWrap(),m_shadowMapSampler.Get() };
	m_context->PSSetSamplers(0, 2, sampler);

	//	�V�F�[�_���Z�b�g����
	m_context->VSSetShader(m_vertexShader, nullptr, 0);
	m_context->HSSetShader(m_hullShader  , nullptr, 0);
	m_context->DSSetShader(m_domainShader, nullptr, 0);
	m_context->PSSetShader(m_pixelShader , nullptr, 0);

	// �e�N�X�`���̐ݒ�
	ID3D11ShaderResourceView* tex[2] = { m_texture,shadowMap };
	m_context->PSSetShaderResources(0, 2, tex);

	// �C���X�^���X�f�[�^�̐ݒ�
	ID3D11ShaderResourceView* srvs[] = { m_instanceSRV.Get() };
	m_context->VSSetShaderResources(1, 1, srvs);

	// �h���[�R�[��
	UINT instanceCount = static_cast<UINT>(700 * 700);
	m_context->DrawInstanced(4, instanceCount, 0, 0);

	//	�V�F�[�_�̓o�^���������Ă���
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->HSSetShader(nullptr, nullptr, 0);
	m_context->DSSetShader(nullptr, nullptr, 0);
	m_context->PSSetShader(nullptr, nullptr, 0);

	// �e�N�X�`�����\�[�X�����
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	m_context->PSSetShaderResources(0, 1, nullsrv);
	m_context->VSSetShaderResources(1, 1, nullsrv);
}


/// <summary>
/// ���_�o�b�t�@�̍쐬
/// </summary>
void Sea::CreateVertexBuffer()
{
	using namespace DirectX::SimpleMath;

	std::vector<DirectX::VertexPositionTexture> vertices =
	{
		{Vector3(-5.0f , 0.0f , -5.0f),Vector2(0.0f ,0.0f)}, // ����
		{Vector3( 5.0f , 0.0f , -5.0f),Vector2(1.0f ,0.0f)}, // �E��
		{Vector3(-5.0f , 0.0f ,  5.0f),Vector2(0.0f ,1.0f)}, // ����
		{Vector3( 5.0f , 0.0f ,  5.0f),Vector2(1.0f ,1.0f)}, // ����
	};

	// ���_�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(DirectX::VertexPositionTexture) * vertices.size());
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexBufferData = {};
	vertexBufferData.pSysMem = vertices.data();

	m_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, m_vertexBuffer.ReleaseAndGetAddressOf());
}

void Sea::CreateInstanceData()
{
	constexpr int width = 700;
	constexpr int height = 700;
	constexpr float tileSize = 10.0f; // �e�|���̕�

	// �C���X�^���X�f�[�^�̔z��쐬
	std::vector<InstanceData> instanceData;
	instanceData.reserve(width * height);

	// ���_�𒆐S�ɔz�u���邽�߂̃I�t�Z�b�g
	const float offsetX = (width - 1) * tileSize * 0.5f;
	const float offsetZ = (height - 1) * tileSize * 0.5f;

	// �I�t�Z�b�g�l���v�Z���i�[���Ă���
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			float worldX = x * tileSize - offsetX;
			float worldZ = y * tileSize - offsetZ;

			InstanceData instance = {};
			instance.offset = DirectX::SimpleMath::Vector4(worldX, 0.0f, worldZ,0.0f);
			instanceData.push_back(instance);
		}
	}

	// StructuredBuffer �p�o�b�t�@�쐬
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = UINT(sizeof(InstanceData) * instanceData.size());
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.StructureByteStride = sizeof(InstanceData);
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = instanceData.data();

	m_device->CreateBuffer(&desc, &initData, m_instanceStructuredBuffer.ReleaseAndGetAddressOf());

	// Shader Resource View ���쐬
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	srvDesc.Buffer.ElementWidth = static_cast<UINT>(instanceData.size());

	m_device->CreateShaderResourceView(m_instanceStructuredBuffer.Get(), &srvDesc, m_instanceSRV.ReleaseAndGetAddressOf());
}

/// <summary>
/// �萔�o�b�t�@�̍쐬
/// </summary>
void Sea::CreateConstBuffer()
{
	// Transform�̒萔�o�b�t�@�̍쐬
	m_transformBuffer = std::make_unique<ConstantBuffer<TransformConstBuffer>>();
	// ������
	m_transformBuffer->Initialize(m_device);

	// �C�m�C�Y�̒萔�o�b�t�@�̍쐬
	m_seaNoiseBuffer = std::make_unique<ConstantBuffer<SeaNoiseConstBuffer>>();
	// ������
	m_seaNoiseBuffer->Initialize(m_device,UpdateStrategy::UPDATE_SUB_RESOURCE);

	// �g�̒萔�o�b�t�@�̍쐬
	m_gerstnerWaveBuffer = std::make_unique<ConstantBuffer<GerstnerWaveConstBuffer>>();
	// ������
	m_gerstnerWaveBuffer->Initialize(m_device, UpdateStrategy::UPDATE_SUB_RESOURCE);
	

	GerstnerWaveConstBuffer waveParams =
	{
		// ��g�i���˂�j - ������肾���Ǒ��݊�����
	   0.8f, -0.5f, 0.4f, 0.6f,
	   11.0f, 1.0f, 0.3f, 0.0f,

	   // ���g�i���j
	   0.6f, 0.4f, -0.5f, 0.4f,
	   6.5f, 1.0f, 0.35f, 0.0f,

	   // ���g�i�����g�j
	   0.4f, -0.25f, -0.6f, 0.25f,
	   2.8f, 1.2f, 0.4f, 0.0f
	};
	SeaNoiseConstBuffer seaNoise =
	{
		0.1f,
		0.01f,
		0.08f,
		0.06f,
		25.0f,
		10.0f,
		0.6f,
		0.01f
	};
	m_gerstnerWaveBuffer->Update(m_context, waveParams);
	m_seaNoiseBuffer->Update(m_context, seaNoise);


	using namespace DirectX::SimpleMath;

	// ----------------------------------------------------------- //
	// ���C�g��Ԃ̃r���[�s��Ǝˉe�s����쐬����
	// ----------------------------------------------------------- //

	/* �菇�S */

	// ���C�g�̌����Ă�������𒲐�����
	//const Vector3 lightDir = Vector3(0.0f, -1.0f, 0.0f);

	Vector3 lightDir = Vector3::Transform(Vector3(0.0f, 0.0f, 1.0f), DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(90.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180.0f)));

	// ���C�g��Ԃ̃r���[�s����v�Z����
	const Matrix lightView = Matrix::CreateLookAt(
		{ 0.0f , 10.0f ,0.0f },			// eye
		Vector3(0.0f, 10.0f, 0.0f) + lightDir,	// target
		Vector3::UnitY				// up
	);

	const Matrix Projection = Matrix::CreateOrthographicOffCenter(
		-50.0f / 2.0f, 50.0f / 2.0f,   // ���E�E
		-50.0f / 2.0f, 50.0f / 2.0f,   // ���E��
		0.1f, 1000.0f     // Near�EFar
	);

	DirectionalLightBuffer cb;
	const Matrix viewProj = lightView * Projection;
	cb.lightViewProjection = XMMatrixTranspose(viewProj);
	cb.lightPosition = Vector3(0.0f, 10.0f, 0.0f);
	cb.lightDirection = lightDir;							// ���C�g���Ƃ炷����
	cb.lightAmbient = Color(0.1f, 0.1f, 0.1f);


	// �萔�o�b�t�@�̍X�V
	m_constantLightBuffer->Update(CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), cb);
}