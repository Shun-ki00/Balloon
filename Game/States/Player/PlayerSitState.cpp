// ============================================
// 
// �t�@�C����: PlayerSitState.cpp
// �T�v: �v���C���[�@������
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/States/Player/PlayerSitState.h"
#include "Game/Player/Player.h"
#include "Game/Player/Body.h"
#include "Game/Player/LeftArm.h"
#include "Game/Player/RightArm.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[�I�u�W�F�N�g</param>
PlayerSitState::PlayerSitState(Player* player)
{
	m_player = player;
}

/// <summary>
/// ����������
/// </summary>
void PlayerSitState::Initialize()
{
}

/// <summary>
/// ���O����
/// </summary>
void PlayerSitState::PreUpdate()
{
	
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void PlayerSitState::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
}

/// <summary>
/// ���㏈��
/// </summary>
void PlayerSitState::PostUpdate()
{

}

/// <summary>
/// �I������
/// </summary>
void PlayerSitState::Finalize()
{

}