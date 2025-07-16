#pragma once

class DebugRenderer
{

public:

	// ボックスの登録
	void Attach(const DirectX::BoundingBox& box);
	// スフィアの登録
	void Attach(const DirectX::BoundingSphere& sphere);

	// リセット
	void Reset();

	// 描画処理
	void Render(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitiveBatch);
	
private:
	//	コンストラクタ
	DebugRenderer();
	//	デストラクタ
	~DebugRenderer() = default;
public:
	DebugRenderer(const DebugRenderer&) = delete;             // コピー禁止
	DebugRenderer& operator=(const DebugRenderer&) = delete;  // コピー代入禁止
	DebugRenderer(const DebugRenderer&&) = delete;            // ムーブ禁止
	DebugRenderer& operator=(const DebugRenderer&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static DebugRenderer* GetInstance()
	{
		static DebugRenderer instance;
		return &instance;
	}

private:

	// ボックス
	std::vector<DirectX::BoundingBox> m_boxes;
	// スフィア
	std::vector<DirectX::BoundingSphere> m_spheres;

};