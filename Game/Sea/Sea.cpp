#include "pch.h"
#include "Game/Sea/Sea.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"


Sea::Sea()
	:
	m_inputLayout{},
	m_vertexShader{},
	m_hullShader{},
	m_domainShader{},
	m_pixelShader{},
	m_texture{},
	m_blendState{},
	m_depthStencilState{},
	m_rasterizerState{}
{
	m_commonResources = CommonResources::GetInstance();
	m_resources       = Resources::GetInstance();
	m_commonStates    = CommonResources::GetInstance()->GetCommonStates();
	m_context         = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	m_device          = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
}


void Sea::Initialize()
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	m_states = std::make_unique<DirectX::DX11::CommonStates>(device);

	// シェーダーを取得する
	m_vertexShader = m_resources->GetShaderResources()->GetVertexShader(VS_ID::Sea_VS);
	m_hullShader   = m_resources->GetShaderResources()->GetHullShader(HS_ID::Sea_HS);
	m_domainShader = m_resources->GetShaderResources()->GetDomainShader(DS_ID::Sea_DS);
	m_pixelShader  = m_resources->GetShaderResources()->GetPixelShader(PS_ID::Sea_PS);
	// インプットレイアウトを取得
	m_inputLayout = m_resources->GetShaderResources()->GetSeaInputLayout();

	// テクスチャを取得する
	m_texture = m_resources->GetTextureResources()->GetTexture(TextureKeyID::Sea);
	m_NormalTexture = m_resources->GetTextureResources()->GetTexture(TextureKeyID::Wood);
	m_CubeTexture = m_resources->GetTextureResources()->GetTexture(TextureKeyID::CubeMap);


	this->CreateConstantBuffer();

	// 頂点データを定義（4つの制御点）
	const float SIZE = 30.0f;

	const int GRID_X = 8;
	const int GRID_Z = 4;
	const int VERTEX_COUNT = GRID_X * GRID_Z;

	DirectX::VertexPositionTexture vertex[VERTEX_COUNT];

	for (int z = 0; z < GRID_Z; ++z)
	{
		for (int x = 0; x < GRID_X; ++x)
		{
			int index = z * GRID_X + x;
			float fx = -SIZE + (2 * SIZE) * (float)x / (GRID_X - 1);
			float fz = SIZE - (2 * SIZE) * (float)z / (GRID_Z - 1);
			vertex[index] = {
				DirectX::XMFLOAT3(fx, 0.0f, fz),
				DirectX::XMFLOAT2((float)x / (GRID_X - 1), (float)z / (GRID_Z - 1))
			};
		}
	}


	// 頂点バッファの説明
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(DirectX::VertexPositionTexture) * _countof(vertex); // 頂点データ全体のサイズ
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;

	// 頂点データの初期化
	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = vertex;

	device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);

	// ブレンドステートの作成
	CreateBlendState(device);
	// 深度ステンシルステートの作成
	CreateDepthStencilState(device);
	// ラスタライザーステートの作成
	CreateRasterizerState(device);

	// 細分度
	m_index = 1.0f;
	// タイム初期化
	m_time = 0.0f;
}

void Sea::Render()
{
	// タイマーの更新
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();
	m_time += elapsedTime;
	// 細分度設定
	m_index = 40.0f;

	// ワールド行列作成
	DirectX::SimpleMath::Matrix world = 
		DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3::Down * 20);

	//	シェーダーに渡す追加のバッファを作成する。
	ConstBuffer cbuff;
	cbuff.matView = m_commonResources->GetViewMatrix().Transpose();
	cbuff.matProj = m_commonResources->GetProjectionMatrix().Transpose();
	cbuff.matWorld = world.Transpose();
	cbuff.TessellationFactor = DirectX::SimpleMath::Vector4(m_index, m_time, 2.0f, 0.0f);

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	m_context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// 入力レイアウトを設定
	m_context->IASetInputLayout(m_inputLayout);

	// 頂点バッファを設定
	ID3D11Buffer* buffers[] = { m_vertexBuffer.Get() };
	UINT stride[] = { sizeof(DirectX::VertexPositionTexture) };
	UINT offset[] = { 0 };
	m_context->IASetVertexBuffers(0, 1, buffers, stride, offset);

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[2] = { m_constantBuffer.Get() , m_waveConstantBuffer.Get()};
	// スロット1から3に一括バインド
	m_context->VSSetConstantBuffers(0, 2, cb);
	m_context->HSSetConstantBuffers(0, 2, cb);
	m_context->DSSetConstantBuffers(0, 2, cb);
	m_context->PSSetConstantBuffers(0, 2, cb);

	// サンプラーステートをピクセルシェーダーに設定
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	m_context->PSSetSamplers(0, 1, sampler);

	// ブレンドステートを設定 (半透明描画用)
	//m_context->OMSetBlendState(m_blendState.Get(), nullptr, 0xFFFFFFFF);

	// プリミティブトポロジーを設定
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST);

	//	深度バッファに書き込み参照する
	m_context->OMSetDepthStencilState(m_states->DepthDefault(), 0);
	// ラスタライザーステートの設定
	m_context->RSSetState(m_rasterizerState.Get());


	//	シェーダをセットする
	m_context->VSSetShader(m_vertexShader, nullptr, 0);
	m_context->HSSetShader(m_hullShader, nullptr, 0);
	m_context->DSSetShader(m_domainShader, nullptr, 0);
	m_context->PSSetShader(m_pixelShader, nullptr, 0);

	// テクスチャの設定
	std::vector<ID3D11ShaderResourceView*> tex = {
		m_texture,
		m_NormalTexture,
		m_CubeTexture,
	};

	m_context->VSSetShaderResources(0, (UINT)tex.size(), tex.data());
	m_context->PSSetShaderResources(0, (UINT)tex.size(), tex.data());

	// 描画コール
	m_context->Draw(32, 0);

	//	シェーダの登録を解除しておく
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->HSSetShader(nullptr, nullptr, 0);
	m_context->DSSetShader(nullptr, nullptr, 0);
	m_context->PSSetShader(nullptr, nullptr, 0);

	// テクスチャリソースを解放
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	m_context->PSSetShaderResources(0, 1, nullsrv);
}

void Sea::CreateConstantBuffer()
{
	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(ConstBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	m_device->CreateBuffer(&desc, nullptr, m_constantBuffer.ReleaseAndGetAddressOf());

	WaveParams waveParams =
	{
		// 大波（高振幅・高速）
		1.0f, -0.85f,  0.55f, 1.8f,   // active, dirX, dirZ, amplitude
		12.0f, 2.5f, 0.75f, 0.0f,     // waveLength, speed, qRatio, pad

		// 中波（対抗方向・中振幅）
		1.0f, 0.6f, -0.6f, 0.9f,
		6.0f, 2.0f, 0.55f, 0.0f,

		// 細波（鋭い風波）
		1.0f, 0.3f, -1.0f, 0.45f,
		2.2f, 1.8f, 0.65f, 0.0f
	};


	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(WaveParams);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	m_device->CreateBuffer(&desc, nullptr, &m_waveConstantBuffer);

	m_context->UpdateSubresource(m_waveConstantBuffer.Get(), 0, nullptr, &waveParams, 0, 0);

}



/// <summary>
/// ブレンドステートの作成
/// </summary>
/// <param name="device">デバイス</param>
void Sea::CreateBlendState(ID3D11Device1* device)
{
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = FALSE;  // カバレッジをアルファに基づいて有効化する
	blendDesc.IndependentBlendEnable = FALSE; // 複数のレンダーターゲットを独立して設定する

	D3D11_RENDER_TARGET_BLEND_DESC rtBlendDesc = {};
	rtBlendDesc.BlendEnable = TRUE;              // ブレンドを有効化
	rtBlendDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;        // ソースのアルファ
	rtBlendDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;    // 逆アルファ
	rtBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;           // 加算ブレンド
	rtBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;              // アルファ値のソース
	rtBlendDesc.DestBlendAlpha = D3D11_BLEND_ZERO;             // アルファ値のデスティネーション
	rtBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;           // アルファ値の加算
	rtBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // RGBA全てを有効

	blendDesc.RenderTarget[0] = rtBlendDesc;

	// カスタムブレンドステートを作成

	device->CreateBlendState(&blendDesc, &m_blendState);
}

/// <summary>
/// 深度ステンシルステートの作成
/// </summary>
/// <param name="device">デバイス</param>
void Sea::CreateDepthStencilState(ID3D11Device1* device)
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = TRUE;                          // 深度テストを有効化
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 深度バッファの書き込みを有効化
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;      // 深度テスト条件 (小さい場合のみ描画)
	depthStencilDesc.StencilEnable = FALSE;                       // ステンシルテストを無効化

	// 深度ステンシルステートを作成
	device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
}

/// <summary>
/// ラスタライザーステートの作成
/// </summary>
/// <param name="device">デバイス</param>
void Sea::CreateRasterizerState(ID3D11Device1* device)
{
	D3D11_RASTERIZER_DESC rasterDesc = {};
	rasterDesc.FillMode = D3D11_FILL_WIREFRAME;      // 塗りつぶし (または D3D11_FILL_WIREFRAME)D3D11_FILL_SOLID
	rasterDesc.CullMode = D3D11_CULL_FRONT;       // カリングなし (または D3D11_CULL_FRONT / D3D11_CULL_BACK)
	rasterDesc.FrontCounterClockwise = FALSE;    // 時計回りの頂点順序を表面として認識
	rasterDesc.DepthClipEnable = TRUE;           // 深度クリッピングを有効化
	// ラスタライザーステートの作成
	device->CreateRasterizerState(&rasterDesc, &m_rasterizerState);
}