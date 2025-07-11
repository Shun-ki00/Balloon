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
	std::ifstream file("Resources/Json/Binary/GameResourceData.msgpack", std::ios::binary);
	
	// バイナリ内容を全読み込み
	std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});

	// MessagePack から JSON へ変換
	nlohmann::json data = nlohmann::json::from_msgpack(buffer);

	// データを格納
	m_data = data;

	// 時間測定用のエイリアス
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = Clock::time_point;
	using Duration = std::chrono::duration<float>;

	// --- 計算開始 ---
	TimePoint startTime = Clock::now();

	/*this->LoadModel();
	this->LoadShader();
	this->LoadTexture();
	this->LoadGameData();*/

	// テクスチャをロードする
	std::thread texture(&Resources::LoadTexture, this);
	// モデルをロードする
	std::thread model(&Resources::LoadModel, this);
	// ゲームデータをロードする
	std::thread gameData(&Resources::LoadGameData, this);
	// シェーダーをロードする
	std::thread shader(&Resources::LoadShader, this);
	
	// ロードが終わるまで待つ
	model.join();
	texture.join();
	shader.join();
	gameData.join();

	// --- 計算終了 ---
	TimePoint endTime = Clock::now();
	Duration elapsed = endTime - startTime;
	// 計算時間を取得
	m_time = elapsed.count();

	// 初期化処理以外必要ないのでデータを空にする
	m_data = {};
}
