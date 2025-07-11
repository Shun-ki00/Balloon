#include "pch.h"
#include "Game/States/Player/PlayerAttackState.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Object/Object.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[�I�u�W�F�N�g</param>
PlayerAttackState::PlayerAttackState(Object* player)
	:
	m_player(player)
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerAttackState::Initialize()
{

}

/// <summary>
/// ���O����
/// </summary>
void PlayerAttackState::PreUpdate()
{
	m_elapsedTime = 0.0f;
	m_moveingTime = 0.3f;

	DirectX::SimpleMath::Vector3 velocity = { 0.0f , 0.0f ,6.0f };

	velocity = DirectX::SimpleMath::Vector3::Transform(velocity, m_player->GetTransform()->GetLocalRotation());

	velocity.y = -6.0f;

	m_player->SetVelocity(
		m_player->GetVelocity() + velocity * 2.0f
	);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void PlayerAttackState::Update(const float& elapsedTime)
{
	// �o�ߎ��Ԃ��X�V
	m_elapsedTime += elapsedTime;

	if (m_elapsedTime >= m_moveingTime)
	{
		ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER,1000, Message::MessageID::PLAYER_IDLING);
	}
}

/// <summary>
/// ���㏈��
/// </summary>
void PlayerAttackState::PostUpdate()
{

}

/// <summary>
/// �I������
/// </summary>
void PlayerAttackState::Finalize()
{

}