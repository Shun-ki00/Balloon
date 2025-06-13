#include "pch.h"
#include "Game/SteeringBehavior/SeekBehavior.h"
#include "Game/Object/Object.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object">���g�I�u�W�F�N�g</param>
/// <param name="target">�^�[�Q�b�g�̃I�u�W�F�N�g</param>
SeekBehavior::SeekBehavior(Object* object, Object* target)
{
    m_object = object;
    m_target = target;
}

/// <summary>
/// �v�Z�������s��
/// </summary>
/// <returns>�v�Z����</returns>
DirectX::SimpleMath::Vector3 SeekBehavior::Calculate()
{
    // ����̍��W
    const DirectX::SimpleMath::Vector3 targetPosition = m_target->GetTransform()->GetLocalPosition();
    // ����̑��x
    const DirectX::SimpleMath::Vector3 targetVelocity = m_target->GetVelocity();

    // �����Ƒ���̋����x�N�g�����v�Z
    const DirectX::SimpleMath::Vector3 toTarget =
        targetPosition - m_object->GetTransform()->GetLocalPosition();

    // �����̑��x���擾
    float speed = m_object->GetVelocity().Length() + 0.01f;

    // �^�[�Q�b�g�܂ł̋������擾
    float distance = toTarget.Length();

    // �^�[�Q�b�g�̖����ʒu��\�����邽�߂̌v�Z
    float lookAheadTime = (distance / speed) * m_predictionMultiplier;

    // �\���ʒu���v�Z
    DirectX::SimpleMath::Vector3 predictedPosition =
        targetPosition + targetVelocity * lookAheadTime;

    // �\���ʒu�֌������x�N�g�����v�Z
    DirectX::SimpleMath::Vector3 desiredVelocity =
        predictedPosition - m_object->GetTransform()->GetLocalPosition();

    // Y�����𖳎�����
    desiredVelocity.y = 0.0f;

    // ���K�����Č����������擾
    desiredVelocity.Normalize();

    // �ړ����x����Z
    desiredVelocity *= m_seekSpeed;

    return desiredVelocity;
}

/// <summary>
/// �L���ɂ���
/// </summary>
void SeekBehavior::On()
{
    // �t���O���I���ɂ���
    m_isActive = true;
}

/// <summary>
/// �����ɂ���
/// </summary>
void SeekBehavior::Off()
{
    // �t���O���I�t�ɂ���
    m_isActive = false;
}