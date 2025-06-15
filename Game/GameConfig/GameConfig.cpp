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