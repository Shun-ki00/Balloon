// ============================================
// 
// ファイル名: PlayerRunState.cpp
// 概要: プレイヤー　走る状態
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/States/Player/PlayerRunState.h"
#include "Game/Object/Object.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">オブジェクト</param>
PlayerRunState::PlayerRunState(Object* object)
{
	m_object = object;
}


/// <summary>
/// 初期化処理
/// </summary>
void PlayerRunState::Initialize()
{
	m_isBackward = false;
	m_isForward  = false;
}

/// <summary>
/// 事前処理
/// </summary>
void PlayerRunState::PreUpdate()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void PlayerRunState::Update(const float& elapsedTime)
{
	// 前方へ移動中かどうか
	if (m_isForward)
		m_object->SetVelocity(m_object->GetVelocity() +
			DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 10.0f * elapsedTime),
				m_object->GetTransform()->GetLocalRotation())
		);

	// 後方へ移動中かどうか
	if(m_isBackward)
		m_object->SetVelocity(m_object->GetVelocity() +
			DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, -10.0f * elapsedTime),
				m_object->GetTransform()->GetLocalRotation())
		);
}

/// <summary>
/// 事後処理
/// </summary>
void PlayerRunState::PostUpdate()
{
	// 速度をリセットする
	m_object->SetVelocity(DirectX::SimpleMath::Vector3::Zero);
	// リセット
	m_isBackward = false;
	m_isForward  = false;
}


/// <summary>
/// 終了処理
/// </summary>
void PlayerRunState::Finalize()
{
	
}