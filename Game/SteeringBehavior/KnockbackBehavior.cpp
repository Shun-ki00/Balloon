#include "pch.h"
#include "Game/SteeringBehavior/KnockbackBehavior.h"
#include "Game/Object/Object.h"
#include "Game/Parameters/Parameters.h"




KnockbackBehavior::KnockbackBehavior(Object* object)
	:
	m_object(object),
	m_target{},
    m_count{}
{
    // �p�����[�^�̐ݒ�
    m_knockbackRadius = Parameters::GetInstance()->GetParameter(ParametersID::STEERING_BEHAVIOR,ParameterKeysF::KnockbackRadius);
    m_knockbackFoce   = Parameters::GetInstance()->GetParameter(ParametersID::STEERING_BEHAVIOR, ParameterKeysF::KnockbackFoce);
    m_knockbackCount  = Parameters::GetInstance()->GetParameter(ParametersID::STEERING_BEHAVIOR, ParameterKeysF::KnockbackCount);
    m_isKnockedBack   = false;
}

DirectX::SimpleMath::Vector3 KnockbackBehavior::Calculate() 
{
    // �f�o�b�O�̎��̂݃p�����[�^���X�V��������
#ifdef _DEBUG

     // �p�����[�^�̐ݒ�
    m_knockbackRadius = Parameters::GetInstance()->GetParameter(ParametersID::STEERING_BEHAVIOR, ParameterKeysF::KnockbackRadius);
    m_knockbackFoce = Parameters::GetInstance()->GetParameter(ParametersID::STEERING_BEHAVIOR, ParameterKeysF::KnockbackFoce);
    m_knockbackCount = Parameters::GetInstance()->GetParameter(ParametersID::STEERING_BEHAVIOR, ParameterKeysF::KnockbackCount);

#endif

    // �͈͊O�̂Ƃ��͌v�Z���s��Ȃ�
    if (!IsWithinKnockbackRange() || m_isKnockedBack)
    {
        m_isKnockedBack = false;
        return DirectX::SimpleMath::Vector3::Zero;
    }

    // �m�b�N�o�b�N�J�E���g�ǉ�
    m_count++;
    // �m�b�N�o�b�N�񐔏���𒴂����ꍇ
    if (m_count >= m_knockbackCount)
    {
        m_count = 0;
        m_isKnockedBack = true;
    }

    // �I�u�W�F�N�g�̐i�s�����i�܂��͌����j���擾
    DirectX::SimpleMath::Vector3 forward = m_object->GetVelocity();

    // �I�u�W�F�N�g�̑��x�����Z�b�g
    // m_object->SetVelocity(DirectX::SimpleMath::Vector3::Zero);

    forward = { forward.x , 0.0f , forward.z };

    // �������x���Ȃ��ꍇ��]����m�b�N�o�b�N������������肷��
    if (forward.Length() < 0.001f) 
    {
        forward = DirectX::SimpleMath::Vector3::Transform(
            DirectX::SimpleMath::Vector3::UnitX,
            m_object->GetTransform()->GetLocalRotation()
        );
    }

    // ���K��
    forward.Normalize();

    // �t�����փm�b�N�o�b�N������
    return -forward * m_knockbackFoce;
}


bool KnockbackBehavior::IsWithinKnockbackRange() 
{
    if (!m_target) return false;

    // �����̍��W
    auto myPosition = m_object->GetTransform()->GetLocalPosition();
    // �^�[�Q�b�g�̍��W
    auto targetPosition = m_target->GetTransform()->GetLocalPosition();

    // �������v�Z
    float distance = (myPosition - targetPosition).Length();

    // �͈͓����ǂ���
    return distance < m_knockbackRadius;
}

/// <summary>
/// �L���ɂ���
/// </summary>
void KnockbackBehavior::On()
{
    // �t���O���I���ɂ���
    m_isActive = true;
}

/// <summary>
/// �����ɂ���
/// </summary>
void KnockbackBehavior::Off()
{
    // �t���O���I�t�ɂ���
    m_isActive = false;
}