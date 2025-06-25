#pragma once
#include "Interface/ICollisionVisitor.h"

class CollisionVisitor : public ICollisionVisitor
{

public:
	// 衝突準備ビジターを開始する
	void StartPrepareCollision(IObject* object) override;
	// 再帰的に衝突準備ビジターを呼び出す
	void PrepareCollision(IObject* object,DirectX::BoundingSphere* boundingSphere) override;
	// 再帰的にDetectCollision関数を呼び出す
	void DetectCollision(IObject* object, IObject* object1) override;

	// 境界ボックスを描画する
	void DebugDraw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitiveBatch) override;

private:
	//	コンストラクタ
	CollisionVisitor();
	//	デストラクタ
	~CollisionVisitor() = default;
public:
	CollisionVisitor(const CollisionVisitor&) = delete;             // コピー禁止
	CollisionVisitor& operator=(const CollisionVisitor&) = delete;  // コピー代入禁止
	CollisionVisitor(const CollisionVisitor&&) = delete;            // ムーブ禁止
	CollisionVisitor& operator=(const CollisionVisitor&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static CollisionVisitor* GetInstance()
	{
		static CollisionVisitor instance;
		return &instance;
	}


private:

	// 「砲塔」配列バウンディングボックス
	std::unordered_map<int, DirectX::BoundingSphere*> m_boundingSphere;

	std::unordered_map<IObject* ,std::unordered_map<bool,  DirectX::BoundingSphere>> m_worldBoundingSpheres;
};