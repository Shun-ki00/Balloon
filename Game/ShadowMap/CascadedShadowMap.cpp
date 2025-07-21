// ============================================
// 
// ファイル名: CascadedShadowMap.h
// 概要: カスケードシャドウマップを作成するクラス
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/ShadowMap/CascadedShadowMap.h"
#include <Framework/Microsoft/RenderTexture.h>

#include "Framework/CommonResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Game/Transform/Transform.h"
#include "Framework/DepthStencil.h"
#include "Game/Buffers.h"


/// <summary>
/// コンストラクタ
/// </summary>
CascadedShadowMap::CascadedShadowMap()
	:
	m_commonResources{},
	m_cascadedIndex{},
	m_transform{},
	m_lightProjectionMatrix{},
	m_lightViewMatrix{},
	m_cameraTransform{},
	m_shadowMapRT{},
	m_shadowMapDS{},
	m_shadowVS{},
	m_shadowPS{},
	m_shadowMapSampler{},
	m_DLBuffer{}
{
	// 共有リソースのインスタンスを取得する
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// 初期化処理
/// </summary>
void CascadedShadowMap::Initialize()
{
	ID3D11Device1* device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// シェーダーを取得
	m_shadowVS = Resources::GetInstance()->GetShaderResources()->GetVertexShader(VS_ID::ShadowMap_VS);
	m_shadowPS = Resources::GetInstance()->GetShaderResources()->GetPixelShader(PS_ID::ShadowMap_PS);

	// シャドウマップの大きさを指定する
	const RECT rectShadow = { 0 , 0 , (LONG)SHADOWMAP_SIZE , (LONG)SHADOWMAP_SIZE };

	// レンダーテクスチャを作成する
	m_shadowMapRT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
	m_shadowMapRT->SetDevice(device);
	m_shadowMapRT->SetWindow(rectShadow);

	// 深度ステンシルを作成する
	m_shadowMapDS = std::make_unique<DepthStencil>(DXGI_FORMAT_D32_FLOAT);
	m_shadowMapDS->SetDevice(device);
	m_shadowMapDS->SetWindow(rectShadow);

	// シャドウマップ用のサンプラーを作成する
	D3D11_SAMPLER_DESC samplerDesc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
	samplerDesc.Filter         = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU       = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressV       = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressW       = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS;

	DX::ThrowIfFailed(
		device->CreateSamplerState(&samplerDesc, m_shadowMapSampler.ReleaseAndGetAddressOf())
	);

	// 定数バッファ用のバッファオブジェクトを作成する
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(DirectionalLightBuffer)); // 16の倍数を指定する
	bufferDesc.Usage          = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	DX::ThrowIfFailed(
		device->CreateBuffer(&bufferDesc, nullptr, m_DLBuffer.ReleaseAndGetAddressOf())
	);

	// ライトの初期化
	m_transform = std::make_unique<Transform>();
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::UnitY * 10.0f);
	m_transform->SetLocalRotation(
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(90.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY,DirectX::XMConvertToRadians(180.0f))
	);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::Zero);

	// プロジェクション行列を作成
	m_lightProjectionMatrix = DirectX::SimpleMath::Matrix::CreateOrthographicOffCenter(
		-50.0f / 2.0f, 50.0f / 2.0f,   // 左・右
		-50.0f / 2.0f, 50.0f / 2.0f,   // 下・上
		0.1f, 1000.0f                  // Near・Far
	);
}

/// <summary>
/// 影描画処理
/// </summary>
/// <param name="model">モデル</param>
/// <param name="world">ワールド行列</param>
void CascadedShadowMap::Draw(DirectX::Model* model, ID3D11DeviceContext1* context, DirectX::CommonStates* states,
	Transform* transform)
{
	using namespace DirectX::SimpleMath;

	Matrix world =
		Matrix::CreateScale(transform->GetWorldScale() * 2.0f) *
		Matrix::CreateFromQuaternion(transform->GetWorldRotation()) *
		Matrix::CreateTranslation(transform->GetWorldPosition());

	// 影用モデル描画
	model->Draw(context, *states, world, m_lightViewMatrix, m_lightProjectionMatrix, false, [&]
		{
			context->VSSetShader(m_shadowVS, nullptr, 0);
			context->PSSetShader(m_shadowPS, nullptr, 0);
		}
	);
}

/// <summary>
/// 影描画準備
/// </summary>
void CascadedShadowMap::Begin()
{
	// デバイスコンテキスト
	ID3D11DeviceContext1* context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// 必要なviewを取得する
	ID3D11RenderTargetView*   rtv = m_shadowMapRT->GetRenderTargetView();
	ID3D11DepthStencilView*   dsv = m_shadowMapDS->GetDepthStencilView();

	// シャドウマップ用のRTVとDSVをクリアする
	context->ClearRenderTargetView(rtv, DirectX::Colors::White);
	context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);

	// RTVとDSVをシャドウマップ用に変更する
	context->OMSetRenderTargets(1, &rtv, dsv);

	// ビューポートをシャドウマップ用に変更する
	const D3D11_VIEWPORT vp = { 0.0f,0.0f,SHADOWMAP_SIZE,SHADOWMAP_SIZE,0.0f,1.0f };
	context->RSSetViewports(1, &vp);

	// ライトの方向
	DirectX::SimpleMath::Vector3 lightDirection = DirectX::SimpleMath::Vector3::Transform(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), m_transform->GetLocalRotation()
	);
	// ライトの向いている方向を調整する scaleをターゲットとしてみる
	m_transform->SetLocalScale(
		m_transform->GetLocalPosition() + lightDirection
	);
	
	// ライト空間のビュー行列を計算する
	m_lightViewMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(
		m_transform->GetLocalPosition(),     // eye
		m_transform->GetLocalScale(),        // targetd
		DirectX::SimpleMath::Vector3::UnitY  // up
	);

	// GPUが使用するリソースのメモリにCPUからアクセスする際に利用する構造体
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	// 定数バッファをマップする
	context->Map(m_DLBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// 定数バッファに送るデータを準備する
	DirectionalLightBuffer* cb = static_cast<DirectionalLightBuffer*>(mappedResource.pData);
	const DirectX::SimpleMath::Matrix viewProj = m_lightViewMatrix * m_lightProjectionMatrix;
	cb->lightViewProjection = DirectX::XMMatrixTranspose(viewProj);	   // ビュー行列と射影行列を合算したもの
	cb->lightPosition  = m_transform->GetLocalPosition();	           // ライトの座標
	cb->lightDirection = lightDirection;							   // ライトが照らす方向
	cb->lightAmbient   = DirectX::SimpleMath::Color(0.2f, 0.2f, 0.2f); // 環境光

	// マップを解除する
	context->Unmap(m_DLBuffer.Get(), 0);
}

/// <summary>
/// 影描画終了処理
/// </summary>
void CascadedShadowMap::End()
{
	// デバイスコンテキスト
	ID3D11DeviceContext1* context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// RTVとDSVを通常描画用の設定に戻す準備
	ID3D11RenderTargetView* defaultRTV = m_commonResources->GetDeviceResources()->GetRenderTargetView();
	ID3D11DepthStencilView* defaultDSV = m_commonResources->GetDeviceResources()->GetDepthStencilView();

	// 描画先に通常描画用のRTVとDSVを設定する
	context->OMSetRenderTargets(1, &defaultRTV, defaultDSV);

	// ビューポートを通常描画用に切り替える
	auto const& defaultVP = m_commonResources->GetDeviceResources()->GetScreenViewport();
	context->RSSetViewports(1, &defaultVP);
}



