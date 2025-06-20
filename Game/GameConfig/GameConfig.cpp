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
	// タイトルシーンデータロード
	m_datas.insert({ "Title" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/TitleScene.msgpack") });
	// ゲームクリアシーンデータロード
	m_datas.insert({ "Clear" , JsonUtilities::LoadBinaryJsonFile("Resources/Json/GameClearScene.msgpack") });
}

