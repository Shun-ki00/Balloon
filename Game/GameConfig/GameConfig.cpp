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
/// コンストラクタ
/// </summary>
GameConfig::GameConfig()
{
}

/// <summary>
/// 全てのデータをロードする
/// </summary>
void GameConfig::LoadJsonFile()
{
	// シーン間のパラメータ
	m_datas.insert({ "SceneLinkParams" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/SceneLinkParams.msgpack") });

	// タイトルシーンデータロード
	m_datas.insert({ "Title" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/TitleScene.msgpack") });
	// ステージセレクトシーンデータロード
	m_datas.insert({ "StageSelect" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/StageSelectScene.msgpack") });
	// ゲームクリアシーンデータロード
	m_datas.insert({ "Clear" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/GameClearScene.msgpack") });
	// ゲームオーバーシーンデータロード
	m_datas.insert({ "GameOver" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/GameOverScene.msgpack") });
	// プレイシーンデータロード
	m_datas.insert({ "Play0" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/PlayScene.msgpack") });
	// プレイシーンデータロード
	m_datas.insert({ "Play1" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/PlayScene1.msgpack") });
	// プレイシーンデータロード
	m_datas.insert({ "Play2" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/Binary/PlayScene2.msgpack") });
}

