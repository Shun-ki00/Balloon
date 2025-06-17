#include "pch.h"
#include "Framework/Renderer.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include "Interface/IRenderableObject.h"
#include "Game/RenderableObjects/UIRenderableObject .h"
#include "Game/Particle/Particle.h"
#include "Game/Particle/ParticleEmitter.h"
#include "Game/Buffers.h"



Renderer::Renderer()
{
	m_commonResources = CommonResources::GetInstance();
	m_device          = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	m_context         = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	m_commonStates    = CommonResources::GetInstance()->GetCommonStates();


	m_particleConstBuffer = std::make_unique<ConstantBuffer<ParticleConstBuffer>>();
	m_particleConstBuffer->Initialize(m_commonResources->GetDeviceResources()->GetD3DDevice());


	// === UI ===

	// 頂点シェーダーを取得する
	m_uiVertexShader = Resources::GetInstance()->GetShaderResources()->GetVertexShader(VS_ID::UI_VS);
	// ジオメトリシェーダーを取得する
	m_uiGeometryShader = Resources::GetInstance()->GetShaderResources()->GetGeometryShader(GS_ID::UI_GS);
	// インプットレイアウトを取得する
	m_uiInputLayout = Resources::GetInstance()->GetShaderResources()->GetUIinputLayout();
	
	// 定数バッファの初期化
	m_uiConstBufferData.windowSize = { 1280.0f ,720.0f };
	m_uiConstBufferData.useTexture = 1.0f;
	m_uiConstBufferData.time = { 0.0f ,0.0f ,0.0f ,0.0f };

	m_uiConstBuffer = std::make_unique<ConstantBuffer<UIConstBuffer>>();
	m_uiConstBuffer->Initialize(m_device);

	// シェーダーにデータを渡すためのUIのバーテックスバッファの作成
	D3D11_BUFFER_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(UIVertexBuffer);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	m_device->CreateBuffer(&desc, nullptr, &m_uiVertexBuffer);

	// === パーティクル ===

	// 頂点シェーダーを取得する
	m_particleVertexShader   = Resources::GetInstance()->GetShaderResources()->GetVertexShader(VS_ID::Particle_VS);
	// ジオメトリシェーダーを取得する
	m_particleGeometryShader = Resources::GetInstance()->GetShaderResources()->GetGeometryShader(GS_ID::Particle_GS);
	// インプットレイアウトを取得する
	m_particleiInputLayout   = Resources::GetInstance()->GetShaderResources()->GetParticleInputLayout();


	// シェーダーにデータを渡すためのUIのバーテックスバッファの作成
	 desc = {};
	ZeroMemory(&desc, sizeof(desc));
	// サイズは必要な頂点分にする
	desc.ByteWidth = sizeof(DirectX::VertexPositionColorTexture) * 300; 
	// 毎フレーム書き換えるならDYNAMICを使う
	desc.Usage = D3D11_USAGE_DYNAMIC;
	// バインドフラグはVertexBuffer
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// CPUから書き込みできるようにする
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// バッファ作成
	m_device->CreateBuffer(&desc, nullptr, &m_particleVertexBuffer);

	// アタッチの許可初期化処理
	m_isActiveAttach = false;
}


/// <summary>
/// 描画処理を行う
/// </summary>
void Renderer::Render()
{
	DirectX::SimpleMath::Matrix viewMatrix       = m_commonResources->GetViewMatrix();
	DirectX::SimpleMath::Matrix projectionMatrix = m_commonResources->GetProjectionMatrix();

	// モデルを描画する
	this->ModelRender(viewMatrix, projectionMatrix);
	// パーティクル描画
	this->ParticleRender(viewMatrix, projectionMatrix);
	// UIの描画
	this->UIRender();
}

/// <summary>
/// モデルをアタッチする
/// </summary>
/// <param name="object">オブジェクト</param>
/// <param name="renderableObject">描画オブジェクト</param>
void Renderer::Attach(IObject* object, IRenderableObject* renderableObject)
{
	// アタッチを許可されてなければスキップ
	if (!m_isActiveAttach) return;

	// キーの追加
	m_objectKeys.push_back(object);

	// 描画オブジェクトの追加
	m_modelRenderableObjects[object] = renderableObject;
}

/// <summary>
/// UIをアタッチする
/// </summary>
/// <param name="object">UIオブジェクト</param>
/// <param name="renderableObject">UI描画オブジェクト</param>
void Renderer::Attach(IObject* object, UIRenderableObject* renderableObject)
{
	// アタッチを許可されてなければスキップ
	if (!m_isActiveAttach) return;

	// キーの追加
	m_UIObjectKeys.push_back(object);

	// 描画オブジェクトの追加
	m_UIRenderableObjects[object] = renderableObject;
}

/// <summary>
/// アタッチを開始
/// </summary>
void Renderer::Begin()
{
	// アタッチの許可
	m_isActiveAttach = true;
	
	// 現在のオブジェクトの数を取得する
	m_objectNumber = m_objectKeys.size();
	// 現在のUIオブジェクトの数を取得する
	m_uiObjectNumber = m_UIObjectKeys.size();
	// 現在のエフェクトの数を取得する
	particleEmitterNumber = m_particleEmitter.size();

}

/// <summary>
/// アタッチ終了
/// </summary>
void Renderer::End()
{
	// 前のシーンのオブジェクトを破棄
	for (int i = 0; i < m_objectNumber; ++i)
	{
		// 先頭のオブジェクト取得
		IObject* obj = m_objectKeys.front();
		// レンダラブルマップから削除
		m_modelRenderableObjects.erase(obj);    
		// ベクタから先頭削除
		m_objectKeys.erase(m_objectKeys.begin());
	}

	// 前のシーンのUIオブジェクトを破棄
	for (int i = 0; i < m_uiObjectNumber; i++)
	{
		// 先頭のオブジェクト取得
		IObject* obj = m_UIObjectKeys.front();  
		// レンダラブルマップから削除
		m_UIRenderableObjects.erase(obj);    
		// ベクタから先頭削除
		m_UIObjectKeys.erase(m_UIObjectKeys.begin()); 
	}

	// 前のシーンのエフェクトを破棄
	for (int i = 0; i < particleEmitterNumber; i++)
	{
		// 先頭のエフェクトを破棄する
		m_particleEmitter.erase(m_particleEmitter.begin());
	}

	// 現在のオブジェクトの数を取得する
	m_objectNumber = m_objectKeys.size();
	// 現在のUIオブジェクトの数を取得する
	m_uiObjectNumber = m_UIObjectKeys.size();
	// 現在のエフェクトの数を取得する
	particleEmitterNumber = m_particleEmitter.size();
}

/// <summary>
/// オブジェクトの削除
/// </summary>
void Renderer::Reset()
{

}


/// <summary>
/// モデルを描画する
/// </summary>
/// <param name="viewMatrix">ビュー行列</param>
/// <param name="projectionMatrix">射影行列</param>
void Renderer::ModelRender(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	for (int i = 0; i < m_objectNumber; ++i)
	{
		IObject* object = m_objectKeys[i];
		IRenderableObject* renderable = m_modelRenderableObjects[object];

		bool active = this->IsHierarchyActive(object);

		if (active && renderable->GetIsActive())
		{
			renderable->Render(m_context, m_commonStates, viewMatrix, projectionMatrix);
		}
	}
}



/// <summary>
/// パーティクルを描画する
/// </summary>
/// <param name="viewMatrix">ビュー行列</param>
/// <param name="projectionMatrix">射影行列</param>
void Renderer::ParticleRender(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	ParticleConstBuffer particleConstBuffer = {};
	particleConstBuffer.projectionMatrix = projectionMatrix.Transpose();
	particleConstBuffer.viewMatrix = viewMatrix.Transpose();
	// ビルボード行列を作る
	m_billboardMatrix = viewMatrix.Invert();
	m_billboardMatrix._41 = 0.0f;
	m_billboardMatrix._42 = 0.0f;
	m_billboardMatrix._43 = 0.0f;
	particleConstBuffer.billboardMatrix = m_billboardMatrix.Transpose();
	particleConstBuffer.worldMatrix = world.Transpose();
	particleConstBuffer.time = DirectX::SimpleMath::Vector4::Zero;

	// 定数バッファの更新
	m_particleConstBuffer->Update(m_context, particleConstBuffer);

	//	シェーダーに定数バッファを渡す
	ID3D11Buffer* cb[1] = { m_particleConstBuffer->GetBuffer() };
	m_context->VSSetConstantBuffers(0, 1, cb);
	m_context->GSSetConstantBuffers(0, 1, cb);
	m_context->PSSetConstantBuffers(0, 1, cb);

	//	半透明描画指定		補間アルファ合成
	ID3D11BlendState* blendstate = m_commonStates->NonPremultiplied();
	//	透明判定処理
	m_context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	m_context->OMSetDepthStencilState(m_commonStates->DepthRead(), 0);

	//	カリングはなし
	m_context->RSSetState(m_commonStates->CullNone());

	//	インプットレイアウトの登録
	m_context->IASetInputLayout(m_particleiInputLayout);

	// プリミティブトポロジーを設定
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// 頂点シェーダーの設定
	m_context->VSSetShader(m_particleVertexShader, nullptr, 0);
	// ジオメトリシェーダーの設定
	m_context->GSSetShader(m_particleGeometryShader, nullptr, 0);

	
	for (int i = 0; i < particleEmitterNumber; ++i)
	{
		ParticleEmitter* emitter = m_particleEmitter[i];

		if (!emitter->GetIsActive() || emitter->GetInputDatas().empty())
			continue;

		particleConstBuffer.worldMatrix = DirectX::SimpleMath::Matrix::Identity;
		m_particleConstBuffer->UpdateIfNeeded(m_context, particleConstBuffer);

		ID3D11ShaderResourceView* srv = emitter->GetTexture();
		m_context->PSSetShaderResources(0, 1, &srv);

		ID3D11SamplerState* sampler[1] = { m_commonStates->LinearWrap() };
		m_context->PSSetSamplers(0, 1, sampler);

		m_context->PSSetShader(emitter->GetPixelShader(), nullptr, 0);

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		m_context->Map(m_particleVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

		memcpy(mappedResource.pData, emitter->GetInputDatas().data(),
			sizeof(DirectX::VertexPositionColorTexture) * emitter->GetInputDatas().size());

		m_context->Unmap(m_particleVertexBuffer.Get(), 0);

		UINT stride = sizeof(DirectX::VertexPositionColorTexture);
		UINT offset = 0;
		ID3D11Buffer* buffer = m_particleVertexBuffer.Get();
		m_context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);

		m_context->Draw(static_cast<UINT>(emitter->GetInputDatas().size()), 0);

		m_context->PSSetShader(nullptr, nullptr, 0);
		ID3D11ShaderResourceView* nullsrv[] = { nullptr };
		m_context->PSSetShaderResources(0, 1, nullsrv);
	}

	//	シェーダの登録を解除しておく
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->GSSetShader(nullptr, nullptr, 0);
}

/// <summary>
/// UIを描画する
/// </summary>
void Renderer::UIRender()
{
	// 経過時間を更新
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();
	m_uiConstBufferData.time.x += elapsedTime;

	// 定数バッファを設定
	m_uiConstBuffer->Update(m_context, m_uiConstBufferData);

	//	シェーダーに定数バッファを渡す
	ID3D11Buffer* cb[1] = { m_uiConstBuffer->GetBuffer() };
	m_context->VSSetConstantBuffers(0, 1, cb);
	m_context->GSSetConstantBuffers(0, 1, cb);
	m_context->PSSetConstantBuffers(0, 1, cb);

	//	半透明描画指定		補間アルファ合成
	ID3D11BlendState* blendstate = m_commonStates->NonPremultiplied();
	//	透明判定処理
	m_context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	//	深度バッファに書き込み参照する
	m_context->OMSetDepthStencilState(m_commonStates->DepthRead(), 0);
	//	カリングはなし
	m_context->RSSetState(m_commonStates->CullNone());
	// 入力レイアウトを設定
	m_context->IASetInputLayout(m_uiInputLayout);
	// プリミティブトポロジーを設定 (ポイントリスト)
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// 頂点シェーダーの設定
	m_context->VSSetShader(m_uiVertexShader, nullptr, 0);
	// ジオメトリシェーダーの設定
	m_context->GSSetShader(m_uiGeometryShader, nullptr, 0);

	for (int i = 0; i < m_uiObjectNumber; ++i)
	{
		IObject* object = m_UIObjectKeys[i];
		UIRenderableObject* renderable = m_UIRenderableObjects[object];

		if (!object->GetIsActive() || !renderable->GetIsActive())
			continue;

		UIVertexBuffer buffer = renderable->GetVertexBufferData();
		m_context->UpdateSubresource(m_uiVertexBuffer.Get(), 0, NULL, &buffer, 0, 0);

		ID3D11Buffer* buffers[] = { m_uiVertexBuffer.Get() };
		UINT stride[] = { sizeof(UIVertexBuffer) };
		UINT offset[] = { 0 };
		m_context->IASetVertexBuffers(0, 1, buffers, stride, offset);

		m_context->PSSetShader(renderable->GetPixelShader(), nullptr, 0);

		std::vector<ID3D11ShaderResourceView*> tex = {
			renderable->GetTexture(),
			renderable->GetRuleTexture(),
		};
		m_context->PSSetShaderResources(0, (UINT)tex.size(), tex.data());

		m_context->Draw(1, 0);

		m_context->PSSetShader(nullptr, nullptr, 0);
		ID3D11ShaderResourceView* nullsrv[] = { nullptr };
		m_context->PSSetShaderResources(0, 1, nullsrv);
	}

	// リソースの解放
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	m_context->PSSetShaderResources(0, 0, nullsrv);
	m_context->PSSetShaderResources(0, 1, nullsrv);

	// 頂点シェーダーの解放
	m_context->VSSetShader(nullptr, nullptr, 0);
	// ジオメトリシェーダーの解放
	m_context->GSSetShader(nullptr, nullptr, 0);

}


bool Renderer::IsHierarchyActive(IObject* object)
{
	while (object != nullptr && object != Root::GetInstance())
	{
		if (!object->GetIsActive())
			return false;

		object = object->GetParent();
	}

	// Root まで到達したら、Root 自体もチェック（必要であれば）
	return Root::GetInstance()->GetIsActive();
}