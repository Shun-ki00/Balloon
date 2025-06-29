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
}


void PlayerSitState::PreUpdate()
{
	
}


void PlayerSitState::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
}

void PlayerSitState::PostUpdate()
{

}


void PlayerSitState::Finalize()
{

}