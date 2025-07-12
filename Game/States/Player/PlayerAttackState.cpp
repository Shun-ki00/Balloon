// ============================================
// 
// ファイル名: PlayerAttackState.cpp
// 概要: プレイヤー　攻撃状態
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/States/Player/PlayerAttackState.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Object/Object.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤーオブジェクト</param>
PlayerAttackState::PlayerAttackState(Object* player)
	:
	m_player(player)
{
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerAttackState::Initialize()
{

}

/// <summary>
/// 事前処理
/// </summary>
void PlayerAttackState::PreUpdate()
{
	m_elapsedTime = 0.0f;
	m_moveingTime = 0.3f;

	DirectX::SimpleMath::Vector3 velocity = { 0.0f , 0.0f ,6.0f };

	velocity = DirectX::SimpleMath::Vector3::Transform(velocity, m_player->GetTransform()->GetLocalRotation());

	velocity.y = -6.0f;

	m_player->SetVelocity(
		m_player->GetVelocity() + velocity * 2.0f
	);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void PlayerAttackState::Update(const float& elapsedTime)
{
	// 経過時間を更新
	m_elapsedTime += elapsedTime;

	if (m_elapsedTime >= m_moveingTime)
	{
		ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER,1000, Message::MessageID::PLAYER_IDLING);
	}
}

/// <summary>
/// 事後処理
/// </summary>
void PlayerAttackState::PostUpdate()
{

}

/// <summary>
/// 終了処理
/// </summary>
void PlayerAttackState::Finalize()
{

}