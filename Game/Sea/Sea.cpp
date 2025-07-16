#include "pch.h"
#include "Game/Sea/Sea.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include "Game/Buffers/ConstantBuffer.h"

/// <summary>
/// コンストラクタ
/// </summary>
Sea::Sea()
	:
	m_inputLayout{},
	m_vertexShader{},
	m_hullShader{},
	m_domainShader{},
	m_pixelShader{},
	m_texture{},
	m_color{}
{
	m_commonResources = CommonResources::GetInstance();
	m_resources       = Resources::GetInstance();
	m_commonStates    = CommonResources::GetInstance()->GetCommonStates();
	m_context         = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	m_device          = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
}

/// <summary>
/// 初期化処理
/// </summary>
void Sea::Initialize()
{
	// シェーダーを取得する
	m_vertexShader = m_resources->GetShaderResources()->GetVertexShader(VS_ID::Sea_VS);
	m_hullShader   = m_resources->GetShaderResources()->GetHullShader(HS_ID::Sea_HS);
	m_domainShader = m_resources->GetShaderResources()->GetDomainShader(DS_ID::Sea_DS);
	m_pixelShader  = m_resources->GetShaderResources()->GetPixelShader(PS_ID::Sea_PS);
	// インプットレイアウトを取得
	m_inputLayout = m_resources->GetShaderResources()->GetSeaInputLayout();

	// テクスチャを取得する
	m_texture = m_resources->GetTextureResources()->GetTexture(TextureKeyID::Sea);

	// 時間測定用のエイリアス
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = Clock::time_point;
	using Duration = std::chrono::duration<float>;

	// --- 計算開始 ---
	TimePoint startTime = Clock::now();

	// 頂点バッファの作成
	this->CreateVertexBuffer();
	// インスタンスデータの作成
	this->CreateInstanceData();
	// 定数バッファの作成
	this->CreateConstBuffer();

	// --- 計算終了 ---
	TimePoint endTime = Clock::now();
	Duration elapsed = endTime - startTime;

	// 計算時間を取得
	m_time = elapsed.count();

	// 色を設定
	m_color = DirectX::SimpleMath::Vector4::One;

	// タイム初期化
	m_time = 0.0f;
}

/// <summary>
/// 描画処理
/// </summary>
void Sea::Render()
{
	// タイマーの更新
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();
	m_time += elapsedTime;

	// ワールド行列作成
	DirectX::SimpleMath::Matrix world = 
		DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3::Down * 20.0f);

	DirectX::SimpleMath::Vector3 position = m_commonResources->GetCameraTransform()->GetLocalPosition();

	//	シェーダーに渡す追加のバッファを作成する。
	TransformConstBuffer buffer;
	buffer.matView = m_commonResources->GetViewMatrix().Transpose();
	buffer.matProj = m_commonResources->GetProjectionMatrix().Transpose();
	buffer.matWorld = world.Transpose();
	buffer.cameraPosition = { position.x , position.y , position.z ,0.0f };
	buffer.TessellationFactor = DirectX::SimpleMath::Vector4(0.0f, m_time, 2.0f, 0.0f);
	buffer.color = m_color;
	// 定数バッファの更新
	m_transformBuffer->Update(m_context, buffer);

	// 入力レイアウトを設定
	m_context->IASetInputLayout(m_inputLayout);

	// ブレンドステートを設定 (半透明描画用)
	m_context->OMSetBlendState(m_commonStates->NonPremultiplied(), nullptr, 0xFFFFFFFF);
	//	深度バッファに書き込み参照する
	m_context->OMSetDepthStencilState(m_commonStates->DepthRead(), 0);
	// ラスタライザーステートの設定
	m_context->RSSetState(m_commonStates->CullCounterClockwise());

	// 頂点バッファを設定
	ID3D11Buffer* buffers[] = { m_vertexBuffer.Get() };
	UINT stride[] = { sizeof(DirectX::VertexPositionTexture) };
	UINT offset[] = { 0 };
	m_context->IASetVertexBuffers(0, 1, buffers, stride, offset);

	// プリミティブトポロジー（三角形リスト）
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[3] = { m_transformBuffer->GetBuffer() , m_seaNoiseBuffer->GetBuffer() ,m_gerstnerWaveBuffer->GetBuffer()};
	// スロット1から3に一括バインド
	m_context->VSSetConstantBuffers(0, 3, cb);
	m_context->HSSetConstantBuffers(0, 3, cb);
	m_context->DSSetConstantBuffers(0, 3, cb);
	m_context->PSSetConstantBuffers(0, 3, cb);

	// サンプラーステートをピクセルシェーダーに設定
	ID3D11SamplerState* sampler[1] = { m_commonStates->LinearWrap() };
	m_context->PSSetSamplers(0, 1, sampler);


	//	シェーダをセットする
	m_context->VSSetShader(m_vertexShader, nullptr, 0);
	m_context->HSSetShader(m_hullShader  , nullptr, 0);
	m_context->DSSetShader(m_domainShader, nullptr, 0);
	m_context->PSSetShader(m_pixelShader , nullptr, 0);

	// テクスチャの設定
	ID3D11ShaderResourceView* tex[1] = { m_texture };
	m_context->PSSetShaderResources(0, 1, tex);

	// インスタンスデータの設定
	ID3D11ShaderResourceView* srvs[] = { m_instanceSRV.Get() };
	m_context->VSSetShaderResources(1, 1, srvs);

	// ドローコール
	UINT instanceCount = static_cast<UINT>(700 * 700);
	m_context->DrawInstanced(4, instanceCount, 0, 0);

	//	シェーダの登録を解除しておく
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->HSSetShader(nullptr, nullptr, 0);
	m_context->DSSetShader(nullptr, nullptr, 0);
	m_context->PSSetShader(nullptr, nullptr, 0);

	// テクスチャリソースを解放
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	m_context->PSSetShaderResources(0, 1, nullsrv);
	m_context->VSSetShaderResources(1, 1, nullsrv);
}


/// <summary>
/// 頂点バッファの作成
/// </summary>
void Sea::CreateVertexBuffer()
{
	using namespace DirectX::SimpleMath;

	std::vector<DirectX::VertexPositionTexture> vertices =
	{
		{Vector3(-5.0f , 0.0f , -5.0f),Vector2(0.0f ,0.0f)}, // 左上
		{Vector3( 5.0f , 0.0f , -5.0f),Vector2(1.0f ,0.0f)}, // 右上
		{Vector3(-5.0f , 0.0f ,  5.0f),Vector2(0.0f ,1.0f)}, // 左下
		{Vector3( 5.0f , 0.0f ,  5.0f),Vector2(1.0f ,1.0f)}, // 左下
	};

	// 頂点バッファの作成
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(DirectX::VertexPositionTexture) * vertices.size());
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexBufferData = {};
	vertexBufferData.pSysMem = vertices.data();

	m_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, m_vertexBuffer.ReleaseAndGetAddressOf());
}

void Sea::CreateInstanceData()
{
	constexpr int width = 700;
	constexpr int height = 700;
	constexpr float tileSize = 10.0f; // 各板ポリの幅

	// インスタンスデータの配列作成
	std::vector<InstanceData> instanceData;
	instanceData.reserve(width * height);

	// 原点を中心に配置するためのオフセット
	const float offsetX = (width - 1) * tileSize * 0.5f;
	const float offsetZ = (height - 1) * tileSize * 0.5f;

	// オフセット値を計算し格納していく
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			float worldX = x * tileSize - offsetX;
			float worldZ = y * tileSize - offsetZ;

			InstanceData instance = {};
			instance.offset = DirectX::SimpleMath::Vector4(worldX, 0.0f, worldZ,0.0f);
			instanceData.push_back(instance);
		}
	}

	// StructuredBuffer 用バッファ作成
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = UINT(sizeof(InstanceData) * instanceData.size());
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.StructureByteStride = sizeof(InstanceData);
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = instanceData.data();

	m_device->CreateBuffer(&desc, &initData, m_instanceStructuredBuffer.ReleaseAndGetAddressOf());

	// Shader Resource View を作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	srvDesc.Buffer.ElementWidth = static_cast<UINT>(instanceData.size());

	m_device->CreateShaderResourceView(m_instanceStructuredBuffer.Get(), &srvDesc, m_instanceSRV.ReleaseAndGetAddressOf());
}

/// <summary>
/// 定数バッファの作成
/// </summary>
void Sea::CreateConstBuffer()
{
	// Transformの定数バッファの作成
	m_transformBuffer = std::make_unique<ConstantBuffer<TransformConstBuffer>>();
	// 初期化
	m_transformBuffer->Initialize(m_device);

	// 海ノイズの定数バッファの作成
	m_seaNoiseBuffer = std::make_unique<ConstantBuffer<SeaNoiseConstBuffer>>();
	// 初期化
	m_seaNoiseBuffer->Initialize(m_device,UpdateStrategy::UPDATE_SUB_RESOURCE);

	// 波の定数バッファの作成
	m_gerstnerWaveBuffer = std::make_unique<ConstantBuffer<GerstnerWaveConstBuffer>>();
	// 初期化
	m_gerstnerWaveBuffer->Initialize(m_device, UpdateStrategy::UPDATE_SUB_RESOURCE);
	

	GerstnerWaveConstBuffer waveParams =
	{
		// 大波（うねり） - ゆったりだけど存在感あり
	   0.8f, -0.5f, 0.4f, 0.6f,
	   11.0f, 1.0f, 0.3f, 0.0f,

	   // 中波（干渉）
	   0.6f, 0.4f, -0.5f, 0.4f,
	   6.5f, 1.0f, 0.35f, 0.0f,

	   // 小波（さざ波）
	   0.4f, -0.25f, -0.6f, 0.25f,
	   2.8f, 1.2f, 0.4f, 0.0f
	};
	SeaNoiseConstBuffer seaNoise =
	{
		0.1f,
		0.01f,
		0.08f,
		0.06f,
		25.0f,
		10.0f,
		0.6f,
		0.01f
	};
	m_gerstnerWaveBuffer->Update(m_context, waveParams);
	m_seaNoiseBuffer->Update(m_context, seaNoise);

}