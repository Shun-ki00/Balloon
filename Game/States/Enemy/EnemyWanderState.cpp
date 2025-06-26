#include "pch.h"
#include "Game/States/Enemy/EnemyWanderState.h"
#include "Game/Object/Object.h"
#include "Framework/Utilities/RandomUtilities.h"

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
			// ��]Tween���J�n
			m_object->GetTransform()->GetTween()->DORotationY(RandomUtilities::RandomFloat(0.0f, 360.0f), 1.5f);

			// �ړ������������_������
			m_moveDistance = RandomUtilities::RandomFloat(2.0f, 5.0f);
			// �ړ��X�s�[�h�����_������
			m_moveSpeed = RandomUtilities::RandomFloat(1.0f, 3.0f);
		}

		return;
	}

	// �ړ��J�n
	m_object->SetVelocity(m_object->GetVelocity() +
		DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f,m_moveSpeed * elapsedTime),
			m_object->GetTransform()->GetLocalRotation()));

	// �ړ����������Z
	m_moveDistance -= elapsedTime * m_moveSpeed;

	// �ړ������ɒB������҂����Ԃɖ߂�
	if (m_moveDistance <= 0.0f)
	{
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