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
	// �V�[���Ԃ̃p�����[�^
	m_datas.insert({ "SceneLinkParams" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/SceneLinkParams.msgpack") });

	// �^�C�g���V�[���f�[�^���[�h
	m_datas.insert({ "Title" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/TitleScene.msgpack") });
	// �X�e�[�W�Z���N�g�V�[���f�[�^���[�h
	m_datas.insert({ "StageSelect" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/StageSelectScene.msgpack") });
	// �Q�[���N���A�V�[���f�[�^���[�h
	m_datas.insert({ "Clear" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/GameClearScene.msgpack") });
	// �Q�[���I�[�o�[�V�[���f�[�^���[�h
	m_datas.insert({ "GameOver" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/GameOverScene.msgpack") });

	// �v���C�V�[���f�[�^���[�h
	m_datas.insert({ "Play0" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/PlayScene.msgpack") });
	// �v���C�V�[���f�[�^���[�h
	m_datas.insert({ "Play1" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/PlayScene1.msgpack") });
	// �v���C�V�[���f�[�^���[�h
	m_datas.insert({ "Play2" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/PlayScene2.msgpack") });
}

