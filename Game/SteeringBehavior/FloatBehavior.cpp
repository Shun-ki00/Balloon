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
/// <param name="floatRange">�h�ꕝ</param>
/// <param name="floatCycleSpeed">�h���T�C�N��</param>
/// <param name="floatSpeed">���x</param>
/// <param name="direction">�h������</param>
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
/// �v�Z�������s��
/// </summary>
/// <returns>�v�Z����</returns>
DirectX::SimpleMath::Vector3 FloatBehavior::Calculate()
{
	// �t���O�������Ȃ�X�L�b�v
	if (!m_isActive) return DirectX::SimpleMath::Vector3::Zero;

	// �o�ߎ��Ԃ��X�V����
	float elapsedTime = (float)CommonResources::GetInstance()->GetStepTimer()->GetElapsedSeconds();
	m_elapsedTime += elapsedTime * m_floatSpeed;

	// �T�C���g�v�Z
	float wave = std::sin(m_elapsedTime * m_floatCycleSpeed * 2.0f * DirectX::XM_PI);
	float offset = wave * m_floatRange;

	return m_direction * offset;
}

/// <summary>
/// �L���ɂ���
/// </summary>
void FloatBehavior::On()
{
	// �t���O���I���ɂ���
	m_isActive = true;
}

/// <summary>
/// �����ɂ���
/// </summary>
void FloatBehavior::Off() 
{
	// �t���O���I�t�ɂ���
	m_isActive = false;
}

