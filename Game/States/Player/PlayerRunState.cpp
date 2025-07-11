#include "pch.h"
#include "Game/States/Player/PlayerRunState.h"
#include "Game/Object/Object.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object">�I�u�W�F�N�g</param>
PlayerRunState::PlayerRunState(Object* object)
{
	m_object = object;
}


/// <summary>
/// ����������
/// </summary>
void PlayerRunState::Initialize()
{
	m_isBackward = false;
	m_isForward  = false;
}

/// <summary>
/// ���O����
/// </summary>
void PlayerRunState::PreUpdate()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void PlayerRunState::Update(const float& elapsedTime)
{
	// �O���ֈړ������ǂ���
	if (m_isForward)
		m_object->SetVelocity(m_object->GetVelocity() +
			DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 10.0f * elapsedTime),
				m_object->GetTransform()->GetLocalRotation())
		);

	// ����ֈړ������ǂ���
	if(m_isBackward)
		m_object->SetVelocity(m_object->GetVelocity() +
			DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, -10.0f * elapsedTime),
				m_object->GetTransform()->GetLocalRotation())
		);
}

/// <summary>
/// ���㏈��
/// </summary>
void PlayerRunState::PostUpdate()
{
	// ���x�����Z�b�g����
	m_object->SetVelocity(DirectX::SimpleMath::Vector3::Zero);
	// ���Z�b�g
	m_isBackward = false;
	m_isForward  = false;
}


/// <summary>
/// �I������
/// </summary>
void PlayerRunState::Finalize()
{
	
}