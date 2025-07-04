#include "pch.h"
#include "Game/States/Enemy/EnemyAttackState.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Object/Object.h"


EnemyAttackState::EnemyAttackState(Object* player)
	:
	m_player(player)
{
}

void EnemyAttackState::Initialize()
{

}

void EnemyAttackState::PreUpdate()
{
	m_elapsedTime = 0.0f;
	m_moveingTime = 0.5f;

	DirectX::SimpleMath::Vector3 velocity = { 0.0f , 0.0f ,6.0f };

	velocity = DirectX::SimpleMath::Vector3::Transform(velocity, m_player->GetTransform()->GetLocalRotation());

	velocity.y = -6.0f;

	m_player->SetVelocity(
		m_player->GetVelocity() + velocity * 2.0f
	);
}


void EnemyAttackState::Update(const float& elapsedTime)
{
	// 経過時間を更新
	m_elapsedTime += elapsedTime;

	if (m_elapsedTime >= m_moveingTime)
	{
		m_player->OnMessegeAccepted({ Message::MessageID::ENEMY_IDLING });
	}
}

void EnemyAttackState::PostUpdate()
{
}


void EnemyAttackState::Finalize()
{

}