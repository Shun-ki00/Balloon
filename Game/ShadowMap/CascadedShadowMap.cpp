// ============================================
// 
// �t�@�C����: CascadedShadowMap.h
// �T�v: �J�X�P�[�h�V���h�E�}�b�v���쐬����N���X
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/ShadowMap/CascadedShadowMap.h"
#include <Framework/Microsoft/RenderTexture.h>

#include "Framework/CommonResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Game/Transform/Transform.h"
#include "Framework/DepthStencil.h"
#include "Game/Buffers.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
CascadedShadowMap::CascadedShadowMap()
	:
	m_commonResources{},
	m_cascadedIndex{},
	m_transform{},
	m_lightProjectionMatrix{},
	m_lightViewMatrix{},
	m_cameraTransform{},
	m_shadowMapRT{},
	m_shadowMapDS{},
	m_shadowVS{},
	m_shadowPS{},
	m_shadowMapSampler{},
	m_DLBuffer{}
{
	// ���L���\�[�X�̃C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// ����������
/// </summary>
void CascadedShadowMap::Initialize()
{
	ID3D11Device1* device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// �V�F�[�_�[���擾
	m_shadowVS = Resources::GetInstance()->GetShaderResources()->GetVertexShader(VS_ID::ShadowMap_VS);
	m_shadowPS = Resources::GetInstance()->GetShaderResources()->GetPixelShader(PS_ID::ShadowMap_PS);

	// �V���h�E�}�b�v�̑傫�����w�肷��
	const RECT rectShadow = { 0 , 0 , (LONG)SHADOWMAP_SIZE , (LONG)SHADOWMAP_SIZE };

	// �����_�[�e�N�X�`�����쐬����
	m_shadowMapRT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
	m_shadowMapRT->SetDevice(device);
	m_shadowMapRT->SetWindow(rectShadow);

	// �[�x�X�e���V�����쐬����
	m_shadowMapDS = std::make_unique<DepthStencil>(DXGI_FORMAT_D32_FLOAT);
	m_shadowMapDS->SetDevice(device);
	m_shadowMapDS->SetWindow(rectShadow);

	// �V���h�E�}�b�v�p�̃T���v���[���쐬����
	D3D11_SAMPLER_DESC samplerDesc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
	samplerDesc.Filter         = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU       = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressV       = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressW       = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS;

	DX::ThrowIfFailed(
		device->CreateSamplerState(&samplerDesc, m_shadowMapSampler.ReleaseAndGetAddressOf())
	);

	// �萔�o�b�t�@�p�̃o�b�t�@�I�u�W�F�N�g���쐬����
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(DirectionalLightBuffer)); // 16�̔{�����w�肷��
	bufferDesc.Usage          = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	DX::ThrowIfFailed(
		device->CreateBuffer(&bufferDesc, nullptr, m_DLBuffer.ReleaseAndGetAddressOf())
	);

	// ���C�g�̏�����
	m_transform = std::make_unique<Transform>();
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::UnitY * 10.0f);
	m_transform->SetLocalRotation(
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(90.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY,DirectX::XMConvertToRadians(180.0f))
	);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::Zero);

	// �v���W�F�N�V�����s����쐬
	m_lightProjectionMatrix = DirectX::SimpleMath::Matrix::CreateOrthographicOffCenter(
		-50.0f / 2.0f, 50.0f / 2.0f,   // ���E�E
		-50.0f / 2.0f, 50.0f / 2.0f,   // ���E��
		0.1f, 1000.0f                  // Near�EFar
	);
}

/// <summary>
/// �e�`�揈��
/// </summary>
/// <param name="model">���f��</param>
/// <param name="world">���[���h�s��</param>
void CascadedShadowMap::Draw(DirectX::Model* model, ID3D11DeviceContext1* context, DirectX::CommonStates* states,
	DirectX::SimpleMath::Matrix world)
{
	// �e�p���f���`��
	model->Draw(context, *states, world, m_lightViewMatrix, m_lightProjectionMatrix, false, [&]
		{
			context->VSSetShader(m_shadowVS, nullptr, 0);
			context->PSSetShader(m_shadowPS, nullptr, 0);
		}
	);
}

/// <summary>
/// �e�`�揀��
/// </summary>
void CascadedShadowMap::Begin()
{
	// �f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext1* context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// �K�v��view���擾����
	ID3D11RenderTargetView*   rtv = m_shadowMapRT->GetRenderTargetView();
	ID3D11DepthStencilView*   dsv = m_shadowMapDS->GetDepthStencilView();

	// �V���h�E�}�b�v�p��RTV��DSV���N���A����
	context->ClearRenderTargetView(rtv, DirectX::Colors::White);
	context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);

	// RTV��DSV���V���h�E�}�b�v�p�ɕύX����
	context->OMSetRenderTargets(1, &rtv, dsv);

	// �r���[�|�[�g���V���h�E�}�b�v�p�ɕύX����
	const D3D11_VIEWPORT vp = { 0.0f,0.0f,SHADOWMAP_SIZE,SHADOWMAP_SIZE,0.0f,1.0f };
	context->RSSetViewports(1, &vp);

	// ���C�g�̕���
	DirectX::SimpleMath::Vector3 lightDirection = DirectX::SimpleMath::Vector3::Transform(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), m_transform->GetLocalRotation()
	);
	// ���C�g�̌����Ă�������𒲐����� scale���^�[�Q�b�g�Ƃ��Ă݂�
	m_transform->SetLocalScale(
		m_transform->GetLocalPosition() + lightDirection
	);
	
	// ���C�g��Ԃ̃r���[�s����v�Z����
	m_lightViewMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(
		m_transform->GetLocalPosition(),     // eye
		m_transform->GetLocalScale(),        // targetd
		DirectX::SimpleMath::Vector3::UnitY  // up
	);

	// GPU���g�p���郊�\�[�X�̃�������CPU����A�N�Z�X����ۂɗ��p����\����
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	// �萔�o�b�t�@���}�b�v����
	context->Map(m_DLBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// �萔�o�b�t�@�ɑ���f�[�^����������
	DirectionalLightBuffer* cb = static_cast<DirectionalLightBuffer*>(mappedResource.pData);
	const DirectX::SimpleMath::Matrix viewProj = m_lightViewMatrix * m_lightProjectionMatrix;
	cb->lightViewProjection = DirectX::XMMatrixTranspose(viewProj);	   // �r���[�s��Ǝˉe�s������Z��������
	cb->lightPosition  = m_transform->GetLocalPosition();	           // ���C�g�̍��W
	cb->lightDirection = lightDirection;							   // ���C�g���Ƃ炷����
	cb->lightAmbient   = DirectX::SimpleMath::Color(0.2f, 0.2f, 0.2f); // ����

	// �}�b�v����������
	context->Unmap(m_DLBuffer.Get(), 0);
}

/// <summary>
/// �e�`��I������
/// </summary>
void CascadedShadowMap::End()
{
	// �f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext1* context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// RTV��DSV��ʏ�`��p�̐ݒ�ɖ߂�����
	ID3D11RenderTargetView* defaultRTV = m_commonResources->GetDeviceResources()->GetRenderTargetView();
	ID3D11DepthStencilView* defaultDSV = m_commonResources->GetDeviceResources()->GetDepthStencilView();

	// �`���ɒʏ�`��p��RTV��DSV��ݒ肷��
	context->OMSetRenderTargets(1, &defaultRTV, defaultDSV);

	// �r���[�|�[�g��ʏ�`��p�ɐ؂�ւ���
	auto const& defaultVP = m_commonResources->GetDeviceResources()->GetScreenViewport();
	context->RSSetViewports(1, &defaultVP);
}



