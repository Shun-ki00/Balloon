#pragma once

class CommonResources;
class Resources;

class Sea
{
private:
	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4    TessellationFactor;
	};

public:
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
	void CreateConstantBuffer();

	// ブレンドステートの作成
	void CreateBlendState(ID3D11Device1* device);
	// 深度ステンシルステートの作成
	void CreateDepthStencilState(ID3D11Device1* device);
	// ラスタライザーステートの作成
	void CreateRasterizerState(ID3D11Device1* device);

private:

	// タイム
	float m_time;
	// テッセレーション
	float m_index;

	// 共有リソース
	CommonResources* m_commonResources;
	// コモンステート
	DirectX::CommonStates* m_commonStates;

	//	コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
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

	ID3D11ShaderResourceView* m_NormalTexture;
	ID3D11ShaderResourceView* m_CubeTexture;

	// ブレンドステート
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;
	// 深度ステンシルステート
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	// ラスタライザーステート
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;


	// 定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;
	// 波パラメータ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_waveConstantBuffer;



	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;

};