// ============================================
// 
// �t�@�C����: KnockbackBehavior.h
// �T�v: �m�b�N�o�b�N���s���r�w�C�r�A
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/SteeringBehavior/KnockbackBehavior.h"
#include "Game/Object/Object.h"
#include "Game/Parameters/Parameters.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object">�I�u�W�F�N�g</param>
/// <param name="knockbackRadius">�m�b�N�o�b�N�͈�</param>
/// <param name="knockbackCount">�m�b�N�o�b�N��</param>
/// <param name="knockbackFoce">�m�b�N�o�b�N���s����</param>
KnockbackBehavior::KnockbackBehavior(Object* object, const float& knockbackRadius, const int& knockbackCount, const float& knockbackFoce)
	:
	m_object(object),
    m_knockbackRadius(knockbackRadius),
    m_knockbackCount(knockbackCount),
    m_knockbackFoce(knockbackFoce),
	m_targets{},
    m_count{}
{
  
}

/// <summary>
/// �v�Z����
/// </summary>
/// <returns>�v�Z����</returns>
DirectX::SimpleMath::Vector3 KnockbackBehavior::Calculate() 
{
    // ��A�N�e�B�u�̎��͌v�Z���Ȃ�
    if (!m_isActive) return DirectX::SimpleMath::Vector3::Zero;

    // �͈͊O�̂Ƃ��͌v�Z���s��Ȃ�
    if (!IsWithinKnockbackRange() || m_isKnockedBack)
    {
        m_isKnockedBack = false;
        return DirectX::SimpleMath::Vector3::Zero;
    }

    m_count++;
    if (m_count >= m_knockbackCount)
    {
        m_count = 0;
        m_isKnockedBack = true;
    }

    // �ł��߂��^�[�Q�b�g�����փm�b�N�o�b�N
    const DirectX::SimpleMath::Vector3 myPosition =
        m_object->GetTransform()->GetLocalPosition();
    Object* nearest = nullptr;
    float minDist = std::numeric_limits<float>::max();

    for (auto* target : m_targets)
    {
        float dist = (myPosition - target->GetTransform()->GetLocalPosition()).LengthSquared();
        if (dist < minDist)
        {
            minDist = dist;
            nearest = target;
        }
    }

    DirectX::SimpleMath::Vector3 direction;

    if (nearest)
    {
        direction = myPosition - nearest->GetTransform()->GetLocalPosition();
    }
    else
    {
        direction = m_object->GetVelocity();
        if (direction.Length() < 0.001f)
        {
            direction = DirectX::SimpleMath::Vector3::Transform(
                DirectX::SimpleMath::Vector3::UnitX,
                m_object->GetTransform()->GetLocalRotation()
            );
        }
    }
    direction.y = 0.0f;
    direction.Normalize();
    return direction * m_knockbackFoce;

}

/// <summary>
/// �m�b�N�o�b�N�͈͓̔����ǂ���
/// </summary>
/// <returns>����</returns>
bool KnockbackBehavior::IsWithinKnockbackRange() 
{
  
    // �m�b�N�o�b�N����I�u�W�F�N�g�̍��W���擾
    const DirectX::SimpleMath::Vector3 myPosition =
        m_object->GetTransform()->GetLocalPosition();

    for (const auto& target : m_targets)
    {
        // �^�[�Q�b�g�̍��W���擾
        const DirectX::SimpleMath::Vector3 targetPosition =
            target->GetTransform()->GetLocalPosition();

        // �������v�Z
        const float distance = (myPosition - targetPosition).Length();

        if (distance < m_knockbackCount)
        {
            return true;
        }
    }

    return false;
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