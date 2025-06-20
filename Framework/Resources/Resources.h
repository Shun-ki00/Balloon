// ============================================
// 
// ファイル名: Resources.h
// 概要: Resources.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================

#pragma once
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"
#include "Game/GameConfig/GameConfig.h"

class CommonResources;

class ModelResources;
class ShaderResources;
class TextureResources;

// Resourcesクラスを定義する
class Resources
{
public:
	// 簡易的な UTF-8 → UTF-16 変換
	static std::wstring ConvertToWString(const std::string& str) {
		return std::wstring(str.begin(), str.end()); 
	};


	static std::wstring GetDirectoryFromJSON(const nlohmann::json& data, const std::string& key) {
		if (data.contains(key) && data[key].is_string()) {
			return Resources::ConvertToWString(data[key]);
		}
		return L"";  // fallback: 空文字
	}

public:
	// モデルリソースを取得する
	ModelResources* GetModelResources() { return m_modelResources; }
	// シェーダーリソースを取得する
	ShaderResources* GetShaderResources() { return m_shaderResources; }
	// テクスチャリソースを取得する
	TextureResources* GetTextureResources() { return m_textureResources; }

public:
	Resources(const Resources&) = delete;             // コピー禁止
	Resources& operator=(const Resources&) = delete;  // コピー代入禁止
	Resources(const Resources&&) = delete;            // ムーブ禁止
	Resources& operator=(const Resources&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static Resources* GetInstance()
	{
		static Resources instance;
		return &instance;
	}
	// リソースをロードする
	void LoadResource();

private:
	// コンストラクタ
	Resources();

	// モデルのロード
	void LoadModel() { m_modelResources->LoadResource(m_data); }
	// シェーダーのロード
	void LoadShader()  { m_shaderResources->LoadResource(m_data); }
	// テクスチャのロード
	void LoadTexture() { m_textureResources->LoadResource(m_data); }
	// ゲームデータをロード
	void LoadGameData() { GameConfig::GetInstance()->LoadJsonFile(); }

private:
	// モデルリソース
	ModelResources* m_modelResources;
	// シェーダーリソース
	ShaderResources* m_shaderResources;
	// テクスチャリソース
	TextureResources* m_textureResources;

	// Jsonデータ
	nlohmann::json m_data;
};