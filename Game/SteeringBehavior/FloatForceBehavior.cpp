#include "pch.h"
#include "Game/SteeringBehavior/FloatForceBehavior.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
FloatForceBehavior::FloatForceBehavior()
{
}


/// <summary>
/// �v�Z�������s��
/// </summary>
/// <returns>�v�Z����</returns>
DirectX::SimpleMath::Vector3 FloatForceBehavior::Calculate()
{
    DirectX::SimpleMath::Vector3 force = DirectX::SimpleMath::Vector3::Zero;

    // �w�肵�������ɗ͂�������
    force = m_direction * m_forcePower;

    // �͂�Ԃ�
    return force;
}

/// <summary>
/// �L���ɂ���
/// </summary>
void FloatForceBehavior::On()
{
    // �t���O���I���ɂ���
    m_isActive = true;
}

/// <summary>
/// �����ɂ���
/// </summary>
void FloatForceBehavior::Off()
{
    // �t���O���I�t�ɂ���
    m_isActive = false;
}