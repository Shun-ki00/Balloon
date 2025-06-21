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
	// �o�C�i���Ƃ��ĊJ��
	std::ifstream file("Resources/Json/Binary/GameResourceData.msgpack", std::ios::binary);
	
	// �o�C�i�����e��S�ǂݍ���
	std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});

	// MessagePack ���� JSON �֕ϊ�
	nlohmann::json data = nlohmann::json::from_msgpack(buffer);

	// �f�[�^���i�[
	m_data = data;

	// ���f�������[�h����
	std::thread model(&Resources::LoadModel, this);
	// �V�F�[�_�[�����[�h����
	std::thread shader(&Resources::LoadShader, this);
	// �e�N�X�`�������[�h����
	std::thread texture(&Resources::LoadTexture, this);
	// �Q�[���f�[�^�����[�h����
	std::thread gameData(&Resources::LoadGameData, this);

	// ���[�h���I���܂ő҂�
	model.join();
	texture.join();
	shader.join();
	gameData.join();

	// �����������ȊO�K�v�Ȃ��̂Ńf�[�^����ɂ���
	m_data = {};
}
