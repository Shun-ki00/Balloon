#include "pch.h"
#include "Game/Enemy/Enemy.h"
#include "Game/Object/Object.h"
#include "Interface/IComposite.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Game/Buffers.h"
#include "Game/Factorys/EnemyFactory.h"
#include "Game/Factorys/BalloonFactory.h"
#include "Game/Balloon/Balloon.h"
#include "Game/Visitor/CollisionVisitor.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Player/Player.h"

#include "Game/SteeringBehavior/WindBehavior.h"
#include "Game/SteeringBehavior/KnockbackBehavior.h"
#include "Game/SteeringBehavior/FloatBehavior.h"
#include "Game/SteeringBehavior/FloatForceBehavior.h"
#include "Game/SteeringBehavior/PushBackBehavior.h"
#include "Game/SteeringBehavior/SeekBehavior.h"

#include "Game/Status/BalloonScaleController.h"
#include "Game/Status/HpController.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="angle"></param>
/// <param name="position"></param>
/// <param name="messageID"></param>
Enemy::Enemy(IObject* root, IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale,
	Message::MessageID messageID)
	:
	// 基底クラス
	Object(
		0.0f,
		0.0f,
		0.0f,
		0.0f
	),
	m_isActive(true),
	m_objectNumber(root->GetObjectNumber() + Object::CountUpNumber()),
	m_objectID(objectID),
	m_messageID(messageID),
	m_parent(parent),
	m_transform{},
	m_childs {}
{

	m_collisionVisitor = CollisionVisitor::GetInstance();

	// ステアリングビヘイビアのインスタンスを取得
	m_steeringBehavior = WindBehavior::GetInstance();

	// Transformを作成
	m_transform = std::make_unique<Transform>();
	
	// 初期座標設定
	m_transform->SetLocalPosition(position);
	// 初期回転設定
	m_transform->SetLocalRotation(rotation);
	// 初期スケール設定
	m_transform->SetLocalScale(scale);

	// 親がいる場合親を設定
	if (parent != nullptr)
		m_transform->SetParent(parent->GetTransform());
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{

}


/// <summary>
/// 初期化処理
/// </summary>
void Enemy::Initialize()
{
	// 当たり判定の初期座標を設定
	m_boundingSphere.Center = m_transform->GetLocalPosition();
	// 当たり判定の大きさを設定
	m_boundingSphere.Radius = 2.0f;

	// ノックバック
	m_knockbackBehavior = std::make_unique<KnockbackBehavior>(this);
	// 揺れる処理
	m_floatBehavior = std::make_unique<FloatBehavior>();
	m_floatBehavior->On();

	m_floatBehavior->Off();

	m_floatForceBehavior = std::make_unique<FloatForceBehavior>();
	m_floatForceBehavior->SetForceStrength(0.0f);

	m_pushBackBehavior = std::make_unique<PushBackBehavior>(this);

	m_seekBehavior = std::make_unique<SeekBehavior>(this, dynamic_cast<Object*>( ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER,0)));

	// 体を追加する
	this->Attach(EnemyFactory::CreateEnemyBody(this,
		DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));

	// 風船を追加する
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		DirectX::SimpleMath::Vector3::Left * -1.0f, DirectX::SimpleMath::Vector3::Backward * 25.0f, DirectX::SimpleMath::Vector3::One));
	// 風船を追加する
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		DirectX::SimpleMath::Vector3::Right * -1.0f, DirectX::SimpleMath::Vector3::Forward * 25.0f, DirectX::SimpleMath::Vector3::One));
	// 風船を追加する
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
	

	for (int i = 0; i < 3; i++)
	{
		// 風船のボディを取得
		m_balloonObject.push_back(dynamic_cast<Balloon*>(m_childs[i + 1].get())->GetBody());
	}

	// HPをコントロール
	m_hpController = std::make_unique<HpController>();
	m_hpController->Initialize();
	// 風船の大きさをコントロール
	m_balloonScaleController = std::make_unique<BalloonScaleController>(m_hpController.get(), m_floatForceBehavior.get());
	m_balloonScaleController->Initialize();

	// オブジェクトのカウントをリセット
	Object::ResetNumber();

	// 当たり判定を準備する
	m_collisionVisitor->StartPrepareCollision(this);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Enemy::Update(const float& elapsedTime)
{
	(void)elapsedTime;

	m_knockbackBehavior->SetTargetObject(
		dynamic_cast<Object*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER, 0)));

	// ビヘイビアツリーの更新処理

	// ステアリングビヘイビアの更新処理


	// 現在の位置を更新する
	m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);

	m_velocity = m_velocity * (1.0f - 2.0f * elapsedTime);

	// Transformの更新処理
	m_transform->Update();

	// 風船の大きさを更新処理
	m_balloonScaleController->Update(elapsedTime);
	// HPの更新処理
	m_hpController->Update(elapsedTime);

	// 子オブジェクトの更新処理
	for (const auto& child : m_childs)
	{
		child->Update(elapsedTime);
	}

	// 当たり判定を行う
	auto player = dynamic_cast<Player*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER,0));
	for (const auto& balloon : player->GetBalloonObject())
	{
		m_collisionVisitor->DetectCollision(this, balloon);
	}
}

/// <summary>
/// 終了処理
/// </summary>
void Enemy::Finalize()
{

}

/// <summary>
/// パーツを追加する
/// </summary>
/// <param name="object"></param>
void Enemy::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// パーツを削除する
/// </summary>
/// <param name="turretPart"></param>
void Enemy::Detach(std::unique_ptr<IObject> object)
{

}

/// <summary>
/// メッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
void Enemy::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		case Message::MessageID::ON_COLLISION:

			if (true)
			{
				// 上向きのベクトルに変化する
				m_velocity.y = m_velocity.y * -1.0f;

				// 相手の風船を破棄する
				auto enemy = ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::BALLOON, messageData.dataInt)->GetParent();

				if(enemy == nullptr)
					enemy = ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::ENEMY, messageData.dataInt);

				// 敵のオブジェクトをキャストする
				enemy->SetIsActive(false);
			}

			break;
		default:
			break;
	}
}

// 通知する
void Enemy::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

// 衝突判定を準備する
void Enemy::PrepareCollision(ICollisionVisitor* collision)
{
	collision->PrepareCollision(this, DirectX::SimpleMath::Vector3::Up * 0.2f, 0.3f);

	for (const auto& child : m_childs)
	{
		if (child->GetObjectID() == IObject::ObjectID::BALLOON)
			dynamic_cast<Balloon*>(child.get())->PrepareCollision(collision);
	}

}

// 衝突判定する
void Enemy::DetectCollision(ICollisionVisitor* collision, IObject* object)
{
	// 判定を行う
	collision->DetectCollision(this, object);
}
