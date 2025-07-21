// ============================================
// 
// ファイル名: CascadedShadowMap.h
// 概要: CascadedShadowMap.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Framework/Microsoft/RenderTexture.h"
#include "Framework/DepthStencil.h"
#include <Model.h>

// 前方宣言
class Transform;
class DepthStencil;
class CommonResources;

namespace DX
{
	class RenderTexture;
}

// CSM
class CascadedShadowMap
{
private:
	const float SHADOWMAP_SIZE = 1120.0f;

public:
	// 現在のカメラのTransformを設定する
	void SetCameraTrasform(Transform* transform) { m_cameraTransform = transform; }
	// 影のシェーダーリソースを取得する
	ID3D11ShaderResourceView* GetShadowShaderResourceView() const { return m_shadowMapRT->GetShaderResourceView(); }
	// 定数バッファを取得する
	ID3D11Buffer* GetBuffer() const { return m_DLBuffer.Get(); }

public:
	// コンストラクタ
	CascadedShadowMap();
	// デストラクタ
	~CascadedShadowMap() = default;

public:

	// 初期化処理
	void Initialize();
	// 描画処理
	void Draw(DirectX::Model* model ,ID3D11DeviceContext1* context, DirectX::CommonStates* states,
		Transform* transform);

	void Begin();
	void End();



private:
	// 共有リソース
	CommonResources* m_commonResources;

	// カスケード
	int m_cascadedIndex;

	// ディレクショナルライトTransform
	std::unique_ptr<Transform> m_transform;
	// ディレクショナルライトプロジェクション行列
	DirectX::SimpleMath::Matrix m_lightProjectionMatrix;
	// ディレクショナルライトビュー行列
	DirectX::SimpleMath::Matrix m_lightViewMatrix;
	// ディレクショナルライトバッファ用のバッファオブジェクト
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_DLBuffer;

	// 現在のカメラのTrasform
	Transform* m_cameraTransform;

	// シャドウマップ用（レンダーテクスチャ）
	std::unique_ptr<DX::RenderTexture> m_shadowMapRT;
	// シャドウマップ用（デプスステンシル）
	std::unique_ptr<DepthStencil> m_shadowMapDS;
	// 頂点シェーダ
	ID3D11VertexShader* m_shadowVS;
	// ピクセルシェーダ
	ID3D11PixelShader*  m_shadowPS;
	// サンプラ
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;
};