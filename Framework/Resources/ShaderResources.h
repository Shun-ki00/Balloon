// ============================================
// 
// ファイル名: ShaderResources.h
// 概要: ShaderResources.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Framework/Resources/ResourceKeys.h"

class ShaderResources
{
public:
	//	UIインプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> UI_INPUT_LAYOUT;
	//	海インプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> SEA_INPUT_LAYOUT;
public:
	// UI インプットレイアウトを取得する
	ID3D11InputLayout* GetUIinputLayout() { return m_UIinputLayout.Get(); }
	// 海 インプットレイアウトを取得
	ID3D11InputLayout* GetSeaInputLayout() { return m_SeaInputLayout.Get(); }
	// 物理ベースレンダリング インプットレイアウトを取得
	ID3D11InputLayout* GetPBRLitInputLayout() { return m_PBRLitInputLayout.Get(); }
	// パーティクル インプットレイアウトを取得
	ID3D11InputLayout* GetParticleInputLayout() { return m_particleInputLayout.Get(); }

	// 頂点シェーダーを取得する
	ID3D11VertexShader* GetVertexShader(VS_ID id);
	// ハルシェーダーを取得する
	ID3D11HullShader* GetHullShader(HS_ID id);
	// ドメインシェーダーを取得する
	ID3D11DomainShader* GetDomainShader(DS_ID id);
	// ジオメトリシェーダーを取得する
	ID3D11GeometryShader* GetGeometryShader(GS_ID id);
	// ピクセルシェーダーを取得する
	ID3D11PixelShader* GetPixelShader(PS_ID id);

public:
	ShaderResources(const ShaderResources&) = delete;             // コピー禁止
	ShaderResources& operator=(const ShaderResources&) = delete;  // コピー代入禁止
	ShaderResources(const ShaderResources&&) = delete;            // ムーブ禁止
	ShaderResources& operator=(const ShaderResources&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static ShaderResources* GetInstance()
	{
		static ShaderResources instance;
		return &instance;
	}
	// リソースをロードする
	void LoadResource(const nlohmann::json& data);

private:
	// コンストラクタ
	ShaderResources();

private:
	// 入力レイアウト UI
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_UIinputLayout;
	// 入力レイアウト Sea
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_SeaInputLayout;
	// 入力レイアウト PBRLit
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_PBRLitInputLayout;
	// 入力レイアウト Particle
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_particleInputLayout;

	// 頂点シェーダー
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11VertexShader>> m_vertexShaders;
	// ハルシェーダー
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11HullShader>> m_hullShaders;
	// ドメインシェーダー
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11DomainShader>> m_domainShaders;
	// ジオメトリシェーダー
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11GeometryShader>> m_geometryShaders;
	// ピクセルシェーダー
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11PixelShader>> m_pixelShaders;
};