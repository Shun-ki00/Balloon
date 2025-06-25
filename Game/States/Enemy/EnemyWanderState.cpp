#include "pch.h"
#include "Game/States/Enemy/EnemyWanderState.h"
#include "Game/Object/Object.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object">�G�I�u�W�F�N�g</param>
EnemyWanderState::EnemyWanderState(Object* object)
{
	m_object = object;
}

/// <summary>
/// ����������
/// </summary>
void EnemyWanderState::Initialize()
{
	
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
	switch (m_phase)
	{
		case WanderPhase::WAIT:
			m_timer += elapsedTime;
			if (m_timer >= m_waitTime)
			{
				// ROTATE �ֈڍs
				m_targetAngle = RandomAngle();
				m_phase = WanderPhase::ROTATE;
			}
			break;

		case WanderPhase::ROTATE:
			// current �� target �ɕ�ԉ�]
			if (RotateTowards(elapsedTime))
			{
				// MOVE �ֈڍs
				m_moved = 0.0f;
				m_phase = WanderPhase::MOVE;
			}
			break;

		case WanderPhase::MOVE:
			// �����Ă�����ֈړ�
			MoveForward(elapsedTime);
			if (m_moved >= m_moveDistance)
			{
				// WAIT �֖߂�
				m_timer = 0.0f;
				m_waitTime = RandomTime();
				m_phase = WanderPhase::WAIT;
			}
			break;
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