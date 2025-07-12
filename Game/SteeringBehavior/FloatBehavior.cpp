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
/// <param name="floatRange">揺れ幅</param>
/// <param name="floatCycleSpeed">揺れるサイクル</param>
/// <param name="floatSpeed">速度</param>
/// <param name="direction">揺れる方向</param>
FloatBehavior::FloatBehavior(const float& floatRange, const float& floatCycleSpeed, const float& floatSpeed,
	const DirectX::SimpleMath::Vector3& direction)
	:
	m_isActive{},
	m_elapsedTime(0.0f),
	m_floatRange(floatRange),
	m_floatCycleSpeed(floatCycleSpeed),
	m_floatSpeed(floatSpeed),
	m_direction(direction)
{
}

/// <summary>
/// 計算処理を行う
/// </summary>
/// <returns>計算結果</returns>
DirectX::SimpleMath::Vector3 FloatBehavior::Calculate()
{
	// フラグが無効ならスキップ
	if (!m_isActive) return DirectX::SimpleMath::Vector3::Zero;

	// 経過時間を更新する
	float elapsedTime = (float)CommonResources::GetInstance()->GetStepTimer()->GetElapsedSeconds();
	m_elapsedTime += elapsedTime * m_floatSpeed;

	// サイン波計算
	float wave = std::sin(m_elapsedTime * m_floatCycleSpeed * 2.0f * DirectX::XM_PI);
	float offset = wave * m_floatRange;

	return m_direction * offset;
}

/// <summary>
/// 有効にする
/// </summary>
void FloatBehavior::On()
{
	// フラグをオンにする
	m_isActive = true;
}

/// <summary>
/// 無効にする
/// </summary>
void FloatBehavior::Off() 
{
	// フラグをオフにする
	m_isActive = false;
}

