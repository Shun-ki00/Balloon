#include "pch.h"
#include "Game/Status/BalloonScaleController.h"
#include "Game/SteeringBehavior/FloatForceBehavior.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Status/HpController.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
BalloonScaleController::BalloonScaleController(HpController* hpController, FloatForceBehavior* floatForceBehavior)
{
	m_floatForceBehavior = floatForceBehavior;
	m_hpController = hpController;
}

/// <summary>
/// ����������
/// </summary>
void BalloonScaleController::Initialize()
{
	m_isBalloonInflating = false;
	m_balloonScale = 0.0f; 
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BalloonScaleController::Update(const float& elapsedTime)
{
	// �L���̏ꍇ
	if (m_isBalloonInflating)
	{
		if (!m_hpController->HpReduction(0.001f))
		{
			this->Off();
		}

		// ���D��傫������
		m_balloonScale += 2.0f * elapsedTime;

		if (m_balloonScale >= 1.0f)
			m_balloonScale = 1.0f;

		// �͂�ݒ�
		m_floatForceBehavior->SetForceStrength(m_balloonScale * 3.0f);
	}
	else
	{
		// ���D������������
		m_balloonScale -= 2.0f * elapsedTime;

		if (m_balloonScale <= 0.0f)
			m_balloonScale = 0.0f;

		// �͂�ݒ�
		m_floatForceBehavior->SetForceStrength(m_balloonScale - 3.0f);
	}

}

/// <summary>
/// �L����
/// </summary>
void BalloonScaleController::On()
{
	m_isBalloonInflating = true;
}

/// <summary>
/// ������
/// </summary>
void BalloonScaleController::Off()
{
	m_isBalloonInflating = false;
}