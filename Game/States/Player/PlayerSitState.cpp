// ============================================
// 
// ファイル名: PlayerSitState.cpp
// 概要: プレイヤー　座る状態
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/States/Player/PlayerSitState.h"
#include "Game/Player/Player.h"
#include "Game/Player/Body.h"
#include "Game/Player/LeftArm.h"
#include "Game/Player/RightArm.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤーオブジェクト</param>
PlayerSitState::PlayerSitState(Player* player)
{
	m_player = player;
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerSitState::Initialize()
{
}

/// <summary>
/// 事前処理
/// </summary>
void PlayerSitState::PreUpdate()
{
	
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void PlayerSitState::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
}

/// <summary>
/// 事後処理
/// </summary>
void PlayerSitState::PostUpdate()
{

}

/// <summary>
/// 終了処理
/// </summary>
void PlayerSitState::Finalize()
{

}