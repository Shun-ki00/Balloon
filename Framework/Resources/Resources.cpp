// ============================================
// 
// �t�@�C����: Resources.cpp
// �T�v: �e�탊�\�[�X�̊Ǘ��Ɠǂݍ��݂��s���N���X�i�V���O���g���j
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Framework/Resources/Resources.h"
#include <iostream>
#include <fstream>
#include <thread>
// �e���\�[�X
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Resources::Resources()
{
	// �C���X�^���X���擾����
	m_modelResources    = ModelResources::GetInstance();
	m_shaderResources   = ShaderResources::GetInstance();
	m_textureResources  = TextureResources::GetInstance();
}


/// <summary>
/// �e���\�[�X�̃��[�h
/// </summary>
void Resources::LoadResource()
{
	// JSON�t�@�C�����J��
	std::ifstream file("Resources/Json/GameResourceData.json");
	assert(file);
	// JSON �����[�h
	nlohmann::json data;
	file >> data; 

	// JSON�t�@�C�����J��
	std::ifstream StageDatafile("Resources/Json/StageData.json");
	assert(StageDatafile);
	// JSON �����[�h
	nlohmann::json StageData;
	StageDatafile >> StageData;

	// �f�[�^���i�[
	m_data = data;

	// ���f�������[�h����
	std::thread model(&Resources::LoadModel, this);
	// �V�F�[�_�[�����[�h����
	std::thread shader(&Resources::LoadShader, this);
	// �e�N�X�`�������[�h����
	std::thread texture(&Resources::LoadTexture, this);

	// ���[�h���I���܂ő҂�
	model.join();
	texture.join();
	shader.join();
	
}
