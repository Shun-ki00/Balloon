// ============================================
// 
// ファイル名: ModelResources.h
// 概要: ModelResources.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Framework/Resources/ResourceKeys.h"

class ModelResources
{
public:
	// テクスチャを取得する
	DirectX::Model* GetModel(ModelKeyID id);

public:
	ModelResources(const ModelResources&) = delete;             // コピー禁止
	ModelResources& operator=(const ModelResources&) = delete;  // コピー代入禁止
	ModelResources(const ModelResources&&) = delete;            // ムーブ禁止
	ModelResources& operator=(const ModelResources&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static ModelResources* GetInstance()
	{
		static ModelResources instance;
		return &instance;
	}
	// リソースをロードする
	void LoadResource(const nlohmann::json& data);

private:
	// コンストラクタ
	ModelResources();
	// デストラクタ
	~ModelResources() = default;

private:

	// モデルのリスト
	std::unordered_map<std::string, std::unique_ptr<DirectX::Model>> m_models;
};