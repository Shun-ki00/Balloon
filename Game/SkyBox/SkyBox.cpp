// ============================================
// 
// �t�@�C����: SkyBox.cpp
// �T�v: �X�J�C�{�b�N�X�̃N���X
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include <Framework/Microsoft/ReadData.h>
#include <DDSTextureLoader.h>
#include "Game/SkyBox/SkyBox.h"

#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Game/Buffers.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SkyBox::SkyBox()
	:
	m_skyboxModel{},
	m_vertexShader{},
	m_pixelShader{},
	m_cubemap{},
	m_eveningCubeMap{},
	m_constantBuffer{},
	m_angle{},
	m_dayProgress{}
{

}

/// <summary>
/// ����������
/// </summary>
void SkyBox::Initialize()
{
	ID3D11DeviceContext* context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	Resources* resources = Resources::GetInstance();

	// �X�J�C�{�b�N�X�p���f���̍쐬
	m_skyboxModel = DirectX::GeometricPrimitive::CreateSphere(context, 2.0f, 6, false);

	// �V�F�[�_�[
	m_vertexShader = resources->GetShaderResources()->GetVertexShader(VS_ID::SkyBox_VS);
	m_pixelShader = resources->GetShaderResources()->GetPixelShader(PS_ID::SkyBox_PS);
	// �X�J�C�}�b�v
	m_cubemap = resources->GetTextureResources()->GetTexture(TextureKeyID::CubeMap);
	m_eveningCubeMap = resources->GetTextureResources()->GetTexture(TextureKeyID::EveningCubeMap);

	// �萔�o�b�t�@�p�̃o�b�t�@�I�u�W�F�N�g���쐬����
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(SkyBoxConstBuffer));	// 16�̔{�����w�肷��
	bufferDesc.Usage          = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	DX::ThrowIfFailed(
		device->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer.ReleaseAndGetAddressOf())
	);

	// ��]�p��������
	m_angle = 0.0f;
	// ����̐i�s�x��������
	m_dayProgress = 0.0f;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void SkyBox::Update(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	float elapsedTime = (float)CommonResources::GetInstance()->GetStepTimer()->GetElapsedSeconds();

	m_angle += elapsedTime * 30.0f;

	// ���[���h�s��̍쐬
	DirectX::SimpleMath::Matrix world =
		DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle * 0.01f));

	// GPU���g�p���郊�\�[�X�̃�������CPU����A�N�Z�X����ۂɗ��p����\����
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	// �R���e�L�X�g
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �萔�o�b�t�@���}�b�v����
	context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// �萔�o�b�t�@�ɑ���f�[�^����������
	SkyBoxConstBuffer* cb = static_cast<SkyBoxConstBuffer*>(mappedResource.pData);
	cb->worldMatrix = world.Transpose();
	cb->viewMatrix = view.Transpose();
	cb->projectionMatrix = projection.Transpose();
	cb->dayProgress = DirectX::SimpleMath::Vector4(m_dayProgress, 0.0f, 0.0f, 0.0f);
	// �}�b�v����������
	context->Unmap(m_constantBuffer.Get(), 0);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="context">�R���e�L�X�g</param>
/// <param name="states">�R�����X�e�[�g</param>
void SkyBox::Render(ID3D11DeviceContext1* context, DirectX::CommonStates* states)
{
	// �X�J�C�{�b�N�X�̕`��
	m_skyboxModel->Draw({}, {}, {}, {}, nullptr, false, [&]()
		{
			// �V�F�[�_�[�̐ݒ�
			context->VSSetShader(m_vertexShader, nullptr, 0);
			context->PSSetShader(m_pixelShader , nullptr, 0);

			// �萔�o�b�t�@�̐ݒ�i���ʒ萔�o�b�t�@�̂݁j
			context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
			context->PSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());

			// �e�N�X�`����ݒ�
			context->PSSetShaderResources(0 , 1, &m_cubemap);
			context->PSSetShaderResources(1 , 1, &m_eveningCubeMap);

			// �T���v���[�̐ݒ�
			auto sampler = states->LinearClamp();
			context->VSSetSamplers(0, 1, &sampler);
			context->PSSetSamplers(0, 1, &sampler);
		});

	// �V�F�[�_�̉��
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	// ���\�[�X�̉��
	ID3D11ShaderResourceView* resource = nullptr;
	context->PSSetShaderResources(0, 1, &resource);
	context->PSSetShaderResources(1, 1, &resource);
}