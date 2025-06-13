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
	m_elapsedTime += elapsedTime;

	// �����̎��͌v�Z���Ȃ�
	if (!m_isFloat) return DirectX::SimpleMath::Vector3::Zero;

	// �v�Z����
	float wave = std::sin(m_elapsedTime * 1.0f * 2.0f * DirectX::XM_PI) * m_amplitude;

	// �v�Z���ʂ�Ԃ�
	return m_direction * wave;
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

