#include "pch.h"
#include "Game/Enemy/Enemy.h"
#include "Game/Buffers.h"
#include "Game/Factorys/EnemyFactory.h"
#include "Game/Factorys/BalloonFactory.h"
#include "Game/Balloon/Balloon.h"
#include "Game/Visitor/CollisionVisitor.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Player/Player.h"
// ステアリングビヘイビア
#include "Game/SteeringBehavior/SteeringBehavior.h"
#include "Game/SteeringBehavior/WindBehavior.h"
#include "Game/SteeringBehavior/KnockbackBehavior.h"
#include "Game/SteeringBehavior/FloatBehavior.h"
#include "Game/SteeringBehavior/FloatForceBehavior.h"
#include "Game/SteeringBehavior/PushBackBehavior.h"
#include "Game/SteeringBehavior/SeekBehavior.h"
// ステート
#include "Game/States/Enemy/EnemyIdleState.h"
#include "Game/States/Enemy/EnemyRunState.h"
#include "Game/States/Enemy/EnemyAttackState.h"
#include "Game/States/Enemy/EnemyWanderState.h"
#include "Game/States/Enemy/EnemyChaseState.h"
// ステータス
#include "Game/Status/BalloonScaleController.h"
#include "Game/Status/HpController.h"

#include "Game/Enemy/ActionSelection.h"
#include "Game/BehaviorTree/SelectorNode.h"
#include "Framework/Utilities/RandomUtilities.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="angle"></param>
/// <param name="position"></param>
/// <param name="messageID"></param>
Enemy::Enemy(IObject* root, IObject* parent, const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale, const float& balloonIndex,
	const FloatBehaviorParams& floatBehavior, const KnockbackBehaviorParams& knockbackBehavior, const SeekBehaviorParams& seekBehavior)
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
	m_balloonIndex(balloonIndex),
	m_parent(parent),
	m_floatBehaviorParams(floatBehavior),
	m_knockbackBehaviorParams(knockbackBehavior),
	m_seekBehaviorParams(seekBehavior),
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
	if (!m_isActive) return;

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

	// 風船の数がゼロになったら
	if (m_balloonIndex <= 0)
	{
		m_velocity = { 0.0f , -5.8f ,0.0f };

		// プレイヤーに回転角を与える
		m_transform->SetLocalRotation(
			DirectX::SimpleMath::Quaternion::Concatenate(
				m_transform->GetLocalRotation(),
				DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
					DirectX::SimpleMath::Vector3::UnitZ,
					DirectX::XMConvertToRadians(4.0f)) 
			)
		);

		m_transform->SetLocalRotation(
			DirectX::SimpleMath::Quaternion::Concatenate(
				m_transform->GetLocalRotation(),
				DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
					DirectX::SimpleMath::Vector3::UnitX,
					DirectX::XMConvertToRadians(-6.0f))
			)
		);

		m_transform->SetLocalRotation(
			DirectX::SimpleMath::Quaternion::Concatenate(
				m_transform->GetLocalRotation(),
				DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
					DirectX::SimpleMath::Vector3::UnitY,
					DirectX::XMConvertToRadians(-4.0f))
			)
		);

		if (m_transform->GetLocalPosition().y <= -30.0f)
		{
			m_isActive = false;
		}
	}

	// ノックバックビヘイビアを更新
	auto knockback = dynamic_cast<KnockbackBehavior*>(m_steeringBehavior->GetSteeringBehavior(BEHAVIOR_TYPE::KNOCK_BACK));
	knockback->ResetTargetObject();

	// 現在のプレイヤーを設定する
	knockback->SetTargetObject(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER));
	// 敵を設定する
	for (const auto& enemy : ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::ENEMY))
	{
		if (enemy == this) continue;

		knockback->SetTargetObject(enemy);
	}

	// アクションを決定する
	//m_actionSelection->GetRootNode()->Tick();

	// オブジェクトの更新処理
	//Object::Update(elapsedTime);

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
/// 子オブジェクトを取得する
/// </summary>
/// <returns>子オブジェクト</returns>
std::vector<IObject*> Enemy::GetChilds() const
{
	std::vector<IObject*> result;
	result.reserve(m_childs.size());
	for (const auto& child : m_childs)
	{
		result.push_back(child.get());
	}
	return result;
}

/// <summary>
/// メッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
void Enemy::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		// 風船削除処理
		case Message::MessageID::BALLOON_LOST:
			this->BalloonLost(messageData.dataInt, static_cast<int>(messageData.dataFloat));
			break;
			// 衝突した時の処理
		case Message::MessageID::ON_COLLISION:
			if (Object::GetState() == m_enemyAttackState.get())
			ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER, messageData.dataFloat,
				{ Message::MessageID::BALLOON_LOST,messageData.dataInt,messageData.dataFloat,false });
			break;
			// Y軸で逆ベクトルにする
		case Message::MessageID::INVERT_Y_VECTOR:
			m_velocity.y = m_velocity.y * -1.0f;
			break;
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
/// 風船削除処理
/// </summary>
/// <param name="balloonObjectNumber">風船の番号</param>
/// <param name="playerObjectNumber">プレイヤーの番号</param>
void Enemy::BalloonLost(const int& balloonObjectNumber, const int& playerObjectNumber)
{
	// 風船のオブジェクトIDをもとに非アクティブにする
	for (const auto& balloon : m_balloonObject)
	{
		// 番号と風船がアクティブ状態でない場合スキップ
		if (balloon->GetObjectNumber() != balloonObjectNumber ||
			!balloon->GetParent()->GetIsActive()) continue;

		// 非アクティブにする
		balloon->GetParent()->SetIsActive(false);
		// 風船の数を減らす
		m_balloonIndex--;
		// 当たったオブジェクト
		ObjectMessenger::GetInstance()->Dispatch(
			IObject::ObjectID::PLAYER, { Message::MessageID::INVERT_Y_VECTOR });
		break;
	}
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
	std::unique_ptr<KnockbackBehavior> knockback = std::make_unique<KnockbackBehavior>(this,
		m_knockbackBehaviorParams.radius,m_knockbackBehaviorParams.count,m_knockbackBehaviorParams.force);
	m_steeringBehavior->Attach(BEHAVIOR_TYPE::KNOCK_BACK, std::move(knockback));

	// 揺れるビヘイビア
	std::unique_ptr<FloatBehavior> floatBehavior = std::make_unique<FloatBehavior>(
		m_floatBehaviorParams.floatRange,m_floatBehaviorParams.floatCycleSpeed,m_floatBehaviorParams.floatSpeed,
		m_floatBehaviorParams.direction
	);
	m_steeringBehavior->Attach(BEHAVIOR_TYPE::FLOATING, std::move(floatBehavior));

	// 力を加えるビヘイビア
	std::unique_ptr<FloatForceBehavior> floatForce = std::make_unique<FloatForceBehavior>();
	floatForce->SetForceStrength(0.0f);
	floatForce->SetForceDirection(DirectX::SimpleMath::Vector3::Up);
	m_steeringBehavior->Attach(BEHAVIOR_TYPE::FLOAT_FORCE, std::move(floatForce));

	// ステージ内に押し戻すビヘイビア
	std::unique_ptr<PushBackBehavior> pushBack = std::make_unique<PushBackBehavior>(this);
	m_steeringBehavior->Attach(BEHAVIOR_TYPE::PUSH_BACK, std::move(pushBack));

	std::unique_ptr<SeekBehavior> seekBehavior = std::make_unique<SeekBehavior>(
		this, dynamic_cast<Object*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER)[0]),
		m_seekBehaviorParams.offset,m_seekBehaviorParams.predictionMultiplier,m_seekBehaviorParams.seekSpeed
		);
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
		{ 0.0f ,5.9f ,0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));

	// 風船を追加する
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ 0.0f ,10.0f ,0.2f }, { -20.0f ,0.0f ,0.0f }, DirectX::SimpleMath::Vector3::One,static_cast<float>(RandomUtilities::RandomInt(0, 5))));
	// 風船を追加する
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ 0.9f ,10.0f ,0.0f }, { -0.0f ,0.0f ,16.0f }, DirectX::SimpleMath::Vector3::One, static_cast<float>(RandomUtilities::RandomInt(0, 5))));
	// 風船を追加する
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ -0.9f ,10.0f ,0.0f }, { -0.0f ,0.0f ,-16.0f }, DirectX::SimpleMath::Vector3::One, static_cast<float>(RandomUtilities::RandomInt(0, 5))));

	// 風船のボディを取得
	for (int i = 0; i < 3; i++)
		m_balloonObject.push_back(dynamic_cast<Balloon*>(m_childs[i + 1].get())->GetBody());

	// オブジェクトのカウントをリセット
	Object::ResetNumber();
}