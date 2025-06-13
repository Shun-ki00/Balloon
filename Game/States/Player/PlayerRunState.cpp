#include "pch.h"
#include "Game/States/Player/PlayerRunState.h"
#include "Game/Object/Object.h"


PlayerRunState::PlayerRunState(Object* object)
{
	m_object = object;
}


void PlayerRunState::Initialize()
{
	m_isBackward = false;
	m_isForward  = false;
}


void PlayerRunState::PreUpdate()
{

}


void PlayerRunState::Update(const float& elapsedTime)
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

void PlayerRunState::PostUpdate()
{
	// ���x�����Z�b�g����
	m_object->SetVelocity(DirectX::SimpleMath::Vector3::Zero);
	// ���Z�b�g
	m_isBackward = false;
	m_isForward = false;
}


void PlayerRunState::Finalize()
{
	
}