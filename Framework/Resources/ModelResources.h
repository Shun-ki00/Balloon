// ============================================
// 
// �t�@�C����: ModelResources.h
// �T�v: ModelResources.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Framework/Resources/ResourceKeys.h"

class ModelResources
{
public:
	// �e�N�X�`�����擾����
	DirectX::Model* GetModel(ModelKeyID id);

public:
	ModelResources(const ModelResources&) = delete;             // �R�s�[�֎~
	ModelResources& operator=(const ModelResources&) = delete;  // �R�s�[����֎~
	ModelResources(const ModelResources&&) = delete;            // ���[�u�֎~
	ModelResources& operator=(const ModelResources&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static ModelResources* GetInstance()
	{
		static ModelResources instance;
		return &instance;
	}
	// ���\�[�X�����[�h����
	void LoadResource(const nlohmann::json& data);

private:
	// �R���X�g���N�^
	ModelResources();
	// �f�X�g���N�^
	~ModelResources() = default;

private:

	// ���f���̃��X�g
	std::unordered_map<std::string, std::unique_ptr<DirectX::Model>> m_models;
};