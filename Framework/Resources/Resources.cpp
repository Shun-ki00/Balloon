// ============================================
// 
// ファイル名: Resources.cpp
// 概要: 各種リソースの管理と読み込みを行うクラス（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Framework/Resources/Resources.h"
#include <iostream>
#include <fstream>
#include <thread>
// 各リソース
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"




/// <summary>
/// コンストラクタ
/// </summary>
Resources::Resources()
{
	// インスタンスを取得する
	m_modelResources    = ModelResources::GetInstance();
	m_shaderResources   = ShaderResources::GetInstance();
	m_textureResources  = TextureResources::GetInstance();
}


/// <summary>
/// 各リソースのロード
/// </summary>
void Resources::LoadResource()
{
	// バイナリとして開く
	std::ifstream file("Resources/Json/GameResourceData.msgpack", std::ios::binary);
	
	// バイナリ内容を全読み込み
	std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});

	// MessagePack から JSON へ変換
	nlohmann::json data = nlohmann::json::from_msgpack(buffer);

	// データを格納
	m_data = data;

	// モデルをロードする
	std::thread model(&Resources::LoadModel, this);
	// シェーダーをロードする
	std::thread shader(&Resources::LoadShader, this);
	// テクスチャをロードする
	std::thread texture(&Resources::LoadTexture, this);
	// ゲームデータをロードする
	std::thread gameData(&Resources::LoadGameData, this);

	// ロードが終わるまで待つ
	model.join();
	texture.join();
	shader.join();
	gameData.join();

	// 初期化処理以外必要ないのでデータを空にする
	m_data = {};
}
