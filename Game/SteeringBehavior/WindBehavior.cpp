// ============================================
// 
// �t�@�C����: WindBehavior.h
// �T�v: �O���̕��̗͂�^����r�w�C�r�A
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/SteeringBehavior/WindBehavior.h"
#include "Game/Parameters/Parameters.h"
#include "Game/Parameters/ParameterKeys.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
WindBehavior::WindBehavior()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void WindBehavior::Update(float deltaTime) 
{
    // ���̋����������Ȃ牽�����Ȃ�
    if (m_isWind)
    {
        // �c�蕗�p�����Ԃ����炷
        m_windTimer -= deltaTime;

        // ���Ԑ؂�ŕ����~����
        if (m_windTimer <= 0.0f)
        {
            // ���𖳌���
            m_isWind = false;
            // ���Ȃ��Ƀ��Z�b�g
            m_currentWind = DirectX::SimpleMath::Vector3::Zero; 
        }

        // ���������Ă�Ԃ͉������Ȃ�
        return; 
    }

    // �����~�܂��Ă��鎞�Ԃ����Z����
    m_timer += deltaTime;
    if (m_timer >= m_idleTime)
    {
        // ���𐶐�
        GenerateNewWind();
        m_timer = 0.0f;
    }

}


/// <summary>
/// �v�Z����
/// </summary>
/// <returns>�v�Z����</returns>
DirectX::SimpleMath::Vector3 WindBehavior::Calculate() 
{
    return m_currentWind;
}


/// <summary>
/// ���𐶐�����
/// </summary>
void WindBehavior::GenerateNewWind() 
{
    // �V�������̕����������_�������iXZ���ʁj
    DirectX::SimpleMath::Vector3 dir(m_dirDist(m_rng), 0.0f, m_dirDist(m_rng));

    // ����[���x�N�g���Ȃ�X�����ɐݒ�
    if (dir.Length() < 0.001f) dir = DirectX::SimpleMath::Vector3::UnitX;

    // �����x�N�g���𐳋K��
    dir.Normalize();

    // ���̋����������_������
    float strength = m_strengthDist(m_rng);

    // ���݂̕��x�N�g�����X�V
    m_currentWind = dir * strength;

    // ���̌p�����Ԃ������_������
    m_currentDuration = m_timeDist(m_rng);

    // �^�C�}�[�����Z�b�g
    m_windTimer = m_currentDuration;

    // �A�N�e�B�u��Ԃɂ���
    m_isWind = true;
}

/// <summary>
/// �L���ɂ���
/// </summary>
void WindBehavior::On()
{
    // �t���O���I���ɂ���
    m_isActive = true;
}

/// <summary>
/// �����ɂ���
/// </summary>
void WindBehavior::Off()
{
    // �t���O���I�t�ɂ���
    m_isActive = false;
}
