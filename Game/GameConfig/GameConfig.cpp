#include "pch.h"
#include "Game/GameConfig/GameConfig.h"
#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <fstream>
#include <WICTextureLoader.h>
#include "Game/Parameters/ParameterBuffers.h"

GameConfig::GameConfig()
{
	// �^�C�g���V�[���̃f�[�^�����[�h
	this->LoadBinaryJsonFile("Title", "Resources/Json/TitleScene.msgpack");
	this->LoadBinaryJsonFile("Clear", "Resources/Json/GameClearScene.msgpack");
}

/// <summary>
/// �f�[�^�̃��[�h
/// </summary>
/// <param name="key">�L�[</param>
/// <param name="path">�t�@�C���p�X</param>
void GameConfig::LoadJsonFile(const std::string& key, const std::string& path)
{
	// �t�@�C����ǂݍ���
	std::ifstream file(path);

	// Json�ɕϊ�
	nlohmann::json j;
	file >> j;

	// �t�@�C�������
	file.close();

	// �f�[�^�̊i�[
	m_datas.insert({ key , j });
}

/// <summary>
/// �o�C�i���f�[�^��JSON�����[�h����
/// </summary>
/// <param name="key"></param>
/// <param name="path"></param>
void GameConfig::LoadBinaryJsonFile(const std::string& key, const std::string& path)
{
	// �o�C�i���Ƃ��ĊJ��
	std::ifstream file(path, std::ios::binary);
	if (!file)
	{
		throw std::runtime_error("�t�@�C�����J���܂���: " + path);
	}

	// �o�C�i�����e��S�ǂݍ���
	std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});

	// MessagePack ���� JSON �֕ϊ�
	nlohmann::json j = nlohmann::json::from_msgpack(buffer);

	// �f�[�^�i�[
	m_datas.insert({ key , j });
}