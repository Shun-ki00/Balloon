#include "pch.h"
#include "Game/States/Player/PlayerSitState.h"
#include "Game/Player/Player.h"
#include "Game/Player/Body.h"
#include "Game/Player/LeftArm.h"
#include "Game/Player/RightArm.h"


PlayerSitState::PlayerSitState(Player* player)
{
	m_player = player;
}


void PlayerSitState::Initialize()
{
	// �̃I�u�W�F�N�g
	auto body = dynamic_cast<Body*>(m_player->GetChilds()[0]);
	// ����
	auto leftArm = body->GetChilds()[2];
	// �E��
	auto rightArm = body->GetChilds()[4];


	//// ������90�x�Ȃ���
	//leftArm->GetTransform()->SetLocalRotation(
	//	DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(40.0f))
	//);
	//// �E����90�x�Ȃ���
	//rightArm->GetTransform()->SetLocalRotation(
	//	DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(40.0f))
	//);
	
}


void PlayerSitState::PreUpdate()
{
	
}


void PlayerSitState::Update(const float& elapsedTime)
{

}

void PlayerSitState::PostUpdate()
{

}


void PlayerSitState::Finalize()
{

}