// ============================================
// 
// �t�@�C����: CascadedShadowMap.h
// �T�v: CascadedShadowMap.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Framework/Microsoft/RenderTexture.h"
#include "Framework/DepthStencil.h"
#include <Model.h>

// �O���錾
class Transform;
class DepthStencil;
class CommonResources;

namespace DX
{
	class RenderTexture;
}

// CSM
class CascadedShadowMap
{
private:
	const float SHADOWMAP_SIZE = 2120.0f;

public:
	// ���݂̃J������Transform��ݒ肷��
	void SetCameraTrasform(Transform* transform) { m_cameraTransform = transform; }
	// �e�̃V�F�[�_�[���\�[�X���擾����
	ID3D11ShaderResourceView* GetShadowShaderResourceView() const { return m_shadowMapRT->GetShaderResourceView(); }
	// �萔�o�b�t�@���擾����
	ID3D11Buffer* GetBuffer() const { return m_DLBuffer.Get(); }

public:
	// �R���X�g���N�^
	CascadedShadowMap();
	// �f�X�g���N�^
	~CascadedShadowMap() = default;

public:

	// ����������
	void Initialize();
	// �`�揈��
	void Draw(DirectX::Model* model ,ID3D11DeviceContext1* context, DirectX::CommonStates* states,
		Transform* transform);

	void Begin();
	void End();



private:
	// ���L���\�[�X
	CommonResources* m_commonResources;

	// �J�X�P�[�h
	int m_cascadedIndex;

	// �f�B���N�V���i�����C�gTransform
	std::unique_ptr<Transform> m_transform;
	// �f�B���N�V���i�����C�g�v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_lightProjectionMatrix;
	// �f�B���N�V���i�����C�g�r���[�s��
	DirectX::SimpleMath::Matrix m_lightViewMatrix;
	// �f�B���N�V���i�����C�g�o�b�t�@�p�̃o�b�t�@�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_DLBuffer;

	// ���݂̃J������Trasform
	Transform* m_cameraTransform;

	// �V���h�E�}�b�v�p�i�����_�[�e�N�X�`���j
	std::unique_ptr<DX::RenderTexture> m_shadowMapRT;
	// �V���h�E�}�b�v�p�i�f�v�X�X�e���V���j
	std::unique_ptr<DepthStencil> m_shadowMapDS;
	// ���_�V�F�[�_
	ID3D11VertexShader* m_shadowVS;
	// �s�N�Z���V�F�[�_
	ID3D11PixelShader*  m_shadowPS;
	// �T���v��
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;
};