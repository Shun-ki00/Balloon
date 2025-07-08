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
#include "Game/SteeringBehavior/SteeringBehavior.h"

#include "Game/Message/ObjectMessenger.h"
#include "Game/Visitor/CollisionVisitor.h"
#include "Game/Parameters/Parameters.h"
#include "Game/Enemy/Enemy.h"
#include "Game/Balloon/Balloon.h"
#include "Game/Player/Body.h"
#include "Framework/SceneManager.h"
// ステート
#include "Game/States/Player/PlayerIdleState.h"
#include "Game/States/Player/PlayerRunState.h"
#include "Game/States/Player/PlayerAttackState.h"
#include "Game/States/Player/PlayerSitState.h"
// ステータス
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
	const DirectX::SimpleMath::Vector3& scale, const float& balloonIndex)
	:
	// 基底クラス
	Object(
		0.0f,
		0.0f,
		0.0f,
		0.0f
	),
	m_collisionVisitor{},
	m_isActive(true),
	m_objectNumber(root->GetObjectNumber() + Object::CountUpNumber()),
	m_objectID(objectID),
	m_balloonIndex(balloonIndex),
	m_transform{},
	m_parent(parent),
	m_childs {},
	m_boundingSphere{},
	m_balloonObject{},
	m_velocity{},
	m_heading{},
	m_side{},
	m_acceralation{},
	m_steeringBehavior{},
	m_playerIdleState{},
	m_playerRunState{},
	m_playerAttackState{},
	m_playerSitState{},
	m_balloonScaleController{},
	m_hpController{},
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
	//m_steeringBehavior = WindBehavior::GetInstance();

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
	// オブジェクトをアタッチする
	this->AttachObject();
	// ステアリングビヘイビアを作成する
	this->CreateSteeringBehavior();
	// ステートを作成する
	this->CreateState();

	// 当たり判定の作成
	m_boundingSphere = std::make_unique<DirectX::BoundingSphere>();
	// 初期化
	m_boundingSphere->Center = DirectX::SimpleMath::Vector3::Up * 0.2f;
	m_boundingSphere->Radius = 0.3f;
	
	// HPをコントロール
	m_hpController = std::make_unique<HpController>();
	m_hpController->Initialize();
	// 風船の大きさをコントロール
	m_balloonScaleController = std::make_unique<BalloonScaleController>(
		m_hpController.get(),dynamic_cast<FloatForceBehavior*>( m_steeringBehavior->GetSteeringBehavior(BEHAVIOR_TYPE::FLOAT_FORCE)));
	m_balloonScaleController->Initialize();

	// 現在のステートを設定
	Object::SetState(m_playerIdleState.get());
	// 当たり判定を準備
	m_collisionVisitor->GetInstance()->StartPrepareCollision(this);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Player::Update(const float& elapsedTime)
{
	// プレイヤーが固定状態の場合
	if (m_isFixed)
	{
		FloatBehavior* floatBehavior = dynamic_cast<FloatBehavior*>(m_steeringBehavior->GetSteeringBehavior(BEHAVIOR_TYPE::FLOATING));

		floatBehavior->On();
		DirectX::SimpleMath::Vector3 acceleration = floatBehavior->Calculate();

		// 速度に加速度を加算する
		m_velocity += acceleration * elapsedTime;
		// 現在の位置を更新する
		m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);

		m_velocity = m_velocity * (1.0f - 2.0f * elapsedTime);

		// Transformの更新のみ行う
		m_transform->Update();

		// 風船の大きさを更新処理
		m_balloonScaleController->Update(elapsedTime);
		// HPの更新処理
		m_hpController->Update(elapsedTime);


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

	if (m_balloonIndex <= 0)
	{
		m_velocity = { 0.0f ,-3.0f ,0.0f };

		if (m_transform->GetLocalPosition().y <= -10.0f)
		{
			SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_GAME_OVER_SCENE);
		}
	}

	// 風船の大きさを更新処理
	m_balloonScaleController->Update(elapsedTime);
	// HPの更新処理
	m_hpController->Update(elapsedTime);


	// 風船の大きさをUIに渡す
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::BALLOON_HP_UI,
		{ Message::MessageID::BALLOON_SCALE , 0,m_balloonScaleController->GetBalloonScale(),false});
	// HPをUIへ通知
	ObjectMessenger::GetInstance()->Dispatch(
		IObject::ObjectID::HP_GAUGE_UI,
		{ Message::MessageID::HP_GAUGE, 0, m_hpController->GetHp(), false } 
	);
	// プレイヤーの高さをUIに渡す
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER_ICON_UI, { Message::MessageID::PLAYER_HEIGHT , 0,m_transform->GetLocalPosition().y,false });

	float result = m_balloonScaleController->GetBalloonScale() * 6.0f - 3.0f;
	dynamic_cast<FloatForceBehavior*>(m_steeringBehavior->GetSteeringBehavior(BEHAVIOR_TYPE::FLOAT_FORCE))->SetForceStrength(result);

	// オブジェクトの更新処理
	Object::Update(elapsedTime);

	// 操舵力から加速度を計算する
	DirectX::SimpleMath::Vector3 acceleration = m_steeringBehavior->Calculate(elapsedTime);
	// 速度に加速度を加算する
	m_velocity += acceleration * elapsedTime;
	// 現在の位置を更新する
	m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);

	m_velocity = m_velocity * (1.0f - 2.0f * elapsedTime);

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

	// 当たり判定を行う

	// 敵を取得する
	auto enemys =
		ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::ENEMY);
	for (const auto& enemy : enemys)
	{	
		// プレイヤーと敵の風船の当たり判定を行う
		for (const auto& balloon : dynamic_cast<Enemy*>(enemy)->GetBalloonObject())
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


/// <summary>
/// 当たり判定を準備する
/// </summary>
/// <param name="collision"></param>
void Player::PrepareCollision(ICollisionVisitor* collision)
{
	// 今回プレイヤーのみの当たり判定なので再帰処理は行わない
	collision->PrepareCollision(this, m_boundingSphere.get());

	for (const auto& child : m_childs)
	{
		if (child->GetObjectID() == IObject::ObjectID::BALLOON)
			dynamic_cast<Balloon*>(child.get())->PrepareCollision(collision);
	}
}

/// <summary>
/// 当たり判定を行う
/// </summary>
/// <param name="collision"></param>
/// <param name="bullets"></param>
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
		// アイドルステートに変更する
		case Message::MessageID::PLAYER_IDLING:
			this->ChangeState(m_playerIdleState.get());
			break;
		// アタックステートに変更する
		case Message::MessageID::PLAYER_ATTCK:
			this->ChangeState(m_playerAttackState.get());
			break;
		// 風船削除処理
		case Message::MessageID::BALLOON_LOST:
			this->BalloonLost(messageData.dataInt,static_cast<int>(messageData.dataFloat));
			break;
		// Y軸で逆ベクトルにする
		case Message::MessageID::INVERT_Y_VECTOR:
			m_velocity.y = m_velocity.y * -1.0f;
			break;
		// 衝突した時の処理
		case Message::MessageID::ON_COLLISION:
			if(Object::GetState() == m_playerAttackState.get())
			ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::ENEMY, messageData.dataFloat,
				{ Message::MessageID::BALLOON_LOST,messageData.dataInt,messageData.dataFloat,false });
			break;
		// 固定処理
		case Message::MessageID::FIXED :

			// 固定すかどうかの処理
			m_isFixed = messageData.dataBool;
			// 指定のビヘイビア状態を変更
			if (messageData.dataBool)
			{
				m_steeringBehavior->Off(BEHAVIOR_TYPE::PUSH_BACK);
				m_steeringBehavior->Off(BEHAVIOR_TYPE::FLOAT_FORCE);

				m_steeringBehavior->On(BEHAVIOR_TYPE::FLOATING);
			}
			else
			{
				m_steeringBehavior->On(BEHAVIOR_TYPE::PUSH_BACK);
				m_steeringBehavior->On(BEHAVIOR_TYPE::FLOAT_FORCE);

				m_steeringBehavior->Off(BEHAVIOR_TYPE::FLOATING);
			}
			break;
		// プレイヤーのタイトルシーンでのアニメーション再生
		case Message::MessageID::PLAYER_TITLE_ANIMATION:
			this->PlayAnimationTitle();
			break;
		// ゲームオーバー時のアニメーション再生
		case Message::MessageID::PLAYER_SIT_ANIMATION:
			this->PlayAnimationFailed();
			break;
		// ゲームクリア時のアニメーション再生
		case Message::MessageID::PLAYER_CLEAR_ANIMATION:
			this->PlayAnimationClear();
			break;

		default:
			break;
	}
}


/// <summary>
/// キーボードの通知を受け取る
/// </summary>
/// <param name="type">キータイプ</param>
/// <param name="key">キー</param>
void Player::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	if (m_isFixed) return;

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


/// <summary>
/// 風船削除処理
/// </summary>
/// <param name="balloonObjectNumber">風船の番号</param>
/// <param name="enemyObjectNumber">敵の番号</param>
void Player::BalloonLost(const int& balloonObjectNumber, const int& enemyObjectNumber)
{
	// 風船のオブジェクトIDをもとに非アクティブにする
	for (const auto& balloon : m_balloonObject)
	{
		// 番号と風船がアクティブ状態でない場合スキップ
		if (balloon->GetObjectNumber() == balloonObjectNumber &&
			!balloon->GetParent()->GetIsActive()) continue;

		// 非アクティブにする
		balloon->GetParent()->SetIsActive(false);
		// 風船の数を減らす
		m_balloonIndex--;
		// 当たったオブジェクト
		ObjectMessenger::GetInstance()->Dispatch(
			IObject::ObjectID::ENEMY,
			enemyObjectNumber, Message::MessageID::INVERT_Y_VECTOR);
		break;
	}
}

/// <summary>
/// タイトルシーン時のアニメーション再生
/// </summary>
void Player::PlayAnimationTitle()
{
	using namespace DirectX::SimpleMath;

	// 体の回転角を決定
	dynamic_cast<Body*>(m_childs[0].get())->GetTransform()->GetTween()->DORotation({ 0.0f ,-10.0f ,0.0f }, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
	// 左足の回転角を決定
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[2]->GetTransform()->SetLocalRotation(Quaternion::CreateFromAxisAngle(Vector3::UnitX, DirectX::XMConvertToRadians(20.0f)));
	// 右足の回転角を決定
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[4]->GetTransform()->SetLocalRotation(Quaternion::CreateFromAxisAngle(Vector3::UnitX, DirectX::XMConvertToRadians(-20.0f)));

	// 頭のアニメーション
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[0]->GetTransform()->GetTween()->DORotation({ -5.0f ,-10.0f ,0.0f }, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
	// 右腕のアニメーション
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[3]->GetTransform()->GetTween()->DORotation({ -45.0f ,0.0f ,-85.0f }, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
	// 左腕のアニメーション
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[1]->GetTransform()->GetTween()->DORotation({ -100.0f ,-60.0f ,0.0f }, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
	// 左足のアニメーション
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[2]->GetTransform()->GetTween()->DORotation({ -20.0f , 0.0f ,0.0f }, 0.3f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
	// 右足のアニメーション
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[4]->GetTransform()->GetTween()->DORotation({ 20.0f , 0.0f ,0.0f }, 0.3f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);

}

/// <summary>
/// ゲームクリア時のアニメーション再生
/// </summary>
void Player::PlayAnimationClear()
{
	using namespace DirectX::SimpleMath;

	// 頭のアニメーション
	// dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[0]->GetTransform()->GetTween()->DORotation({ -5.0f ,-10.0f ,0.0f }, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
	// 右腕のアニメーション
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[3]->GetTransform()->GetTween()->DORotation({ -120.0f ,-10.0f ,0.0f }, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
	// 左腕のアニメーション
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[1]->GetTransform()->GetTween()->DORotation({ -120.0f ,10.0f ,0.0f }, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
	// 左足のアニメーション
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[2]->GetTransform()->GetTween()->DORotation({ 0.0f , 0.0f ,45.0f }, 0.3f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
	// 右足のアニメーション
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[4]->GetTransform()->GetTween()->DORotation({ 0.0f , 0.0f ,-45.0f }, 0.3f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);

}

/// <summary>
/// ゲームオーバー時のアニメーション再生
/// </summary>
void Player::PlayAnimationFailed()
{
	using namespace DirectX::SimpleMath;

	// 左右の足を90度曲げる
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[2]->GetTransform()->SetLocalRotation(Quaternion::CreateFromAxisAngle(Vector3::UnitX, DirectX::XMConvertToRadians(-90.0f)));
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[4]->GetTransform()->SetLocalRotation(Quaternion::CreateFromAxisAngle(Vector3::UnitX, DirectX::XMConvertToRadians(-90.0f)));

	// 頭を少し下げる
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[0]->GetTransform()->SetLocalRotation(
		Quaternion::CreateFromAxisAngle(Vector3::UnitX, DirectX::XMConvertToRadians(10.0f)) *
		Quaternion::CreateFromAxisAngle(Vector3::UnitY, DirectX::XMConvertToRadians(-20.0f))
	);

	// 右腕のアニメーション
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[3]->GetTransform()->GetTween()->DORotation({ 0.0f ,0.0f ,-5.0f }, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
	// 左腕のアニメーション
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[1]->GetTransform()->GetTween()->DORotation({ 0.0f ,0.0f ,5.0f }, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
	// 頭のアニメーション
	dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[0]->GetTransform()->GetTween()->DORotationY(20.0f, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
}


/// <summary>
/// ステートを作成する
/// </summary>
void Player::CreateState()
{
	// ステートの作成
	m_playerIdleState = std::make_unique<PlayerIdleState>();
	m_playerRunState = std::make_unique<PlayerRunState>(this);
	m_playerAttackState = std::make_unique<PlayerAttackState>(this);
	m_playerSitState = std::make_unique<PlayerSitState>(this);

	// ステートの初期化処理
	m_playerIdleState->Initialize();
	m_playerRunState->Initialize();
	m_playerAttackState->Initialize();
	m_playerSitState->Initialize();
}


/// <summary>
/// ステアリングビヘイビアを作成する
/// </summary>
void Player::CreateSteeringBehavior()
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

	m_steeringBehavior->Off(BEHAVIOR_TYPE::FLOATING);
}

/// <summary>
/// オブジェクトをアタッチする
/// </summary>
void Player::AttachObject()
{
	// 体を追加する
	this->Attach(PlayerFactory::CreatePlayerBody(this,
		{0.0f ,5.9f ,0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));

	// 風船を追加する
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ 0.0f ,10.0f ,0.2f }, { -20.0f ,0.0f ,0.0f }, DirectX::SimpleMath::Vector3::One));
	// 風船を追加する
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ 0.9f ,10.0f ,0.0f }, { -0.0f ,0.0f ,16.0f }, DirectX::SimpleMath::Vector3::One));
	// 風船を追加する
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ -0.9f ,10.0f ,0.0f }, { -0.0f ,0.0f ,-16.0f }, DirectX::SimpleMath::Vector3::One));


	for (int i = 0; i < 3; i++)
	{
		// 風船のボディを取得
		m_balloonObject.push_back(dynamic_cast<Balloon*>(m_childs[i + 1].get())->GetBody());
	}

	// オブジェクトのカウントをリセット
	Object::ResetNumber();
}