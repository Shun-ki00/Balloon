// ============================================
// 
// ファイル名: SkyBox.h
// 概要: SkyBox.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once

class SkyBox
{
public:
	// コンストラクタ
	SkyBox();
	// デストラクタ
	~SkyBox() = default;

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(DirectX::SimpleMath::Matrix view , DirectX::SimpleMath::Matrix projection);
	// 描画処理
	void Render(ID3D11DeviceContext1* context , DirectX::CommonStates* states);

	// テクスチャを変更
	void SetDayProgress(float progress) { m_dayProgress = progress; }

private:

	// スカイボックスモデル
	std::unique_ptr<DirectX::GeometricPrimitive> m_skyboxModel;

	// 頂点シェーダー
	ID3D11VertexShader*   m_vertexShader;
	// ピクセルシェーダー
	ID3D11PixelShader*    m_pixelShader;

	// キューブマップ
	ID3D11ShaderResourceView* m_cubemap;
	// キューブマップ　夕方
	ID3D11ShaderResourceView* m_eveningCubeMap;

	// 定数バッファ用のバッファオブジェクト
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	// 回転角
	float m_angle;
	// 一日の進行度
	float m_dayProgress;

};