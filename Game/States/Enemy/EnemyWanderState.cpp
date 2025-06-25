#include "pch.h"
#include "Game/States/Enemy/EnemyWanderState.h"
#include "Game/Object/Object.h"

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
	switch (m_phase)
	{
		case WanderPhase::WAIT:
			m_timer += elapsedTime;
			if (m_timer >= m_waitTime)
			{
				// ROTATE へ移行
				m_targetAngle = RandomAngle();
				m_phase = WanderPhase::ROTATE;
			}
			break;

		case WanderPhase::ROTATE:
			// current → target に補間回転
			if (RotateTowards(elapsedTime))
			{
				// MOVE へ移行
				m_moved = 0.0f;
				m_phase = WanderPhase::MOVE;
			}
			break;

		case WanderPhase::MOVE:
			// 向いてる方向へ移動
			MoveForward(elapsedTime);
			if (m_moved >= m_moveDistance)
			{
				// WAIT へ戻す
				m_timer = 0.0f;
				m_waitTime = RandomTime();
				m_phase = WanderPhase::WAIT;
			}
			break;
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