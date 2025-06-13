// ============================================
// 
// ファイル名: TextureResources.h
// 概要: TextureResources.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================

#pragma once
#include "Framework/Resources/ResourceKeys.h"


class TextureResources
{
public:
	// テクスチャを取得する
	ID3D11ShaderResourceView* GetTexture(TextureKeyID id);

	// テクスチャサイズを取得する
	void GetTextureSize(const TextureKeyID& id, float& width, float& height);


public:
	TextureResources(const TextureResources&) = delete;             // コピー禁止
	TextureResources& operator=(const TextureResources&) = delete;  // コピー代入禁止
	TextureResources(const TextureResources&&) = delete;            // ムーブ禁止
	TextureResources& operator=(const TextureResources&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static TextureResources* GetInstance()
	{
		static TextureResources instance;
		return &instance;
	}
	// リソースをロードする
	void LoadResource(const nlohmann::json& data);

private:
	// コンストラクタ
	TextureResources();
	// デストラクタ
	~TextureResources() = default;

private:

	// デバイス
	ID3D11Device1* m_device;

	// テクスチャリスト
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textures;
};