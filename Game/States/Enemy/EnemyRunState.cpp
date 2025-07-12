// ============================================
// 
// �t�@�C����: EnemyRunState.h
// �T�v: �G�@������
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/States/Enemy/EnemyRunState.h"
#include "Game/Object/Object.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object">�Ώۂ̃I�u�W�F�N�g</param>
EnemyRunState::EnemyRunState(Object* object)
{
	m_object = object;
}

/// <summary>
/// ����������
/// </summary>
void EnemyRunState::Initialize()
{
	m_isBackward = false;
	m_isForward  = false;
}

/// <summary>
/// ���O����
/// </summary>
void EnemyRunState::PreUpdate()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void EnemyRunState::Update(const float& elapsedTime)
{
	// �O���ֈړ������ǂ���
	if (m_isForward)
		m_object->SetVelocity(m_object->GetVelocity() +
			DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 5.0f * elapsedTime),
				m_object->GetTransform()->GetLocalRotation())
		);

	// ����ֈړ������ǂ���
	if(m_isBackward)
		m_object->SetVelocity(m_object->GetVelocity() +
			DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, -5.0f * elapsedTime),
				m_object->GetTransform()->GetLocalRotation())
		);
}

/// <summary>
/// ���㏈��
/// </summary>
void EnemyRunState::PostUpdate()
{
	// ���x�����Z�b�g����
	m_object->SetVelocity(DirectX::SimpleMath::Vector3::Zero);
	// ���Z�b�g
	m_isBackward = false;
	m_isForward = false;
}

/// <summary>
/// �I������
/// </summary>
void EnemyRunState::Finalize()
{
	
}