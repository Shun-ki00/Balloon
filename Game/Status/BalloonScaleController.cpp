#include "pch.h"
#include "Game/Status/BalloonScaleController.h"
#include "Game/SteeringBehavior/FloatForceBehavior.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Status/HpController.h"

/// <summary>
/// コンストラクタ
/// </summary>
BalloonScaleController::BalloonScaleController(HpController* hpController, FloatForceBehavior* floatForceBehavior)
{
	m_floatForceBehavior = floatForceBehavior;
	m_hpController = hpController;
}

/// <summary>
/// 初期化処理
/// </summary>
void BalloonScaleController::Initialize()
{
	m_isBalloonInflating = false;
	m_balloonScale = 0.0f;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BalloonScaleController::Update(const float& elapsedTime)
{
	// 有効の場合
	if (m_isBalloonInflating)
	{
		if (!m_hpController->HpReduction(0.001f))
		{
			this->Off();
		}

		// 風船を大きくする
		m_balloonScale += 2.0f * elapsedTime;

		if (m_balloonScale >= 1.0f)
			m_balloonScale = 1.0f;

		// 力を設定
		m_floatForceBehavior->SetForceStrength(m_balloonScale * 3.0f);
	}
	else
	{
		// 風船を小さくする
		m_balloonScale -= 2.0f * elapsedTime;

		if (m_balloonScale <= 0.0f)
			m_balloonScale = 0.0f;

		// 力を設定
		m_floatForceBehavior->SetForceStrength(m_balloonScale - 3.0f);
	}

}

/// <summary>
/// 有効化
/// </summary>
void BalloonScaleController::On()
{
	m_isBalloonInflating = true;
}

/// <summary>
/// 無効化
/// </summary>
void BalloonScaleController::Off()
{
	m_isBalloonInflating = false;
}