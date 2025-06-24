#include "pch.h"
#include "Game/States/Enemy/EnemyRunState.h"
#include "Game/Object/Object.h"


EnemyRunState::EnemyRunState(Object* object)
{
	m_object = object;
}


void EnemyRunState::Initialize()
{
	m_isBackward = false;
	m_isForward  = false;
}


void EnemyRunState::PreUpdate()
{

}


void EnemyRunState::Update(const float& elapsedTime)
{
	// 前方へ移動中かどうか
	if (m_isForward)
		m_object->SetVelocity(m_object->GetVelocity() +
			DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 5.0f * elapsedTime),
				m_object->GetTransform()->GetLocalRotation())
		);

	// 後方へ移動中かどうか
	if(m_isBackward)
		m_object->SetVelocity(m_object->GetVelocity() +
			DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, -5.0f * elapsedTime),
				m_object->GetTransform()->GetLocalRotation())
		);
}

void EnemyRunState::PostUpdate()
{
	// 速度をリセットする
	m_object->SetVelocity(DirectX::SimpleMath::Vector3::Zero);
	// リセット
	m_isBackward = false;
	m_isForward = false;
}


void EnemyRunState::Finalize()
{
	
}