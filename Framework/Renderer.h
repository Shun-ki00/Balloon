#pragma once
#include "Interface/IObject.h"
#include "Interface/IRenderableObject.h"
#include "Game/Buffers/ConstantBuffer.h"
#include "Game/Particle/ParticleEmitter.h"
#include "Game/ShadowMap/CascadedShadowMap.h"

class CommonResources;
class Particle;
class ParticleEmitter;
class UIRenderableObject;
class CascadedShadowMap;

class Renderer
{

public:
	// �R���X�g���N�^
	Renderer();
	// �f�X�g���N�^
	~Renderer() = default;

	// �V���h�E�}�b�v���擾����
	ID3D11ShaderResourceView* GetShadowMap() const { return m_shadowMap->GetShadowShaderResourceView(); }

	// �`��I�u�W�F�N�g�ǉ�
	void Attach(IObject* object, IRenderableObject* renderableObject);
	void Attach(ParticleEmitter* emitter) { m_particleEmitter.push_back(emitter); }
	void Attach(IObject* object, UIRenderableObject* renderableObject);

	// �`�揈��
	void Render();

	// �A�^�b�`�̋���
	void Begin();
	// �A�^�b�`�̏I��
	void End();

	// �I�u�W�F�N�g�̍폜
	void Reset();

private:

	// ���f���̕`��
	void ModelRender(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix);
	// �p�[�e�B�N���`��
	void ParticleRender(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix);
	// UI�`��
	void UIRender();

	// �A�N�e�B�u��Ԃ�T��
	bool IsHierarchyActive(IObject* object);

private:
	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �f�o�C�X
	ID3D11Device1* m_device;
	// �R���e�L�X�g
	ID3D11DeviceContext1* m_context;
	// �R�����X�e�[�g
	DirectX::CommonStates* m_commonStates;

	// �`��̋���
	bool m_isActiveAttach;


	// �`��I�u�W�F�N�g
	std::vector<IObject*> m_objectKeys;
	std::unordered_map<IObject*, IRenderableObject*> m_modelRenderableObjects;

	// UI�`��I�u�W�F�N�g
	std::vector<IObject*> m_UIObjectKeys;
	std::unordered_map<IObject*, UIRenderableObject*> m_UIRenderableObjects;

	// �p�[�e�B�N���I�u�W�F�N�g
	std::vector<ParticleEmitter*> m_particleEmitter;

	// �e�I�u�W�F�N�g�̐�
	int m_objectNumber;
	int m_uiObjectNumber;
	int particleEmitterNumber;

	// �V���h�E�}�b�v�`��
	std::unique_ptr<CascadedShadowMap> m_shadowMap;


	// === UI ===

	// �C���v�b�g���C�A�E�g
	ID3D11InputLayout* m_uiInputLayout;
	// ���_�V�F�[�_�[
	ID3D11VertexShader* m_uiVertexShader;
	// �W�I���g���V�F�[�_�[
	ID3D11GeometryShader* m_uiGeometryShader;
	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_uiVertexBuffer;
	// �萔�o�b�t�@�f�[�^
	UIConstBuffer m_uiConstBufferData;
	// �萔�o�b�t�@
	std::unique_ptr<ConstantBuffer<UIConstBuffer>> m_uiConstBuffer;

	// === �p�[�e�B�N�� ===
	
	// �C���v�b�g���C�A�E�g
	ID3D11InputLayout* m_particleiInputLayout;
	// �萔�o�b�t�@
	std::unique_ptr<ConstantBuffer<ParticleConstBuffer>> m_particleConstBuffer;
	// ���_�V�F�[�_�[
	ID3D11VertexShader* m_particleVertexShader;
	// �W�I���g���V�F�[�_�[
	ID3D11GeometryShader* m_particleGeometryShader;
	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_particleVertexBuffer;
	// �r���{�[�h
	DirectX::SimpleMath::Matrix m_billboardMatrix;
};