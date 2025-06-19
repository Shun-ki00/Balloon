// ============================================
// 
// ファイル名: Player.cpp
// 概要: プレイヤーオブジェクト
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/Player/Player.h"
#include "Game/Object/Object.h"
#include "Game/Node/Root.h"

#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Framework/Resources/ModelResources.h"
#include "Game/RenderableObjects/PlayerRenderableObject.h"

#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/BalloonFactory.h"

#include "Game/Buffers.h"

#include "Game/SteeringBehavior/WindBehavior.h"
#include "Game/SteeringBehavior/KnockbackBehavior.h"
#include "Game/SteeringBehavior/FloatBehavior.h"
#include "Game/SteeringBehavior/FloatForceBehavior.h"
#include "Game/SteeringBehavior/PushBackBehavior.h"

#include "Game/Message/ObjectMessenger.h"
#include "Game/Visitor/CollisionVisitor.h"
#include "Game/Parameters/Parameters.h"
#include "Game/Enemy/Enemy.h"
#include "Game/Balloon/Balloon.h"

// ステート
#include "Game/States/Player/PlayerIdleState.h"
#include "Game/States/Player/PlayerRunState.h"
#include "Game/States/Player/PlayerAttackState.h"
#include "Game/States/Player/PlayerSitState.h"

#include "Game/Status/BalloonScaleController.h"
#include "Game/Status/HpController.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="angle"></param>
/// <param name="position"></param>
/// <param name="messageID"></param>
Player::Player(IObject* root, IObject* parent, IObject::ObjectID objectID,
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

	// ステアリングビヘイビアのインスタンスを取得
	m_steeringBehavior = WindBehavior::GetInstance();

}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{

}


/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize()
{
	// ステートの作成
	m_playerIdleState   = std::make_unique<PlayerIdleState>();
	m_playerRunState    = std::make_unique<PlayerRunState>(this);
	m_playerAttackState = std::make_unique<PlayerAttackState>(this);
	m_playerSitState    = std::make_unique<PlayerSitState>(this);
	

	// 現在のステートを設定
	Object::SetState(m_playerSitState.get());

	// ノックバック
	m_knockbackBehavior = std::make_unique<KnockbackBehavior>(this);
	// 揺れる処理
	m_floatBehavior = std::make_unique<FloatBehavior>();
	m_floatBehavior->On();

	m_floatBehavior->Off();

	m_floatForceBehavior = std::make_unique<FloatForceBehavior>();
	m_floatForceBehavior->SetForceStrength(0.0f);

	m_pushBackBehavior = std::make_unique<PushBackBehavior>(this);

	// HPをコントロール
	m_hpController = std::make_unique<HpController>();
	m_hpController->Initialize();
	// 風船の大きさをコントロール
	m_balloonScaleController = std::make_unique<BalloonScaleController>(m_hpController.get(), m_floatForceBehavior.get());
	m_balloonScaleController->Initialize();
	
	// 体を追加する
	this->Attach(PlayerFactory::CreatePlayerBody(this,
		DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));

	// 風船を追加する
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{0.0f ,0.0f ,0.4f}, { -30.0f ,0.0f ,0.0f }, DirectX::SimpleMath::Vector3::One));
	// 風船を追加する
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ 1.0f ,0.0f ,0.5f }, {-30.0f ,0.0f ,26.0f}, DirectX::SimpleMath::Vector3::One));
	// 風船を追加する
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ -1.0f ,0.0f ,0.5f }, { -30.0f ,0.0f ,-26.0f }, DirectX::SimpleMath::Vector3::One));


	for (int i = 0; i < 3; i++)
	{
		// 風船のボディを取得
		m_balloonObject.push_back(dynamic_cast<Balloon*>(m_childs[i + 1].get())->GetBody());
	}

	// ステートの初期化処理
	m_playerIdleState->Initialize();
	m_playerRunState->Initialize();
	m_playerAttackState->Initialize();
	m_playerSitState->Initialize();

	// オブジェクトのカウントをリセット
	Object::ResetNumber();

	// 当たり判定を準備
	m_collisionVisitor->GetInstance()->StartPrepareCollision(this);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Player::Update(const float& elapsedTime)
{
	// 固定設定の場合
	if (m_isFixed)
	{
		m_floatBehavior->On();
		DirectX::SimpleMath::Vector3 acceleration = m_floatBehavior->Calculate();

		// 速度に加速度を加算する
		m_velocity += acceleration * elapsedTime;
		// 現在の位置を更新する
		m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);

		m_velocity = m_velocity * (1.0f - 2.0f * elapsedTime);

		// Transformの更新のみ行う
		m_transform->Update();

		// 子オブジェクトの更新処理
		for (const auto& child : m_childs)
		{
			child->Update(elapsedTime);
		}

		return;
	}

	m_knockbackBehavior->SetTargetObject(
		dynamic_cast<Object*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::ENEMY,1)));

	// 風船の大きさを更新処理
	m_balloonScaleController->Update(elapsedTime);
	// HPの更新処理
	m_hpController->Update(elapsedTime);

	// プレイヤーの高さをUIに渡す
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER_ICON_UI, { Message::MessageID::PLAYER_HEIGHT , 0,m_transform->GetLocalPosition().y,false });

	// オブジェクトの更新処理
	Object::Update(elapsedTime);

	// 操舵力から加速度を計算する
	DirectX::SimpleMath::Vector3 acceleration = 
		m_steeringBehavior->Calculate() + m_knockbackBehavior->Calculate() + 
		m_floatBehavior->Calculate() + m_floatForceBehavior->Calculate() + m_pushBackBehavior->Calculate();

	// 速度に加速度を加算する
	m_velocity += acceleration * elapsedTime;
	// 現在の位置を更新する
	m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);

	m_velocity = m_velocity * (1.0f - 2.0f * elapsedTime);

	// Transformの更新処理
	m_transform->Update();

	// 子オブジェクトの更新処理
	for (const auto& child : m_childs)
	{
		child->Update(elapsedTime);
	}

	// 当たり判定を行う
	for (int i = 0; i < Parameters::GetInstance()->GetParameter(ParametersID::ENEMY, ParameterKeysI::Number); i++)
	{
		auto enemy = dynamic_cast<Enemy*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::ENEMY, i + 1));

		for (const auto& balloon : enemy->GetBalloonObject())
		{
			m_collisionVisitor->DetectCollision(this, balloon);
		}
	}
}

/// <summary>
/// 終了処理
/// </summary>
void Player::Finalize()
{

}

/// <summary>
/// パーツを追加する
/// </summary>
/// <param name="object"></param>
void Player::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// パーツを削除する
/// </summary>
/// <param name="turretPart"></param>
void Player::Detach(std::unique_ptr<IObject> object)
{

}

/// <summary>
/// 子オブジェクトを取得する
/// </summary>
/// <returns>子オブジェクト</returns>
std::vector<IObject*> Player::GetChilds() const
{
	std::vector<IObject*> result;
	result.reserve(m_childs.size());
	for (const auto& child : m_childs)
	{
		result.push_back(child.get());
	}
	return result;
}



void Player::PrepareCollision(ICollisionVisitor* collision)
{
	// 今回プレイヤーのみの当たり判定なので再帰処理は行わない
	collision->PrepareCollision(this, DirectX::SimpleMath::Vector3::Up * 0.2f  , 0.3f);

	for (const auto& child : m_childs)
	{
		if (child->GetObjectID() == IObject::ObjectID::BALLOON)
			dynamic_cast<Balloon*>(child.get())->PrepareCollision(collision);
	}
}

void Player::DetectCollision(ICollisionVisitor* collision, IObject* bullets)
{
	// 判定を行う
	collision->DetectCollision(this, bullets);
}


/// <summary>
/// メッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
void Player::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{

		case Message::MessageID::PLAYER_IDLING:
			this->ChangeState(m_playerIdleState.get());
			break;
		case Message::MessageID::PLAYER_ATTCK:
			break;

		case Message::MessageID::ON_COLLISION:
			
			if (Object::GetState() == m_playerAttackState.get())
			{
				// 上向きのベクトルに変化する
				m_velocity.y = m_velocity.y * -1.0f;

				// 相手の風船を破棄する
				auto enemy = ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::BALLOON, messageData.dataInt)->GetParent();
				if (enemy->GetParent()->GetParent()->GetObjectID() == ObjectID::BALLOON)
				{
					// 敵のオブジェクトをキャストする
					enemy->SetIsActive(false);
				}

			}
			break;

		default:
			break;
	}
}


// 通知する
void Player::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	switch (key)
	{
		case DirectX::Keyboard::Keys::Up:

			if (type == KeyType::ON_KEY_DOWN)
			{
				if(Object::GetState() != m_playerRunState.get())
				Object::ChangeState(m_playerRunState.get());
				m_playerRunState->SetIsForward(true);
			}
			if (type == KeyType::ON_KEY_UP)
			{
				if (Object::GetState() == m_playerRunState.get())
					Object::ChangeState(m_playerIdleState.get());
			}
				

			break;
		case DirectX::Keyboard::Keys::Down:

			if (type == KeyType::ON_KEY_DOWN)
			{
				if (Object::GetState() != m_playerRunState.get())
					Object::ChangeState(m_playerRunState.get());
				m_playerRunState->SetIsBackward(true);
			}
			if (type == KeyType::ON_KEY_UP)
			{
				if (Object::GetState() == m_playerRunState.get())
					Object::ChangeState(m_playerIdleState.get());
			}

			break;
		case DirectX::Keyboard::Keys::Left:

			// プレイヤーに回転角を与える
			m_transform->SetLocalRotation(
				DirectX::SimpleMath::Quaternion::Concatenate(
					m_transform->GetLocalRotation(),
					DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
						DirectX::SimpleMath::Vector3::Up,
						DirectX::XMConvertToRadians(2.0f))
				)
			);

			break;
		case DirectX::Keyboard::Keys::Right:

			// プレイヤーに回転角を与える
			m_transform->SetLocalRotation(
				DirectX::SimpleMath::Quaternion::Concatenate(
					m_transform->GetLocalRotation(),
					DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
						DirectX::SimpleMath::Vector3::Up,
						DirectX::XMConvertToRadians(-2.0f))
				)
			);
			break;


		case DirectX::Keyboard::Keys::Space:

			if (type == KeyType::ON_KEY_DOWN)
			{
				// HPがあるなら有効化
				if (m_hpController->GetHp() <= 0.01f) break;
				m_balloonScaleController->On();
			}
			if (type == KeyType::ON_KEY_UP)
			{
				// 無効化
				m_balloonScaleController->Off();
			}
			break;

		case DirectX::Keyboard::Keys::Z:

			if (!m_hpController->HpReduction(0.1f))
				break;
		
			this->ChangeState(m_playerAttackState.get());

			break;

		default:
			break;
	}
}
