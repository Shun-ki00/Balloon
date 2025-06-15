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
/// データのロード
/// </summary>
/// <param name="key">キー</param>
/// <param name="path">ファイルパス</param>
void GameConfig::LoadJsonFile(const std::string& key, const std::string& path)
{
	// ファイルを読み込む
	std::ifstream file(path);

	// Jsonに変換
	nlohmann::json j;
	file >> j;

	// ファイルを閉じる
	file.close();

	// データの格納
	m_datas.insert({ key , j });
}