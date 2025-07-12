// ============================================
// 
// ファイル名: EnemyRunState.h
// 概要: 敵　走る状態
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/States/Enemy/EnemyRunState.h"
#include "Game/Object/Object.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">対象のオブジェクト</param>
EnemyRunState::EnemyRunState(Object* object)
{
	m_object = object;
}

/// <summary>
/// 初期化処理
/// </summary>
void EnemyRunState::Initialize()
{
	m_isBackward = false;
	m_isForward  = false;
}

/// <summary>
/// 事前処理
/// </summary>
void EnemyRunState::PreUpdate()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
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

/// <summary>
/// 事後処理
/// </summary>
void EnemyRunState::PostUpdate()
{
	// 速度をリセットする
	m_object->SetVelocity(DirectX::SimpleMath::Vector3::Zero);
	// リセット
	m_isBackward = false;
	m_isForward = false;
}

/// <summary>
/// 終了処理
/// </summary>
void EnemyRunState::Finalize()
{
	
}