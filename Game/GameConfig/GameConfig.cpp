#include "pch.h"
#include "Game/GameConfig/GameConfig.h"
#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <fstream>
#include <WICTextureLoader.h>
#include "Game/Parameters/ParameterBuffers.h"
#include "Framework/Utilities/JsonUtilities.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameConfig::GameConfig()
{
}

/// <summary>
/// �S�Ẵf�[�^�����[�h����
/// </summary>
void GameConfig::LoadJsonFile()
{
	// �^�C�g���V�[���f�[�^���[�h
	m_datas.insert({ "Title" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/TitleScene.msgpack") });
	// �Q�[���N���A�V�[���f�[�^���[�h
	m_datas.insert({ "Clear" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/GameClearScene.msgpack") });
}

