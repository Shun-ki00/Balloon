#include "pch.h"
#include "Game/Status/HpController.h"
#include "Game/SteeringBehavior/FloatForceBehavior.h"
#include "Game/Message/ObjectMessenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
HpController::HpController()
{

}

/// <summary>
/// ����������
/// </summary>
void HpController::Initialize()
{
    // ����HP
    m_hp = 1.0f;
    // �ő�HP
    m_maxHp = 1.0f;

    m_targetHp = m_hp;
    m_reduceSpeed = 0.5f;

    m_isReducing = false;
    m_isRecovering = false;
    m_recoverDelayTimer = 0.0f;
    m_recoverDelay = 3.0f;
    m_recoverSpeed = 0.25f;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void HpController::Update(const float& elapsedTime)
{
    // HP��������
    if (m_isReducing)
    {
        float delta = m_reduceSpeed * elapsedTime;

        if (m_hp - delta <= m_targetHp)
        {
            m_hp = m_targetHp;
            m_isReducing = false;

            // ����������A�x���^�C�}�[���J�n
            m_recoverDelayTimer = 0.0f;
        }
        else
        {
            m_hp -= delta;
        }

      
        return; // �������͉񕜏������s��Ȃ�
    }

    // HP�񕜊J�n�̃f�B���C�^�C�}�[�i�s
    if (!m_isRecovering && m_hp < m_maxHp)
    {
        m_recoverDelayTimer += elapsedTime;
        if (m_recoverDelayTimer >= m_recoverDelay)
        {
            m_isRecovering = true;
        }
    }

    // �񕜏���
    if (m_isRecovering)
    {
        float delta = m_recoverSpeed * elapsedTime;

        if (m_hp + delta >= m_maxHp)
        {
            m_hp = m_maxHp;
            m_isRecovering = false;
        }
        else
        {
            m_hp += delta;
        }

        m_targetHp = m_hp;
    }
}


/// <summary>
/// HP�����炷
/// </summary>
/// <param name="hp">���炷��</param>
/// <returns>���点�ꂽ���ǂ���</returns>
bool HpController::HpReduction(const float& amount)
{
    float requestedHp = m_targetHp - amount;

    if (requestedHp < 0.0f)
        return false;

    // �񕜒��Ȃ�L�����Z��
    if (m_isRecovering)
    {
        m_isRecovering = false;
    }

    // �x���^�C�}�[���������i�ēx���Z�b�g�j
    m_recoverDelayTimer = 0.0f;

    // �����^�[�Q�b�g�X�V
    m_targetHp = requestedHp;
    m_isReducing = true;

    return true;

}