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
	// タイトルシーンのデータをロード
	this->LoadBinaryJsonFile("Title", "Resources/Json/TitleScene.msgpack");
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

/// <summary>
/// バイナリデータのJSONをロードする
/// </summary>
/// <param name="key"></param>
/// <param name="path"></param>
void GameConfig::LoadBinaryJsonFile(const std::string& key, const std::string& path)
{
	// バイナリとして開く
	std::ifstream file(path, std::ios::binary);
	if (!file)
	{
		throw std::runtime_error("ファイルが開けません: " + path);
	}

	// バイナリ内容を全読み込み
	std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});

	// MessagePack から JSON へ変換
	nlohmann::json j = nlohmann::json::from_msgpack(buffer);

	// データ格納
	m_datas.insert({ key , j });
}