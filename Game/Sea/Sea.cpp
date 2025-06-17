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
	m_texture{}
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
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// �V�F�[�_�[���擾����
	m_vertexShader = m_resources->GetShaderResources()->GetVertexShader(VS_ID::Sea_VS);
	m_hullShader   = m_resources->GetShaderResources()->GetHullShader(HS_ID::Sea_HS);
	m_domainShader = m_resources->GetShaderResources()->GetDomainShader(DS_ID::Sea_DS);
	m_pixelShader  = m_resources->GetShaderResources()->GetPixelShader(PS_ID::Sea_PS);
	// �C���v�b�g���C�A�E�g���擾
	m_inputLayout = m_resources->GetShaderResources()->GetSeaInputLayout();

	// �e�N�X�`�����擾����
	m_texture = m_resources->GetTextureResources()->GetTexture(TextureKeyID::Sea);

	// �萔�o�b�t�@�̍X�V
	this->CreateBuffer();

	// �ו��x
	m_index = 1.0f;
	// �^�C��������
	m_time = 0.0f;
}

/// <summary>
/// �`�揈��
/// </summary>
void Sea::Render()
{
	// �^�C�}�[�̍X�V
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();
	m_time += elapsedTime;
	// �ו��x�ݒ�
	m_index = 40.0f;

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
	buffer.TessellationFactor = DirectX::SimpleMath::Vector4(m_index, m_time, 2.0f, 0.0f);
	// �萔�o�b�t�@�̍X�V
	m_transformBuffer->Update(m_context, buffer);

	// ���̓��C�A�E�g��ݒ�
	m_context->IASetInputLayout(m_inputLayout);

	// ���_�o�b�t�@��ݒ�
	ID3D11Buffer* buffers[] = { m_vertexBuffer.Get() };
	UINT stride[] = { sizeof(DirectX::VertexPositionTexture) };
	UINT offset[] = { 0 };
	m_context->IASetVertexBuffers(0, 1, buffers, stride, offset);

	//	�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[3] = { m_transformBuffer->GetBuffer() , m_seaNoiseBuffer->GetBuffer() ,m_gerstnerWaveBuffer->GetBuffer()};
	// �X���b�g1����3�Ɉꊇ�o�C���h
	m_context->VSSetConstantBuffers(0, 3, cb);
	m_context->HSSetConstantBuffers(0, 3, cb);
	m_context->DSSetConstantBuffers(0, 3, cb);
	m_context->PSSetConstantBuffers(0, 3, cb);

	// �T���v���[�X�e�[�g���s�N�Z���V�F�[�_�[�ɐݒ�
	ID3D11SamplerState* sampler[1] = { m_commonStates->LinearWrap() };
	m_context->PSSetSamplers(0, 1, sampler);

	// �u�����h�X�e�[�g��ݒ� (�������`��p)
	m_context->OMSetBlendState(m_commonStates->AlphaBlend(), nullptr, 0xFFFFFFFF);

	// �v���~�e�B�u�g�|���W�[��ݒ�
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST);

	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	m_context->OMSetDepthStencilState(m_commonStates->DepthDefault(), 0);
	// ���X�^���C�U�[�X�e�[�g�̐ݒ�
	m_context->RSSetState(m_commonStates->CullCounterClockwise());

	//	�V�F�[�_���Z�b�g����
	m_context->VSSetShader(m_vertexShader, nullptr, 0);
	m_context->HSSetShader(m_hullShader  , nullptr, 0);
	m_context->DSSetShader(m_domainShader, nullptr, 0);
	m_context->PSSetShader(m_pixelShader , nullptr, 0);

	// �e�N�X�`���̐ݒ�
	ID3D11ShaderResourceView* tex[1] = { m_texture };
	m_context->PSSetShaderResources(0, 1, tex);

	// �`��R�[��
	m_context->Draw(static_cast<UINT>(32 * (700 * 700)), 0);

	//	�V�F�[�_�̓o�^���������Ă���
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->HSSetShader(nullptr, nullptr, 0);
	m_context->DSSetShader(nullptr, nullptr, 0);
	m_context->PSSetShader(nullptr, nullptr, 0);

	// �e�N�X�`�����\�[�X�����
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	m_context->PSSetShaderResources(0, 1, nullsrv);
}

/// <summary>
/// �o�b�t�@�̍쐬
/// </summary>
void Sea::CreateBuffer()
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
	

	// �萔�̍X�V
	GerstnerWaveConstBuffer waveParams =
	{
		// ��g�i���˂�j
		1.2f, -0.8f,  0.6f, 0.9f,
		12.0f, 1.4f, 0.4f, 0.0f,

		// ���g�i���ˊ��j
		0.9f,  0.6f, -0.7f, 0.6f,
		6.0f,  1.6f, 0.5f, 0.0f,

		// ���g�i�ׂ������̂����g�j
		0.6f, -0.3f, -1.1f, 0.3f,
		2.5f, 2.0f,  0.65f, 0.0f
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

	const int PATCH_COUNT_X = 700;
	const int PATCH_COUNT_Z = 700;
	const int PATCH_TOTAL = PATCH_COUNT_X * PATCH_COUNT_Z;
	const int VERTICES_PER_PATCH = 32;
	const int TOTAL_VERTICES = PATCH_TOTAL * VERTICES_PER_PATCH;

	std::vector<DirectX::VertexPositionTexture> vertices(TOTAL_VERTICES);

	// 1�̃p�b�`�̃T�C�Y
	const float PATCH_SIZE = 20.0f; // �e�p�b�`�̗̈�i���[���h���W�Łj
	const float HALF_EXTENT_X = PATCH_COUNT_X * PATCH_SIZE * 0.5f;
	const float HALF_EXTENT_Z = PATCH_COUNT_Z * PATCH_SIZE * 0.5f;

	for (int patchZ = 0; patchZ < PATCH_COUNT_Z; ++patchZ) {
		for (int patchX = 0; patchX < PATCH_COUNT_X; ++patchX) {

			int patchIndex = patchZ * PATCH_COUNT_X + patchX;
			int baseVertexIndex = patchIndex * VERTICES_PER_PATCH;

			float offsetX = patchX * PATCH_SIZE - HALF_EXTENT_X;
			float offsetZ = patchZ * PATCH_SIZE - HALF_EXTENT_Z;

			for (int z = 0; z < 4; ++z) {
				for (int x = 0; x < 8; ++x) {
					int localIndex = z * 8 + x;

					float fx = offsetX + PATCH_SIZE * (float)x / 7.0f;
					float fz = offsetZ + PATCH_SIZE * (float)z / 3.0f;

					float u = (float)x / 7.0f;
					float v = (float)z / 3.0f;

					vertices[baseVertexIndex + localIndex] = {
						DirectX::XMFLOAT3(fx, 0.0f, fz),
						DirectX::XMFLOAT2(u, v)
					};
				}
			}
		}
	}


	// ���_�o�b�t�@�̐���
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(DirectX::VertexPositionTexture) * vertices.size());
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;

	// ���_�f�[�^�̏�����
	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = vertices.data();

	m_device->CreateBuffer(&vertexBufferDesc, &vertexData, m_vertexBuffer.ReleaseAndGetAddressOf());

}



