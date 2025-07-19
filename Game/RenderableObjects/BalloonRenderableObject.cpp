#include "pch.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Framework/Resources/ShaderResources.h"
#include "Game/RenderableObjects/BalloonRenderableObject.h"
#include "Game/Buffers/ConstantBuffer.h"
#include "Game/AmbientLight/AmbientLight.h"
#include "Game/Buffers.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="model">モデル</param>
BalloonRenderableObject::BalloonRenderableObject(const bool& isActive, DirectX::Model* model)
	:
	m_isAcitve(isActive),
	m_model(model),
	m_baseMap{},
	m_normalMap{},
	m_skyMap{},
	m_worldMatrix{},
	m_constants{},
	m_constantBuffer{}
{
	// 共有リソースのインスタンスを取得する
	m_resources = Resources::GetInstance();
	// デバイスを取得する
	m_device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	m_ambientLight = AmbientLight::GetInstance();
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="constants">定数バッファの格納用データ</param>
void BalloonRenderableObject::Initialize(const PBRLitConstantBuffer& constants)
{
	// 定数バッファに送るデータの初期値設定
	m_constants = constants;

	// 定数バッファオブジェクトの作成
	m_constantBuffer = std::make_unique<ConstantBuffer<PBRLitConstantBuffer>>();
	m_constantBuffer->Initialize(m_device);

	// 定数バッファオブジェクトの作成
	m_constantLightBuffer = std::make_unique<ConstantBuffer<DirectionalLightBuffer>>();
	m_constantLightBuffer->Initialize(m_device);

	// シャドウマップ用のサンプラーを作成する
	D3D11_SAMPLER_DESC samplerDesc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
	samplerDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS;
	DX::ThrowIfFailed(
		m_device->CreateSamplerState(&samplerDesc, m_shadowMapSampler.ReleaseAndGetAddressOf())
	);

	// テクスチャを設定
	m_baseMap   = m_resources->GetTextureResources()->GetTexture(TextureKeyID::Player);
	m_normalMap = m_resources->GetTextureResources()->GetTexture(TextureKeyID::Balloon);
	m_skyMap    = m_resources->GetTextureResources()->GetTexture(TextureKeyID::CubeMap);

	// インプットレイアウトを設定
	m_inputLayout = m_resources->GetShaderResources()->GetPBRLitInputLayout();
	// 頂点シェーダーを設定
	m_vertexShader = m_resources->GetShaderResources()->GetVertexShader(VS_ID::PBRLit_VS);
	// ピクセルシェーダーを設定
	m_pixelShader = m_resources->GetShaderResources()->GetPixelShader(PS_ID::Balloon_PS);

	// ワールド行列初期化
	m_worldMatrix = DirectX::SimpleMath::Matrix::Identity;

	// モデルのエフェクト情報を更新する
	m_model->UpdateEffects([](DirectX::IEffect* effect) {
		// ベーシックエフェクトを設定する
		DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
		if (basicEffect)
		{
			// 拡散反射光
			DirectX::SimpleMath::Color diffuseColor = DirectX::SimpleMath::Color(1.0f, 0.95f, 0.9f);
			// ライトが照らす方向
			DirectX::SimpleMath::Vector3 lightDirection(0.0f, 1.0f, 0.0f);

			basicEffect->SetLightEnabled(1, false);
			basicEffect->SetLightEnabled(2, false);

			// ゼロ番のライトに拡散反射光を設定する
			basicEffect->SetLightDiffuseColor(0, diffuseColor);
			// ゼロ番のライトが照らす方向を設定する
			basicEffect->SetLightDirection(0, lightDirection);
		}
		});


}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="context">コンテキスト</param>
/// <param name="worldMatrix">ワールド行列</param>
void BalloonRenderableObject::Update(ID3D11DeviceContext* context, const DirectX::SimpleMath::Matrix& worldMatrix)
{
	// ワールド行列を更新する
	m_worldMatrix = worldMatrix;
	// 値が変更されている場合更新処理を行う
	this->UpdateConstantBufferIfNeeded(context);

	this->CreateLightBuffer();
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="context">コンテキスト</param>
void BalloonRenderableObject::Render(ID3D11DeviceContext* context, DirectX::CommonStates* commonStates,
	DirectX::SimpleMath::Matrix viewMatrix, DirectX::SimpleMath::Matrix projectionMatrix,
	ID3D11ShaderResourceView* shadowMap
)
{
	// 非アクティブの時は描画しない
	if (!m_isAcitve) return;

	// モデル描画
	m_model->Draw(context, *commonStates, m_worldMatrix, viewMatrix, projectionMatrix, false, [&]
		{
			// 定数バッファを指定する
			ID3D11Buffer* cbuf[] = { m_ambientLight->GetBuffer() };
			context->VSSetConstantBuffers(1, 1, cbuf);
			context->PSSetConstantBuffers(1, 1, cbuf);

			// ブレンドステートを設定 (半透明描画用)
			context->OMSetBlendState(commonStates->AlphaBlend(), nullptr, 0xFFFFFFFF);

			context->IASetInputLayout(m_inputLayout);

			// 定数バッファを指定する
			cbuf[0] = { m_constantBuffer->GetBuffer()};
			context->VSSetConstantBuffers(2, 1, cbuf);
			context->PSSetConstantBuffers(2, 1, cbuf);

			// 定数バッファを指定する
			cbuf[0] = { m_constantLightBuffer->GetBuffer() };
			context->VSSetConstantBuffers(3, 1, cbuf);
			context->PSSetConstantBuffers(3, 1, cbuf);

			// テクスチャの設定
			std::vector<ID3D11ShaderResourceView*> tex = {
				m_baseMap,
				m_normalMap,
				m_skyMap,
				shadowMap
			};

			context->VSSetShaderResources(0, (UINT)tex.size(), tex.data());
			context->PSSetShaderResources(0, (UINT)tex.size(), tex.data());

			// シェーダーを設定
			context->VSSetShader(m_vertexShader, nullptr, 0);
			context->PSSetShader(m_pixelShader, nullptr, 0);

			// サンプラーステートを指定する
			ID3D11SamplerState* sampler[] = { commonStates->LinearWrap(),m_shadowMapSampler.Get() };
			context->VSSetSamplers(0, 2, sampler);
			context->PSSetSamplers(0, 2, sampler);
		});

	// シェーダの解放
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	// テクスチャリソースの解放
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	context->PSSetShaderResources(0, 1, nullsrv);
	context->PSSetShaderResources(1, 1, nullsrv);
	context->PSSetShaderResources(2, 1, nullsrv);
	context->PSSetShaderResources(3, 1, nullsrv);
}

/// <summary>
/// 定数バッファを取得する
/// </summary>
/// <returns>バッファ</returns>
ID3D11Buffer* BalloonRenderableObject::GetConstantBuffer() const
{
	return m_constantBuffer->GetBuffer();
}


/// <summary>
/// 値が変更された場合定数バッファを更新する
/// </summary>
/// <param name="context">コンテキスト</param>
void BalloonRenderableObject::UpdateConstantBufferIfNeeded(ID3D11DeviceContext* context)
{
	m_constantBuffer->UpdateIfNeeded(context, m_constants);
}


void BalloonRenderableObject::CreateLightBuffer()
{
	using namespace DirectX::SimpleMath;

	// ----------------------------------------------------------- //
	// ライト空間のビュー行列と射影行列を作成する
	// ----------------------------------------------------------- //

	/* 手順４ */

	// ライトの向いている方向を調整する
	//const Vector3 lightDir = Vector3(0.0f, -1.0f, 0.0f);

	Vector3 lightDir = Vector3::Transform(Vector3(0.0f, 0.0f, 1.0f), DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(90.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180.0f)));

	// ライト空間のビュー行列を計算する
	const Matrix lightView = Matrix::CreateLookAt(
		{ 0.0f , 10.0f ,0.0f },			// eye
		Vector3( 0.0f , 10.0f ,0.0f) + lightDir,	// target
		Vector3::UnitY				// up
	);

	const Matrix Projection = Matrix::CreateOrthographicOffCenter(
		-50.0f / 2.0f, 50.0f / 2.0f,   // 左・右
		-50.0f / 2.0f, 50.0f / 2.0f,   // 下・上
		0.1f, 1000.0f     // Near・Far
	);

	DirectionalLightBuffer cb;
	const Matrix viewProj = lightView * Projection;
	cb.lightViewProjection = XMMatrixTranspose(viewProj);
	cb.lightPosition = Vector3(0.0f, 10.0f, 0.0f);
	cb.lightDirection = lightDir;							// ライトが照らす方向
	cb.lightAmbient = Color(0.2f, 0.2f, 0.2f);


	// 定数バッファの更新
	m_constantLightBuffer->Update(CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(), cb);
}