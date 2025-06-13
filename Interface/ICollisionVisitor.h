#pragma once
#include "Interface/IObject.h"

class ICollisionVisitor
{
public:
	// デストラクタ
	virtual ~ICollisionVisitor() = default;

	// 衝突準備ビジターを開始する
	virtual void StartPrepareCollision(IObject* component) = 0;
	// 再帰的に衝突準備ビジターを呼び出す
	virtual void PrepareCollision(IObject* object,
		const DirectX::SimpleMath::Vector3& position, const float& radius) = 0;
	// 再帰的にDetectCollision関数を呼び出す
	virtual void DetectCollision(IObject* component, IObject* bullets) = 0;

	// 境界ボックスを描画する
	virtual void DebugDraw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitiveBatch ) = 0;
};