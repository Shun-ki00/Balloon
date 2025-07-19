#pragma once
#include "Interface/IObject.h"
#include "Interface/IRenderableObject.h"
#include "Game/Buffers/ConstantBuffer.h"
#include "Game/Particle/ParticleEmitter.h"
#include "Game/ShadowMap/CascadedShadowMap.h"

class CommonResources;
class Particle;
class ParticleEmitter;
class UIRenderableObject;
class CascadedShadowMap;

class Renderer
{

public:
	// コンストラクタ
	Renderer();
	// デストラクタ
	~Renderer() = default;

	// シャドウマップを取得する
	ID3D11ShaderResourceView* GetShadowMap() const { return m_shadowMap->GetShadowShaderResourceView(); }

	// 描画オブジェクト追加
	void Attach(IObject* object, IRenderableObject* renderableObject);
	void Attach(ParticleEmitter* emitter) { m_particleEmitter.push_back(emitter); }
	void Attach(IObject* object, UIRenderableObject* renderableObject);

	// 描画処理
	void Render();

	// アタッチの許可
	void Begin();
	// アタッチの終了
	void End();

	// オブジェクトの削除
	void Reset();

private:

	// モデルの描画
	void ModelRender(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix);
	// パーティクル描画
	void ParticleRender(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix);
	// UI描画
	void UIRender();

	// アクティブ状態を探す
	bool IsHierarchyActive(IObject* object);

private:
	// 共有リソース
	CommonResources* m_commonResources;
	// デバイス
	ID3D11Device1* m_device;
	// コンテキスト
	ID3D11DeviceContext1* m_context;
	// コモンステート
	DirectX::CommonStates* m_commonStates;

	// 描画の許可
	bool m_isActiveAttach;


	// 描画オブジェクト
	std::vector<IObject*> m_objectKeys;
	std::unordered_map<IObject*, IRenderableObject*> m_modelRenderableObjects;

	// UI描画オブジェクト
	std::vector<IObject*> m_UIObjectKeys;
	std::unordered_map<IObject*, UIRenderableObject*> m_UIRenderableObjects;

	// パーティクルオブジェクト
	std::vector<ParticleEmitter*> m_particleEmitter;

	// 各オブジェクトの数
	int m_objectNumber;
	int m_uiObjectNumber;
	int particleEmitterNumber;

	// シャドウマップ描画
	std::unique_ptr<CascadedShadowMap> m_shadowMap;


	// === UI ===

	// インプットレイアウト
	ID3D11InputLayout* m_uiInputLayout;
	// 頂点シェーダー
	ID3D11VertexShader* m_uiVertexShader;
	// ジオメトリシェーダー
	ID3D11GeometryShader* m_uiGeometryShader;
	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_uiVertexBuffer;
	// 定数バッファデータ
	UIConstBuffer m_uiConstBufferData;
	// 定数バッファ
	std::unique_ptr<ConstantBuffer<UIConstBuffer>> m_uiConstBuffer;

	// === パーティクル ===
	
	// インプットレイアウト
	ID3D11InputLayout* m_particleiInputLayout;
	// 定数バッファ
	std::unique_ptr<ConstantBuffer<ParticleConstBuffer>> m_particleConstBuffer;
	// 頂点シェーダー
	ID3D11VertexShader* m_particleVertexShader;
	// ジオメトリシェーダー
	ID3D11GeometryShader* m_particleGeometryShader;
	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_particleVertexBuffer;
	// ビルボード
	DirectX::SimpleMath::Matrix m_billboardMatrix;
};