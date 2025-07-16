#include "pch.h"
#include "Game/Visitor/CollisionVisitor.h"
#include "Interface/ICollision.h"
#include "Game/Message/ObjectMessenger.h"
#include "Framework/Microsoft/DebugDraw.h"

/// <summary>
/// コンストラクタ
/// </summary>
CollisionVisitor::CollisionVisitor()
	:
	m_isActiveAttach(false),
	m_boundingSphere{},
	m_worldBoundingSpheres{}
{
}

/// <summary>
/// 衝突判定の準備処理
/// </summary>
/// <param name="object">オブジェクト</param>
void CollisionVisitor::StartPrepareCollision(IObject* object)
{
	dynamic_cast<ICollision*>(object)->PrepareCollision(this);
}


/// <summary>
///	境界球を登録する
/// </summary>
/// <param name="object">オブジェクト</param>
/// <param name="boundingSphere">スフィア</param>
void CollisionVisitor::PrepareCollision(IObject* object, DirectX::BoundingSphere* boundingSphere)
{
	// オブジェクト番号と境界スフィアをマップに格納する
	m_boundingSphere.insert({ object->GetObjectNumber() , boundingSphere });
}


/// <summary>
/// 当たり判定を行う
/// </summary>
/// <param name="object">オブジェクト</param>
/// <param name="object1">オブジェクト1</param>
void CollisionVisitor::DetectCollision(IObject* object, IObject* object1)
{
	// アタッチ中は衝突判定を行わない
	if (m_isActiveAttach) return;

	DirectX::BoundingSphere worldBoundingSphere;
	DirectX::BoundingSphere worldBoundingSphere1;

	// どちらかが非アクティブの場合判定を行わない
	if (!object->GetIsActive() || !object1->GetIsActive())
		return;

	// 部品番号から境界ボックスを検索する
	auto it = m_boundingSphere.find(object->GetObjectNumber());

	worldBoundingSphere.Center =
		DirectX::SimpleMath::Vector3::Transform(it->second->Center, object->GetTransform()->GetWorldMatrix());

	worldBoundingSphere.Radius = it->second->Radius;

	// 部品番号から境界ボックスを検索する
	it = m_boundingSphere.find(object1->GetObjectNumber());

	worldBoundingSphere1.Center =
		DirectX::SimpleMath::Vector3::Transform(it->second->Center, object1->GetTransform()->GetWorldMatrix());

	      
	worldBoundingSphere1.Radius = it->second->Radius;

	// 当たり判定を行う
	if (worldBoundingSphere.Intersects(worldBoundingSphere1))
	{
		// 衝突した場合,メッセージを送る 衝突相手の番号も一緒に送る
		ObjectMessenger::GetInstance()->Dispatch(object->GetObjectID(), object->GetObjectNumber(),
			{ Message::MessageID::ON_COLLISION , object1->GetObjectNumber(),static_cast<float>(object1->GetParent()->GetParent()->GetObjectNumber())});

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

/// <summary>
/// 境界球の描画
/// </summary>
/// <param name="primitiveBatch"></param>
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

/// <summary>
/// アタッチを開始
/// </summary>
void CollisionVisitor::Begin()
{
	// アタッチの許可
	m_isActiveAttach = true;
}

/// <summary>
/// アタッチ終了
/// </summary>
void CollisionVisitor::End()
{
	// アタッチの終了
	m_isActiveAttach = false;
}

/// <summary>
/// データのクリア
/// </summary>
void CollisionVisitor::Clear()
{
	m_boundingSphere.clear();
	m_worldBoundingSpheres.clear();
}