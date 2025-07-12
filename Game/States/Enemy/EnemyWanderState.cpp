// ============================================
// 
// ファイル名: EnemyWanderState.h
// 概要: 敵　徘徊状態
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/States/Enemy/EnemyWanderState.h"
#include "Game/Object/Object.h"
#include "Framework/Utilities/RandomUtilities.h"

const float EnemyWanderState::MIN_ROTATION_ANGLE = 0.0f;
const float EnemyWanderState::MAX_ROTATION_ANGLE = 360.0f;

const float EnemyWanderState::ROTATION_DURATION = 1.5f;

const float EnemyWanderState::MIN_MOVE_DISTANCE = 2.0f;
const float EnemyWanderState::MAX_MOVE_DISTANCE = 5.0f;

const float EnemyWanderState::MIN_MOVE_SPEED = 1.0f;
const float EnemyWanderState::MAX_MOVE_SPEED = 3.0f;

const float EnemyWanderState::MIN_WAIT_TIME = 2.0f;
const float EnemyWanderState::MAX_WAIT_TIME = 4.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">敵オブジェクト</param>
EnemyWanderState::EnemyWanderState(Object* object)
	:
	m_object{},
	m_isWait{},
	m_isFlate{},
	m_timer{},
	m_waitTime{},
	m_targetAngle{},
	m_rotationSpeed{},
	m_moveSpeed{},
	m_moveDistance{},
	m_moved{}
{
	m_object = object;
}

/// <summary>
/// 初期化処理
/// </summary>
void EnemyWanderState::Initialize()
{
	m_isWait = true;
	m_timer = 0.0f;
	m_waitTime = 1.0f;
}

/// <summary>
/// 前処理
/// </summary>
void EnemyWanderState::PreUpdate()
{
	
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void EnemyWanderState::Update(const float& elapsedTime)
{
	// 待ち時間処理
	if (m_isWait)
	{
		// 待ち時間
		m_timer += elapsedTime;
		// 待ち時間が終了したら
		if (m_timer >= m_waitTime)
		{
			// 待ち時間終了
			m_isWait = false;

			// 膨らませるかランダム決定
			m_isFlate = static_cast<bool>(RandomUtilities::RandomInt(0, 1));
			// trueの場合膨らませる
			if (m_isFlate)
				m_object->OnMessegeAccepted({ Message::MessageID::ENEMY_ON_BALLOON_SCALE });

			// 回転Tweenを開始
			m_object->GetTransform()->GetTween()->DORotationY(
				RandomUtilities::RandomFloat(MIN_ROTATION_ANGLE, MAX_ROTATION_ANGLE), ROTATION_DURATION);

			// 移動距離をランダム決定
			m_moveDistance = RandomUtilities::RandomFloat(MIN_MOVE_DISTANCE, MAX_MOVE_DISTANCE);
			// 移動スピードランダム決定
			m_moveSpeed = RandomUtilities::RandomFloat(MIN_MOVE_SPEED, MAX_MOVE_SPEED);
		}

		return;
	}

	// 移動開始
	m_object->SetVelocity(m_object->GetVelocity() +
		DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Backward * m_moveSpeed * elapsedTime,
			m_object->GetTransform()->GetLocalRotation()));

	// 移動距離を減算
	m_moveDistance -= elapsedTime * m_moveSpeed;

	// 移動距離に達したら待ち時間に戻る
	if (m_moveDistance <= 0.0f)
	{
		// 膨らませる処理を終了
		m_object->OnMessegeAccepted({ Message::MessageID::ENEMY_OFF_BALLOON_SCALE });

		// 待機時間をオンにする
		m_isWait = true;

		// タイマーのリセット
		m_timer = 0.0f;
		// 待機時間をランダム決定
		m_waitTime = RandomUtilities::RandomFloat(MIN_WAIT_TIME , MAX_WAIT_TIME);
	}
}

/// <summary>
/// 後処理
/// </summary>
void EnemyWanderState::PostUpdate()
{
	
}

/// <summary>
/// 終了処理
/// </summary>
void EnemyWanderState::Finalize()
{

}