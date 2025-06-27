#include "pch.h"
#include "Game/States/Enemy/EnemyChaseState.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Object/Object.h"
#include "Game/SteeringBehavior/SeekBehavior.h"
#include "Game/SteeringBehavior/SteeringBehavior.h"
#include "Game/Enemy/Enemy.h"
#include "Interface/IObject.h"

EnemyChaseState::EnemyChaseState(Object* enemy, Object* player, SteeringBehavior* steeringBehavior, SeekBehavior* seekBehavior)
{
	m_enemy        = enemy;
	m_player       = player;
    m_seekBehavior = seekBehavior;
    m_steeringBehavior = steeringBehavior;
}


void EnemyChaseState::Initialize()
{

}


void EnemyChaseState::PreUpdate()
{
    // �r�w�C�r�A���I���ɂ���
    m_steeringBehavior->On(BEHAVIOR_TYPE::SEEK);

    // �v���C���[�̈ʒu���擾
    DirectX::SimpleMath::Vector3 playerPos = m_player->GetTransform()->GetLocalPosition();
    // �G�̈ʒu���擾
    DirectX::SimpleMath::Vector3 enemyPos  = m_enemy->GetTransform()->GetLocalPosition();

    // �����x�N�g���i�������������j
    DirectX::SimpleMath::Vector3 direction = playerPos - enemyPos;

    // �x�N�g�����[���łȂ����`�F�b�N
    if (direction.LengthSquared() > 0.0001f)
    {
        // ��]�p�iYaw�j�ɕϊ�
        float yaw = std::atan2(direction.x, direction.z);
        float deg = DirectX::XMConvertToDegrees(yaw);

        // Y����]Tween�i��: 0.3�b�����ĉ�]�j
        m_enemy->GetTransform()->GetTween()->DORotationY(-deg, 0.0f);
    }
}


void EnemyChaseState::Update(const float& elapsedTime)
{
    // SeekBehavior�ɂ���ĎZ�o���ꂽ�x�N�g���̌������擾����
    DirectX::SimpleMath::Vector3 velocity = m_seekBehavior->GetDirection();

    // �x�N�g�����L���Ȃ�������X�V
    if (velocity.LengthSquared() > 0.0001f)
    {
        float yaw = std::atan2(velocity.x, velocity.z);
    
        m_enemy->GetTransform()->SetLocalRotation(
            DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, yaw)
        );
    }
}

void EnemyChaseState::PostUpdate()
{
    m_steeringBehavior->Off(BEHAVIOR_TYPE::SEEK);
}


void EnemyChaseState::Finalize()
{

}