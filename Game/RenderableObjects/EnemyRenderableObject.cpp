#include "pch.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Framework/Resources/ShaderResources.h"
#include "Game/RenderableObjects/EnemyRenderableObject.h"
#include "Game/Buffers/ConstantBuffer.h"
#include "Game/AmbientLight/AmbientLight.h"
#include "Game/Buffers.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="model">���f��</param>
EnemyRenderableObject::EnemyRenderableObject(const bool& isActive, DirectX::Model* model)
	:
	m_isAcitve(isActive),
	m_model(model),
	m_baseMap{},
	m_normalMap{},
	m_skyMap{},
	m_worldMatrix{},
	m_constants{},
	m_constantBuffer{}
{
	// ���L���\�[�X�̃C���X�^���X���擾����
	m_resources = Resources::GetInstance();
	// �f�o�C�X���擾����
	m_device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	m_ambientLight = AmbientLight::GetInstance();
}

/// <summary>
/// ����������
/// </summary>
/// <param name="constants">�萔�o�b�t�@�̊i�[�p�f�[�^</param>
void EnemyRenderableObject::Initialize(const PBRLitConstantBuffer& constants)
{
	// �萔�o�b�t�@�ɑ���f�[�^�̏����l�ݒ�
	m_constants = constants;

	// �萔�o�b�t�@�I�u�W�F�N�g�̍쐬
	m_constantBuffer = std::make_unique<ConstantBuffer<PBRLitConstantBuffer>>();
	m_constantBuffer->Initialize(m_device);

	// �e�N�X�`����ݒ�
	m_baseMap   = m_resources->GetTextureResources()->GetTexture(TextureKeyID::Enemy);
	m_normalMap = m_resources->GetTextureResources()->GetTexture(TextureKeyID::Wood);
	m_skyMap    = m_resources->GetTextureResources()->GetTexture(TextureKeyID::CubeMap);

	// �C���v�b�g���C�A�E�g��ݒ�
	m_inputLayout = m_resources->GetShaderResources()->GetPBRLitInputLayout();
	// ���_�V�F�[�_�[��ݒ�
	m_vertexShader = m_resources->GetShaderResources()->GetVertexShader(VS_ID::PBRLit_VS);
	// �s�N�Z���V�F�[�_�[��ݒ�
	m_pixelShader = m_resources->GetShaderResources()->GetPixelShader(PS_ID::PBRLit_PS);

	// ���[���h�s�񏉊���
	m_worldMatrix = DirectX::SimpleMath::Matrix::Identity;

	// ���f���̃G�t�F�N�g�����X�V����
	m_model->UpdateEffects([](DirectX::IEffect* effect) {
		// �x�[�V�b�N�G�t�F�N�g��ݒ肷��
		DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
		if (basicEffect)
		{
			// �g�U���ˌ�
			DirectX::SimpleMath::Color diffuseColor = DirectX::SimpleMath::Color(1.0f, 0.95f, 0.9f);
			// ���C�g���Ƃ炷����
			DirectX::SimpleMath::Vector3 lightDirection(0.0f, 1.0f, 0.0f);

			basicEffect->SetLightEnabled(1, false);
			basicEffect->SetLightEnabled(2, false);

			// �[���Ԃ̃��C�g�Ɋg�U���ˌ���ݒ肷��
			basicEffect->SetLightDiffuseColor(0, diffuseColor);
			// �[���Ԃ̃��C�g���Ƃ炷������ݒ肷��
			basicEffect->SetLightDirection(0, lightDirection);
		}
		});
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="context">�R���e�L�X�g</param>
/// <param name="worldMatrix">���[���h�s��</param>
void EnemyRenderableObject::Update(ID3D11DeviceContext* context, const DirectX::SimpleMath::Matrix& worldMatrix)
{
	// ���[���h�s����X�V����
	m_worldMatrix = worldMatrix;
	// �l���ύX����Ă���ꍇ�X�V�������s��
	this->UpdateConstantBufferIfNeeded(context);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="context">�R���e�L�X�g</param>
void EnemyRenderableObject::Render(ID3D11DeviceContext* context, DirectX::CommonStates* commonStates,
	DirectX::SimpleMath::Matrix viewMatrix, DirectX::SimpleMath::Matrix projectionMatrix
)
{
	// ��A�N�e�B�u�̎��͕`�悵�Ȃ�
	if (!m_isAcitve) return;

	// ���f���`��
	m_model->Draw(context, *commonStates, m_worldMatrix, viewMatrix, projectionMatrix, false, [&]
		{
			// �萔�o�b�t�@���w�肷��
			ID3D11Buffer* cbuf[] = { m_ambientLight->GetBuffer()};
			context->VSSetConstantBuffers(1, 1, cbuf);
			context->PSSetConstantBuffers(1, 1, cbuf);

			// �u�����h�X�e�[�g��ݒ� (�������`��p)
			context->OMSetBlendState(commonStates->AlphaBlend(), nullptr, 0xFFFFFFFF);

			context->IASetInputLayout(m_inputLayout);

			// �萔�o�b�t�@���w�肷��
			cbuf[0] = { m_constantBuffer->GetBuffer()};
			context->VSSetConstantBuffers(2, 1, cbuf);
			context->PSSetConstantBuffers(2, 1, cbuf);

			// �e�N�X�`���̐ݒ�
			std::vector<ID3D11ShaderResourceView*> tex = {
				m_baseMap,
				m_normalMap,
				m_skyMap,
			};

			context->VSSetShaderResources(0, (UINT)tex.size(), tex.data());
			context->PSSetShaderResources(0, (UINT)tex.size(), tex.data());

			// �V�F�[�_�[��ݒ�
			context->VSSetShader(m_vertexShader, nullptr, 0);
			context->PSSetShader(m_pixelShader, nullptr, 0);

			// �T���v���[�X�e�[�g���w�肷��
			ID3D11SamplerState* sampler[] = { commonStates->LinearWrap() };
			context->VSSetSamplers(0, 1, sampler);
			context->PSSetSamplers(0, 1, sampler);
		});

	// �V�F�[�_�̉��
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	// �e�N�X�`�����\�[�X�̉��
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	context->PSSetShaderResources(0, 1, nullsrv);
	context->PSSetShaderResources(1, 1, nullsrv);
	context->PSSetShaderResources(2, 1, nullsrv);
}

/// <summary>
/// �萔�o�b�t�@���擾����
/// </summary>
/// <returns>�o�b�t�@</returns>
ID3D11Buffer* EnemyRenderableObject::GetConstantBuffer() const
{
	return m_constantBuffer->GetBuffer();
}


/// <summary>
/// �l���ύX���ꂽ�ꍇ�萔�o�b�t�@���X�V����
/// </summary>
/// <param name="context">�R���e�L�X�g</param>
void EnemyRenderableObject::UpdateConstantBufferIfNeeded(ID3D11DeviceContext* context)
{
	m_constantBuffer->UpdateIfNeeded(context, m_constants);
}
