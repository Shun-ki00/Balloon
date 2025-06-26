#include "pch.h"
#include "Game/States/Enemy/EnemyWanderState.h"
#include "Game/Object/Object.h"
#include "Framework/Utilities/RandomUtilities.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">敵オブジェクト</param>
EnemyWanderState::EnemyWanderState(Object* object)
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
			// 回転Tweenを開始
			m_object->GetTransform()->GetTween()->DORotationY(RandomUtilities::RandomFloat(0.0f, 360.0f), 1.5f);

			// 移動距離をランダム決定
			m_moveDistance = RandomUtilities::RandomFloat(2.0f, 5.0f);
			// 移動スピードランダム決定
			m_moveSpeed = RandomUtilities::RandomFloat(1.0f, 3.0f);
		}

		return;
	}

	// 移動開始
	m_object->SetVelocity(m_object->GetVelocity() +
		DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f,m_moveSpeed * elapsedTime),
			m_object->GetTransform()->GetLocalRotation()));

	// 移動距離を減算
	m_moveDistance -= elapsedTime * m_moveSpeed;

	// 移動距離に達したら待ち時間に戻る
	if (m_moveDistance <= 0.0f)
	{
		m_isWait = true;
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