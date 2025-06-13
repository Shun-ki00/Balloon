// ============================================
// 
// ファイル名: FloatBehavior.cpp
// 概要: 浮遊（フロート）挙動
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include  "Game/SteeringBehavior/FloatBehavior.h"
#include "Framework/CommonResources.h"

/// <summary>
/// コンストラクタ
/// </summary>
FloatBehavior::FloatBehavior()
	:
	m_isFloat{},
	m_amplitude{},
	m_floatSpeed{},
	m_direction{},
	m_elapsedTime{}
{
	m_isFloat = true;
	m_elapsedTime = 0.0f;

	m_amplitude = 2.0f;
	m_floatSpeed = 1.0f;
	m_direction = DirectX::SimpleMath::Vector3::Up;
}

/// <summary>
/// 計算処理を行う
/// </summary>
/// <returns>計算結果</returns>
DirectX::SimpleMath::Vector3 FloatBehavior::Calculate()
{
	// 経過時間を更新する
	float elapsedTime = (float)CommonResources::GetInstance()->GetStepTimer()->GetElapsedSeconds();
	m_elapsedTime += elapsedTime;

	// 無効の時は計算しない
	if (!m_isFloat) return DirectX::SimpleMath::Vector3::Zero;

	// 計算する
	float wave = std::sin(m_elapsedTime * 1.0f * 2.0f * DirectX::XM_PI) * m_amplitude;

	// 計算結果を返す
	return m_direction * wave;
}

/// <summary>
/// 有効にする
/// </summary>
void FloatBehavior::On()
{
	// フラグをオンにする
	m_isFloat = true;
}

/// <summary>
/// 無効にする
/// </summary>
void FloatBehavior::Off() 
{
	// フラグをオフにする
	m_isFloat = false;
}

