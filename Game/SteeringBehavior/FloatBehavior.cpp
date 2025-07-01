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
	m_frequency = 1.0f;
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

	float prevTime = m_elapsedTime;
	m_elapsedTime += elapsedTime * 2.0f;

	float prevWave = std::sin(m_elapsedTime);
	float currWave = std::sin(m_elapsedTime * m_frequency * 2.0f * DirectX::XM_PI) * m_amplitude;

	float delta = currWave - prevWave;
	return m_direction * prevWave;
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

