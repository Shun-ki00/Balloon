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
	m_texture{}
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
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// シェーダーを取得する
	m_vertexShader = m_resources->GetShaderResources()->GetVertexShader(VS_ID::Sea_VS);
	m_hullShader   = m_resources->GetShaderResources()->GetHullShader(HS_ID::Sea_HS);
	m_domainShader = m_resources->GetShaderResources()->GetDomainShader(DS_ID::Sea_DS);
	m_pixelShader  = m_resources->GetShaderResources()->GetPixelShader(PS_ID::Sea_PS);
	// インプットレイアウトを取得
	m_inputLayout = m_resources->GetShaderResources()->GetSeaInputLayout();

	// テクスチャを取得する
	m_texture = m_resources->GetTextureResources()->GetTexture(TextureKeyID::Sea);

	// 定数バッファの更新
	this->CreateBuffer();

	// 細分度
	m_index = 1.0f;
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
	// 細分度設定
	m_index = 40.0f;

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
	buffer.TessellationFactor = DirectX::SimpleMath::Vector4(m_index, m_time, 2.0f, 0.0f);
	// 定数バッファの更新
	m_transformBuffer->Update(m_context, buffer);

	// 入力レイアウトを設定
	m_context->IASetInputLayout(m_inputLayout);

	// 頂点バッファを設定
	ID3D11Buffer* buffers[] = { m_vertexBuffer.Get() };
	UINT stride[] = { sizeof(DirectX::VertexPositionTexture) };
	UINT offset[] = { 0 };
	m_context->IASetVertexBuffers(0, 1, buffers, stride, offset);

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

	// ブレンドステートを設定 (半透明描画用)
	m_context->OMSetBlendState(m_commonStates->AlphaBlend(), nullptr, 0xFFFFFFFF);

	// プリミティブトポロジーを設定
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST);

	//	深度バッファに書き込み参照する
	m_context->OMSetDepthStencilState(m_commonStates->DepthDefault(), 0);
	// ラスタライザーステートの設定
	m_context->RSSetState(m_commonStates->CullCounterClockwise());

	//	シェーダをセットする
	m_context->VSSetShader(m_vertexShader, nullptr, 0);
	m_context->HSSetShader(m_hullShader, nullptr, 0);
	m_context->DSSetShader(m_domainShader, nullptr, 0);
	m_context->PSSetShader(m_pixelShader, nullptr, 0);

	// テクスチャの設定
	ID3D11ShaderResourceView* tex[1] = { m_texture };
	m_context->PSSetShaderResources(0, 1, tex);

	// 描画コール
	m_context->Draw(static_cast<UINT>(32 * (700 * 700)), 0);

	//	シェーダの登録を解除しておく
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->HSSetShader(nullptr, nullptr, 0);
	m_context->DSSetShader(nullptr, nullptr, 0);
	m_context->PSSetShader(nullptr, nullptr, 0);

	// テクスチャリソースを解放
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	m_context->PSSetShaderResources(0, 1, nullsrv);
}

/// <summary>
/// バッファの作成
/// </summary>
void Sea::CreateBuffer()
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
	

	// 定数の更新
	GerstnerWaveConstBuffer waveParams =
	{
		// 大波（うねり）
		1.2f, -0.8f,  0.6f, 0.9f,
		12.0f, 1.4f, 0.4f, 0.0f,

		// 中波（反射干渉）
		0.9f,  0.6f, -0.7f, 0.6f,
		6.0f,  1.6f, 0.5f, 0.0f,

		// 小波（細かい風のさざ波）
		0.6f, -0.3f, -1.1f, 0.3f,
		2.5f, 2.0f,  0.65f, 0.0f
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

	const int PATCH_COUNT_X = 700;
	const int PATCH_COUNT_Z = 700;
	const int PATCH_TOTAL = PATCH_COUNT_X * PATCH_COUNT_Z;
	const int VERTICES_PER_PATCH = 32;
	const int TOTAL_VERTICES = PATCH_TOTAL * VERTICES_PER_PATCH;

	std::vector<DirectX::VertexPositionTexture> vertices(TOTAL_VERTICES);

	// 1つのパッチのサイズ
	const float PATCH_SIZE = 20.0f; // 各パッチの領域（ワールド座標で）
	const float HALF_EXTENT_X = PATCH_COUNT_X * PATCH_SIZE * 0.5f;
	const float HALF_EXTENT_Z = PATCH_COUNT_Z * PATCH_SIZE * 0.5f;

	for (int patchZ = 0; patchZ < PATCH_COUNT_Z; ++patchZ) {
		for (int patchX = 0; patchX < PATCH_COUNT_X; ++patchX) {

			int patchIndex = patchZ * PATCH_COUNT_X + patchX;
			int baseVertexIndex = patchIndex * VERTICES_PER_PATCH;

			float offsetX = patchX * PATCH_SIZE - HALF_EXTENT_X;
			float offsetZ = patchZ * PATCH_SIZE - HALF_EXTENT_Z;

			for (int z = 0; z < 4; ++z) {
				for (int x = 0; x < 8; ++x) {
					int localIndex = z * 8 + x;

					float fx = offsetX + PATCH_SIZE * (float)x / 7.0f;
					float fz = offsetZ + PATCH_SIZE * (float)z / 3.0f;

					float u = (float)x / 7.0f;
					float v = (float)z / 3.0f;

					vertices[baseVertexIndex + localIndex] = {
						DirectX::XMFLOAT3(fx, 0.0f, fz),
						DirectX::XMFLOAT2(u, v)
					};
				}
			}
		}
	}


	// 頂点バッファの説明
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(DirectX::VertexPositionTexture) * vertices.size());
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;

	// 頂点データの初期化
	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = vertices.data();

	m_device->CreateBuffer(&vertexBufferDesc, &vertexData, m_vertexBuffer.ReleaseAndGetAddressOf());

}



