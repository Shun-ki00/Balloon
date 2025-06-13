#include "pch.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Framework/Resources/ShaderResources.h"
#include "Game/RenderableObjects/EnemyRenderableObject.h"
#include "Game/Buffers/ConstantBuffer.h"
#include "Game/AmbientLight/AmbientLight.h"
#include "Game/Buffers.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="model">モデル</param>
EnemyRenderableObject::EnemyRenderableObject(const bool& isActive, DirectX::Model* model)
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
void EnemyRenderableObject::Initialize(const PBRLitConstantBuffer& constants)
{
	// 定数バッファに送るデータの初期値設定
	m_constants = constants;

	// 定数バッファオブジェクトの作成
	m_constantBuffer = std::make_unique<ConstantBuffer<PBRLitConstantBuffer>>();
	m_constantBuffer->Initialize(m_device);

	// テクスチャを設定
	m_baseMap   = m_resources->GetTextureResources()->GetTexture(TextureKeyID::Enemy);
	m_normalMap = m_resources->GetTextureResources()->GetTexture(TextureKeyID::Wood);
	m_skyMap    = m_resources->GetTextureResources()->GetTexture(TextureKeyID::CubeMap);

	// インプットレイアウトを設定
	m_inputLayout = m_resources->GetShaderResources()->GetPBRLitInputLayout();
	// 頂点シェーダーを設定
	m_vertexShader = m_resources->GetShaderResources()->GetVertexShader(VS_ID::PBRLit_VS);
	// ピクセルシェーダーを設定
	m_pixelShader = m_resources->GetShaderResources()->GetPixelShader(PS_ID::PBRLit_PS);

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
void EnemyRenderableObject::Update(ID3D11DeviceContext* context, const DirectX::SimpleMath::Matrix& worldMatrix)
{
	// ワールド行列を更新する
	m_worldMatrix = worldMatrix;
	// 値が変更されている場合更新処理を行う
	this->UpdateConstantBufferIfNeeded(context);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="context">コンテキスト</param>
void EnemyRenderableObject::Render(ID3D11DeviceContext* context, DirectX::CommonStates* commonStates,
	DirectX::SimpleMath::Matrix viewMatrix, DirectX::SimpleMath::Matrix projectionMatrix
)
{
	// 非アクティブの時は描画しない
	if (!m_isAcitve) return;

	// モデル描画
	m_model->Draw(context, *commonStates, m_worldMatrix, viewMatrix, projectionMatrix, false, [&]
		{
			// 定数バッファを指定する
			ID3D11Buffer* cbuf[] = { m_ambientLight->GetBuffer()};
			context->VSSetConstantBuffers(1, 1, cbuf);
			context->PSSetConstantBuffers(1, 1, cbuf);

			// ブレンドステートを設定 (半透明描画用)
			context->OMSetBlendState(commonStates->AlphaBlend(), nullptr, 0xFFFFFFFF);

			context->IASetInputLayout(m_inputLayout);

			// 定数バッファを指定する
			cbuf[0] = { m_constantBuffer->GetBuffer()};
			context->VSSetConstantBuffers(2, 1, cbuf);
			context->PSSetConstantBuffers(2, 1, cbuf);

			// テクスチャの設定
			std::vector<ID3D11ShaderResourceView*> tex = {
				m_baseMap,
				m_normalMap,
				m_skyMap,
			};

			context->VSSetShaderResources(0, (UINT)tex.size(), tex.data());
			context->PSSetShaderResources(0, (UINT)tex.size(), tex.data());

			// シェーダーを設定
			context->VSSetShader(m_vertexShader, nullptr, 0);
			context->PSSetShader(m_pixelShader, nullptr, 0);

			// サンプラーステートを指定する
			ID3D11SamplerState* sampler[] = { commonStates->LinearWrap() };
			context->VSSetSamplers(0, 1, sampler);
			context->PSSetSamplers(0, 1, sampler);
		});

	// シェーダの解放
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	// テクスチャリソースの解放
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	context->PSSetShaderResources(0, 1, nullsrv);
	context->PSSetShaderResources(1, 1, nullsrv);
	context->PSSetShaderResources(2, 1, nullsrv);
}

/// <summary>
/// 定数バッファを取得する
/// </summary>
/// <returns>バッファ</returns>
ID3D11Buffer* EnemyRenderableObject::GetConstantBuffer() const
{
	return m_constantBuffer->GetBuffer();
}


/// <summary>
/// 値が変更された場合定数バッファを更新する
/// </summary>
/// <param name="context">コンテキスト</param>
void EnemyRenderableObject::UpdateConstantBufferIfNeeded(ID3D11DeviceContext* context)
{
	m_constantBuffer->UpdateIfNeeded(context, m_constants);
}
