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

#include "Interface/ISteeringBehavior.h"
#include "Game/SteeringBehavior/WindBehavior.h"
#include "Game/SteeringBehavior/KnockbackBehavior.h"
#include "Game/SteeringBehavior/FloatBehavior.h"
#include "Game/SteeringBehavior/FloatForceBehavior.h"
#include "Game/SteeringBehavior/PushBackBehavior.h"
#include "Game/SteeringBehavior/SeekBehavior.h"
#include "Game/SteeringBehavior/SteeringBehavior.h"

#include "Game/States/Enemy/EnemyIdleState.h"
#include "Game/States/Enemy/EnemyRunState.h"
#include "Game/States/Enemy/EnemyAttackState.h"
#include "Game/States/Enemy/EnemyWanderState.h"
#include "Game/States/Enemy/EnemyChaseState.h"

#include "Game/Status/BalloonScaleController.h"
#include "Game/Status/HpController.h"

#include "Game/Enemy/ActionSelection.h"
#include "Game/BehaviorTree/SelectorNode.h"


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
	m_childs {},
	m_isFixed{}
{

	m_collisionVisitor = CollisionVisitor::GetInstance();

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
	
	// オブジェクトを追加する
	this->AttachObject();
	// ステアリングビヘイビアを作成する
	this->CreateSteeringBehavior();
	// ステートを作成する
	this->CreateState();

	// ==== ステータスの作成と初期化処理 ====

	// HPをコントロール
	m_hpController = std::make_unique<HpController>();
	m_hpController->Initialize();
	// 風船の大きさをコントロール
	m_balloonScaleController = std::make_unique<BalloonScaleController>(
		m_hpController.get(),dynamic_cast<FloatForceBehavior*>( m_steeringBehavior->GetSteeringBehavior(BEHAVIOR_TYPE::FLOAT_FORCE)));
	m_balloonScaleController->Initialize();


	// ==== アクションセレクター ====

	m_actionSelection = std::make_unique<ActionSelection>();
	m_actionSelection->Initialize(this);


	// ==== 当たり判定 ====

	// 当たり判定の作成
	m_boundingSphere = std::make_unique<DirectX::BoundingSphere>();
	// 初期化
	m_boundingSphere->Center = DirectX::SimpleMath::Vector3::Up * 0.2f;
	m_boundingSphere->Radius = 0.3f;

	// 当たり判定を準備する
	m_collisionVisitor->StartPrepareCollision(this);

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Enemy::Update(const float& elapsedTime)
{
	// プレイヤーが固定状態の場合
	if (m_isFixed)
	{
		// 徘徊状態にする
		this->ChangeState(m_enemyWanderState.get());

		// 風船の大きさを更新処理
		m_balloonScaleController->Update(elapsedTime);
		// HPの更新処理
		m_hpController->Update(elapsedTime);

		float result = m_balloonScaleController->GetBalloonScale() * 6.0f - 3.0f;
		dynamic_cast<FloatForceBehavior*>(m_steeringBehavior->GetSteeringBehavior(BEHAVIOR_TYPE::FLOAT_FORCE))->SetForceStrength(result);

		// Transformの更新処理
		m_transform->Update();

		// 風船の大きさを設定する
		for (const auto& balloon : m_balloonObject)
		{
			balloon->GetParent()->OnMessegeAccepted({ Message::MessageID::BALLOON_SCALE ,0,m_balloonScaleController->GetBalloonScale(),false });
		}

		// 子オブジェクトの更新処理
		for (const auto& child : m_childs)
		{
			child->Update(elapsedTime);
		}

		return;
	}
	// アクションを決定する
	m_actionSelection->GetRootNode()->Tick();

	// オブジェクトの更新処理
	Object::Update(elapsedTime);

	// ==== ステータスの更新処理 ====

	// 風船の大きさを更新処理
	m_balloonScaleController->Update(elapsedTime);
	// HPの更新処理
	m_hpController->Update(elapsedTime);

	float result = m_balloonScaleController->GetBalloonScale() * 6.0f - 3.0f;
	dynamic_cast<FloatForceBehavior*>(m_steeringBehavior->GetSteeringBehavior(BEHAVIOR_TYPE::FLOAT_FORCE))->SetForceStrength(result);

	
	// 操舵力から加速度を計算する
	DirectX::SimpleMath::Vector3 acceleration = m_steeringBehavior->Calculate(elapsedTime);
	// 速度に加速度を加算する
	m_velocity += acceleration * elapsedTime;
	// 現在の位置を更新する
	m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);

	m_velocity = m_velocity * (1.0f - 2.0f * elapsedTime);

	// Transformの更新処理
	m_transform->Update();


	// ==== 子オブジェクトの更新処理 ====

	// 子オブジェクトの更新処理
	for (const auto& child : m_childs)
	{
		child->Update(elapsedTime);
	}

	// 風船の大きさを設定する
	for (const auto& balloon : m_balloonObject)
	{
		balloon->GetParent()->OnMessegeAccepted({ Message::MessageID::BALLOON_SCALE ,0,m_balloonScaleController->GetBalloonScale(),false });
	}


	// ==== 衝突判定の更新 ====

	// 当たり判定を行う
	auto player = dynamic_cast<Player*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER)[0]);
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

		case Message::MessageID::ENEMY_ON_BALLOON_SCALE:
			// HPがあるなら有効化
			if (m_hpController->GetHp() <= 0.01f) break;
			m_balloonScaleController->On();
			break;

		case Message::MessageID::ENEMY_OFF_BALLOON_SCALE:
			m_balloonScaleController->Off();
			break;

		case Message::MessageID::ENEMY_IDLING:
			Object::ChangeState(m_enemyIdleState.get());
			break;
		case Message::MessageID::ENEMY_WANDER:
			if (Object::GetState() != m_enemyAttackState.get())
			Object::ChangeState(m_enemyWanderState.get());
			break;
		case Message::MessageID::ENEMY_CHASE:
			if (Object::GetState() != m_enemyAttackState.get())
			Object::ChangeState(m_enemyChaseState.get());
		case Message::MessageID::ENEMY_ATTACK:
			if(Object::GetState() != m_enemyAttackState.get())
			Object::ChangeState(m_enemyAttackState.get());
			break;

		case Message::MessageID::FIXED:
			m_isFixed = messageData.dataBool;
			break;
		default:
			break;
	}
}

/// <summary>
/// キーボードの通知を受け取る
/// </summary>
/// <param name="type">キーボードタイプ</param>
/// <param name="key">キー</param>
void Enemy::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

/// <summary>
/// 衝突判定を準備する
/// </summary>
/// <param name="collision">当たり判定処理</param>
void Enemy::PrepareCollision(ICollisionVisitor* collision)
{
	collision->PrepareCollision(this,m_boundingSphere.get());

	for (const auto& child : m_childs)
	{
		if (child->GetObjectID() == IObject::ObjectID::BALLOON)
			dynamic_cast<Balloon*>(child.get())->PrepareCollision(collision);
	}

}

/// <summary>
/// 衝突判定する
/// </summary>
/// <param name="collision">当たり判定処理</param>
/// <param name="object">対象のオブジェクト</param>
void Enemy::DetectCollision(ICollisionVisitor* collision, IObject* object)
{
	// 判定を行う
	collision->DetectCollision(this, object);
}


/// <summary>
/// ステートを作成する
/// </summary>
void Enemy::CreateState()
{
	// ステートの作成
	m_enemyIdleState = std::make_unique<EnemyIdleState>();
	m_enemyRunState = std::make_unique<EnemyRunState>(this);
	m_enemyAttackState = std::make_unique<EnemyAttackState>(this);
	m_enemyWanderState = std::make_unique<EnemyWanderState>(this);
	m_enemyChaseState = std::make_unique<EnemyChaseState>(
		dynamic_cast<Object*>(this), dynamic_cast<Object*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER)[0]),
		m_steeringBehavior.get(), dynamic_cast<SeekBehavior*>(m_steeringBehavior->GetSteeringBehavior(BEHAVIOR_TYPE::SEEK))
	);

	// ステートの初期化処理
	m_enemyIdleState->Initialize();
	m_enemyRunState->Initialize();
	m_enemyAttackState->Initialize();
	m_enemyWanderState->Initialize();
	m_enemyChaseState->Initialize();

	// 初期ステートにアイドル状態を設定
	Object::SetState(m_enemyIdleState.get());
}


/// <summary>
/// ステアリングビヘイビアを作成する
/// </summary>
void Enemy::CreateSteeringBehavior()
{
	// ステアリングビヘイビアの追加
	m_steeringBehavior = std::make_unique<SteeringBehavior>();
	m_steeringBehavior->Initialize();

	// ノックバックビヘイビア
	std::unique_ptr<KnockbackBehavior> knockback = std::make_unique<KnockbackBehavior>(this);
	m_steeringBehavior->Attach(BEHAVIOR_TYPE::KNOCK_BACK, std::move(knockback));

	// 揺れるビヘイビア
	std::unique_ptr<FloatBehavior> floatBehavior = std::make_unique<FloatBehavior>();
	m_steeringBehavior->Attach(BEHAVIOR_TYPE::FLOATING, std::move(floatBehavior));

	// 力を加えるビヘイビア
	std::unique_ptr<FloatForceBehavior> floatForce = std::make_unique<FloatForceBehavior>();
	floatForce->SetForceStrength(0.0f);
	floatForce->SetForceDirection(DirectX::SimpleMath::Vector3::Up);
	m_steeringBehavior->Attach(BEHAVIOR_TYPE::FLOAT_FORCE, std::move(floatForce));

	// ステージ内に押し戻すビヘイビア
	std::unique_ptr<PushBackBehavior> pushBack = std::make_unique<PushBackBehavior>(this);
	m_steeringBehavior->Attach(BEHAVIOR_TYPE::PUSH_BACK, std::move(pushBack));

	std::unique_ptr<SeekBehavior> seekBehavior = std::make_unique<SeekBehavior>(this, dynamic_cast<Object*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER)[0]));
	
	m_steeringBehavior->Attach(BEHAVIOR_TYPE::SEEK, std::move(seekBehavior));


	m_steeringBehavior->Off(BEHAVIOR_TYPE::FLOATING);
}

/// <summary>
/// オブジェクトをアタッチする
/// </summary>
void Enemy::AttachObject()
{
	// 体を追加する
	this->Attach(EnemyFactory::CreateEnemyBody(this,
		DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));

	// 風船を追加する
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ 0.0f ,10.0f ,0.2f }, { -20.0f ,0.0f ,0.0f }, DirectX::SimpleMath::Vector3::One));
	// 風船を追加する
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ 0.9f ,10.0f ,0.0f }, { -0.0f ,0.0f ,16.0f }, DirectX::SimpleMath::Vector3::One));
	// 風船を追加する
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ -0.9f ,10.0f ,0.0f }, { -0.0f ,0.0f ,-16.0f }, DirectX::SimpleMath::Vector3::One));

	// 風船のボディを取得
	for (int i = 0; i < 3; i++)
		m_balloonObject.push_back(dynamic_cast<Balloon*>(m_childs[i + 1].get())->GetBody());

	// オブジェクトのカウントをリセット
	Object::ResetNumber();
}