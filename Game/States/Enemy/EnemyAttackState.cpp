// ============================================
// 
// �t�@�C����: EnemyAttackState.h
// �T�v: �G�@�U�����
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/States/Enemy/EnemyAttackState.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Object/Object.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="enemy">�G�I�u�W�F�N�g</param>
EnemyAttackState::EnemyAttackState(Object* enemy)
	:
	m_enemy(enemy)
{
}

/// <summary>
/// ����������
/// </summary>
void EnemyAttackState::Initialize()
{

}

/// <summary>
/// ���O����
/// </summary>
void EnemyAttackState::PreUpdate()
{
	m_elapsedTime = 0.0f;
	m_moveingTime = 0.5f;

	DirectX::SimpleMath::Vector3 velocity = { 0.0f , 0.0f ,6.0f };

	velocity = DirectX::SimpleMath::Vector3::Transform(velocity, m_enemy->GetTransform()->GetLocalRotation());

	velocity.y = -6.0f;

	m_enemy->SetVelocity(
		m_enemy->GetVelocity() + velocity * 2.0f
	);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void EnemyAttackState::Update(const float& elapsedTime)
{
	// �o�ߎ��Ԃ��X�V
	m_elapsedTime += elapsedTime;

	if (m_elapsedTime >= m_moveingTime)
	{
		m_enemy->OnMessegeAccepted({ Message::MessageID::ENEMY_IDLING });
	}
}

/// <summary>
/// ���㏈��
/// </summary>
void EnemyAttackState::PostUpdate()
{
}

/// <summary>
/// �I������
/// </summary>
void EnemyAttackState::Finalize()
{

}