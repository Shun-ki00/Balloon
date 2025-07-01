// ============================================
// 
// �t�@�C����: FloatBehavior.cpp
// �T�v: ���V�i�t���[�g�j����
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include  "Game/SteeringBehavior/FloatBehavior.h"
#include "Framework/CommonResources.h"

/// <summary>
/// �R���X�g���N�^
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
/// �v�Z�������s��
/// </summary>
/// <returns>�v�Z����</returns>
DirectX::SimpleMath::Vector3 FloatBehavior::Calculate()
{
	// �o�ߎ��Ԃ��X�V����
	float elapsedTime = (float)CommonResources::GetInstance()->GetStepTimer()->GetElapsedSeconds();

	float prevTime = m_elapsedTime;
	m_elapsedTime += elapsedTime * 2.0f;

	float prevWave = std::sin(m_elapsedTime);
	float currWave = std::sin(m_elapsedTime * m_frequency * 2.0f * DirectX::XM_PI) * m_amplitude;

	float delta = currWave - prevWave;
	return m_direction * prevWave;
}

/// <summary>
/// �L���ɂ���
/// </summary>
void FloatBehavior::On()
{
	// �t���O���I���ɂ���
	m_isFloat = true;
}

/// <summary>
/// �����ɂ���
/// </summary>
void FloatBehavior::Off() 
{
	// �t���O���I�t�ɂ���
	m_isFloat = false;
}

