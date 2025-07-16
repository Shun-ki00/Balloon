// ============================================
// 
// ファイル名: EnemyAttackState.h
// 概要: 敵　攻撃状態
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/States/Enemy/EnemyAttackState.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Object/Object.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="enemy">敵オブジェクト</param>
EnemyAttackState::EnemyAttackState(Object* enemy)
	:
	m_enemy(enemy)
{
}

/// <summary>
/// 初期化処理
/// </summary>
void EnemyAttackState::Initialize()
{

}

/// <summary>
/// 事前処理
/// </summary>
void EnemyAttackState::PreUpdate()
{
	m_elapsedTime = 0.0f;
	m_moveingTime = 1.5f;

	DirectX::SimpleMath::Vector3 velocity = { 0.0f , 0.0f ,-1.0f };

	auto player = ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER)[0];

	velocity = DirectX::SimpleMath::Vector3::Transform(velocity, player->GetTransform()->GetLocalRotation());

	velocity.y = -3.0f;

	m_enemy->SetVelocity(
		m_enemy->GetVelocity() + velocity * 2.0f
	);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void EnemyAttackState::Update(const float& elapsedTime)
{
	// 経過時間を更新
	m_elapsedTime += elapsedTime;

	if (m_elapsedTime >= m_moveingTime)
	{
		m_enemy->OnMessegeAccepted({ Message::MessageID::ENEMY_IDLING });
	}
}

/// <summary>
/// 事後処理
/// </summary>
void EnemyAttackState::PostUpdate()
{
}

/// <summary>
/// 終了処理
/// </summary>
void EnemyAttackState::Finalize()
{

}