#pragma once
#include "Game/Buffers/ConstantBuffer.h"

class CommonResources;
class Resources;

class Sea
{
private:

	// 変換用定数バッファ
	struct TransformConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4    cameraPosition;
		DirectX::SimpleMath::Vector4    TessellationFactor;
		DirectX::SimpleMath::Vector4    color;
	};

	// インスタンスデータ
	struct InstanceData
	{
		DirectX::SimpleMath::Vector4 offset;
	};


	// 海のノイズ用の定数バッファ
	struct SeaNoiseConstBuffer
	{
		float flowVelocity;    // 流れる力
		float swingSpeed;      // 左右の振れ
		float fnUVPath1;       // ノイズの影響 (x軸)
		float fnUVPath2;       // ノイズの影響 (y軸)

		float fnUVPower;       // UVスケール
		float fnOctaves;       // ノイズのオクターブ数
		float fnPersistence;   // ノイズ持続度
		float padding;         // パディング
	};

	// ゲルストナ波の定数バッファ
	struct GerstnerWaveConstBuffer
	{
		// Wave1
		float active1, direction1X, direction1Z, amplitude1;
		float waveLength1, speed1, qRatio1, pad1;

		// Wave2
		float active2, direction2X, direction2Z, amplitude2;
		float waveLength2, speed2, qRatio2, pad2;

		// Wave3
		float active3, direction3X, direction3Z, amplitude3;
		float waveLength3, speed3, qRatio3, pad3;
	};

public:

	// 色を設定する
	void SetColor(const DirectX::SimpleMath::Vector4& color) { m_color = color; }

	// コンストラクタ
	Sea();
	// デストラクタ
	~Sea() = default;

public:

	// 初期化処理
	void Initialize();
	// 描画処理
	void Render();

private:

	// 定数バッファの作成
	void CreateConstBuffer();
	// 頂点の生成
	void CreateVertexBuffer();
	// インスタンスデータの作成
	void CreateInstanceData();

private:

	// タイム
	float m_time;
	
	// 共有リソース
	CommonResources* m_commonResources;
	// コモンステート
	DirectX::CommonStates* m_commonStates;
	// コンテキスト
	ID3D11DeviceContext1* m_context;
	// デバイス
	ID3D11Device1* m_device;
	// リソース
	Resources* m_resources;

	// 入力レイアウト
	ID3D11InputLayout* m_inputLayout;
	// 頂点シェーダー
	ID3D11VertexShader* m_vertexShader;
	// ハルシェーダー
	ID3D11HullShader* m_hullShader;
	// ドメインシェーダー
	ID3D11DomainShader* m_domainShader;
	// ピクセルシェーダー
	ID3D11PixelShader* m_pixelShader;

	// テクスチャ
	ID3D11ShaderResourceView* m_texture;

	// Transform定数バッファ
	std::unique_ptr<ConstantBuffer<TransformConstBuffer>> m_transformBuffer;
	// 海ノイズ定数バッファ
	std::unique_ptr<ConstantBuffer<SeaNoiseConstBuffer>> m_seaNoiseBuffer;
	// 波定数バッファ
	std::unique_ptr<ConstantBuffer<GerstnerWaveConstBuffer>> m_gerstnerWaveBuffer;

	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	// インスタンスバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_instanceStructuredBuffer;
	// インスタンスのシェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_instanceSRV;

	// 色
	DirectX::SimpleMath::Vector4 m_color;
};