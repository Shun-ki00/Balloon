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

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object">�G�I�u�W�F�N�g</param>
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
/// ����������
/// </summary>
void EnemyWanderState::Initialize()
{
	m_isWait = true;
	m_timer = 0.0f;
	m_waitTime = 1.0f;
}

/// <summary>
/// �O����
/// </summary>
void EnemyWanderState::PreUpdate()
{
	
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void EnemyWanderState::Update(const float& elapsedTime)
{
	// �҂����ԏ���
	if (m_isWait)
	{
		// �҂�����
		m_timer += elapsedTime;
		// �҂����Ԃ��I��������
		if (m_timer >= m_waitTime)
		{
			// �҂����ԏI��
			m_isWait = false;

			// �c��܂��邩�����_������
			m_isFlate = static_cast<bool>(RandomUtilities::RandomInt(0, 1));
			// true�̏ꍇ�c��܂���
			if (m_isFlate)
				m_object->OnMessegeAccepted({ Message::MessageID::ENEMY_ON_BALLOON_SCALE });

			// ��]Tween���J�n
			m_object->GetTransform()->GetTween()->DORotationY(
				RandomUtilities::RandomFloat(MIN_ROTATION_ANGLE, MAX_ROTATION_ANGLE), ROTATION_DURATION);

			// �ړ������������_������
			m_moveDistance = RandomUtilities::RandomFloat(MIN_MOVE_DISTANCE, MAX_MOVE_DISTANCE);
			// �ړ��X�s�[�h�����_������
			m_moveSpeed = RandomUtilities::RandomFloat(MIN_MOVE_SPEED, MAX_MOVE_SPEED);
		}

		return;
	}

	// �ړ��J�n
	m_object->SetVelocity(m_object->GetVelocity() +
		DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Backward * m_moveSpeed * elapsedTime,
			m_object->GetTransform()->GetLocalRotation()));

	// �ړ����������Z
	m_moveDistance -= elapsedTime * m_moveSpeed;

	// �ړ������ɒB������҂����Ԃɖ߂�
	if (m_moveDistance <= 0.0f)
	{
		// �c��܂��鏈�����I��
		m_object->OnMessegeAccepted({ Message::MessageID::ENEMY_OFF_BALLOON_SCALE });

		m_isWait = true;
	}

}

/// <summary>
/// �㏈��
/// </summary>
void EnemyWanderState::PostUpdate()
{
	
}

/// <summary>
/// �I������
/// </summary>
void EnemyWanderState::Finalize()
{

}