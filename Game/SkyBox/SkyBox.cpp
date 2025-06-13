// ============================================
// 
// ファイル名: SkyBox.cpp
// 概要: スカイボックスのクラス
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include <Framework/Microsoft/ReadData.h>
#include <DDSTextureLoader.h>
#include "Game/SkyBox/SkyBox.h"

#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Game/Buffers.h"


/// <summary>
/// コンストラクタ
/// </summary>
SkyBox::SkyBox()
	:
	m_skyboxModel{},
	m_vertexShader{},
	m_pixelShader{},
	m_cubemap{},
	m_eveningCubeMap{},
	m_constantBuffer{},
	m_angle{},
	m_dayProgress{}
{

}

/// <summary>
/// 初期化処理
/// </summary>
void SkyBox::Initialize()
{
	ID3D11DeviceContext* context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	Resources* resources = Resources::GetInstance();

	// スカイボックス用モデルの作成
	m_skyboxModel = DirectX::GeometricPrimitive::CreateSphere(context, 2.0f, 6, false);

	// シェーダー
	m_vertexShader = resources->GetShaderResources()->GetVertexShader(VS_ID::SkyBox_VS);
	m_pixelShader = resources->GetShaderResources()->GetPixelShader(PS_ID::SkyBox_PS);
	// スカイマップ
	m_cubemap = resources->GetTextureResources()->GetTexture(TextureKeyID::CubeMap);
	m_eveningCubeMap = resources->GetTextureResources()->GetTexture(TextureKeyID::EveningCubeMap);

	// 定数バッファ用のバッファオブジェクトを作成する
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(SkyBoxConstBuffer));	// 16の倍数を指定する
	bufferDesc.Usage          = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	DX::ThrowIfFailed(
		device->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer.ReleaseAndGetAddressOf())
	);

	// 回転角を初期化
	m_angle = 0.0f;
	// 一日の進行度を初期化
	m_dayProgress = 0.0f;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void SkyBox::Update(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	float elapsedTime = (float)CommonResources::GetInstance()->GetStepTimer()->GetElapsedSeconds();

	m_angle += elapsedTime * 30.0f;

	// ワールド行列の作成
	DirectX::SimpleMath::Matrix world =
		DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle * 0.01f));

	// GPUが使用するリソースのメモリにCPUからアクセスする際に利用する構造体
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	// コンテキスト
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// 定数バッファをマップする
	context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// 定数バッファに送るデータを準備する
	SkyBoxConstBuffer* cb = static_cast<SkyBoxConstBuffer*>(mappedResource.pData);
	cb->worldMatrix = world.Transpose();
	cb->viewMatrix = view.Transpose();
	cb->projectionMatrix = projection.Transpose();
	cb->dayProgress = DirectX::SimpleMath::Vector4(m_dayProgress, 0.0f, 0.0f, 0.0f);
	// マップを解除する
	context->Unmap(m_constantBuffer.Get(), 0);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="context">コンテキスト</param>
/// <param name="states">コモンステート</param>
void SkyBox::Render(ID3D11DeviceContext1* context, DirectX::CommonStates* states)
{
	// スカイボックスの描画
	m_skyboxModel->Draw({}, {}, {}, {}, nullptr, false, [&]()
		{
			// シェーダーの設定
			context->VSSetShader(m_vertexShader, nullptr, 0);
			context->PSSetShader(m_pixelShader , nullptr, 0);

			// 定数バッファの設定（共通定数バッファのみ）
			context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
			context->PSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());

			// テクスチャを設定
			context->PSSetShaderResources(0 , 1, &m_cubemap);
			context->PSSetShaderResources(1 , 1, &m_eveningCubeMap);

			// サンプラーの設定
			auto sampler = states->LinearClamp();
			context->VSSetSamplers(0, 1, &sampler);
			context->PSSetSamplers(0, 1, &sampler);
		});

	// シェーダの解放
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	// リソースの解放
	ID3D11ShaderResourceView* resource = nullptr;
	context->PSSetShaderResources(0, 1, &resource);
	context->PSSetShaderResources(1, 1, &resource);
}