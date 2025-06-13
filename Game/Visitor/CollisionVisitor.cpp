#include "pch.h"
#include "Game/Visitor/CollisionVisitor.h"
#include "Interface/ICollision.h"
#include "Game/Message/ObjectMessenger.h"
#include "Framework/Microsoft/DebugDraw.h"

CollisionVisitor::CollisionVisitor()
{

}

void CollisionVisitor::StartPrepareCollision(IObject* object)
{
	dynamic_cast<ICollision*>(object)->PrepareCollision(this);
}


void CollisionVisitor::PrepareCollision(IObject* object,
	const DirectX::SimpleMath::Vector3& position , const float& radius)
{
	DirectX::BoundingSphere boundingSphere;

	// 初期座標を設定
	boundingSphere.Center = position;
	// 大きさを設定
	boundingSphere.Radius = radius;

	// オブジェクト番号と境界スフィアをマップに格納する
	m_boundingSphere.insert({ object->GetObjectNumber() , boundingSphere });
}



void CollisionVisitor::DetectCollision(IObject* object, IObject* object1)
{
	DirectX::BoundingSphere worldBoundingSphere;
	DirectX::BoundingSphere worldBoundingSphere1;

	// どちらかが非アクティブの場合判定を行わない
	if (!object->GetIsActive() || !object1->GetIsActive())
		return;

	// 部品番号から境界ボックスを検索する
	auto it = m_boundingSphere.find(object->GetObjectNumber());

	worldBoundingSphere.Center =
		it->second.Center + object->GetTransform()->GetWorldPosition();

	worldBoundingSphere.Radius = it->second.Radius;

	// 部品番号から境界ボックスを検索する
	it = m_boundingSphere.find(object1->GetObjectNumber());

	worldBoundingSphere1.Center =
		it->second.Center + object1->GetTransform()->GetWorldPosition();

	worldBoundingSphere1.Radius = it->second.Radius;

	// 当たり判定を行う
	if (worldBoundingSphere.Intersects(worldBoundingSphere1))
	{
		// 衝突した場合,メッセージを送る 衝突相手の番号も一緒に送る
		ObjectMessenger::GetInstance()->Dispatch(object->GetObjectID(), object->GetObjectNumber(),
			{ Message::MessageID::ON_COLLISION , object1->GetObjectNumber() });

		// 衝突した場合,メッセージを送る 衝突相手の番号も一緒に送る
	/*	ObjectMessenger::GetInstance()->Dispatch(object1->GetObjectNumber(),
			{ Message::MessageID::ON_COLLISION , object->GetObjectNumber() });*/

		// object 側の更新
		m_worldBoundingSpheres[object][true] = worldBoundingSphere;
		m_worldBoundingSpheres[object].erase(false);

		// object1 側の更新
		m_worldBoundingSpheres[object1][true] = worldBoundingSphere1;
		m_worldBoundingSpheres[object1].erase(false);
	}
	else
	{
		if (m_worldBoundingSpheres.find(object) == m_worldBoundingSpheres.end())
		{
			m_worldBoundingSpheres[object].insert({ false, worldBoundingSphere });
		}

		m_worldBoundingSpheres[object1].insert({ false, worldBoundingSphere1 });
	}

}

void CollisionVisitor::DebugDraw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitiveBatch)
{
	for (const auto& [object, result] : m_worldBoundingSpheres)
	{
		for (const auto& [collisionResult, sphere] : result)
		{
			if (collisionResult)
				DX::Draw(primitiveBatch, sphere, DirectX::Colors::Yellow);
			else
				DX::Draw(primitiveBatch, sphere, DirectX::Colors::Green);
		}
	}

	m_worldBoundingSpheres.clear();
}