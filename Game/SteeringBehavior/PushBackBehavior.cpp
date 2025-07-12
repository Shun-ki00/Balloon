// ============================================
// 
// �t�@�C����: PushBackBehavior.h
// �T�v: �X�e�[�W�Ȃ��ɖ߂��r�w�C�r�A
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/SteeringBehavior/PushBackBehavior.h"
#include "Interface/IObject.h"

const DirectX::SimpleMath::Vector3 PushBackBehavior::STAGE_MIN_BOUNDS = { -10.0f , -10.0f , -10.0f };
const DirectX::SimpleMath::Vector3 PushBackBehavior::STAGE_MAX_BOUNDS = {  10.0f ,  10.0f ,  10.0f };

const float PushBackBehavior::PUSH_BACK_STRENGTH = 10.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="object">�Ώۂ̃I�u�W�F�N�g</param>
PushBackBehavior::PushBackBehavior(IObject* object)
    :
    m_object(object)
{
}

/// <summary>
/// �v�Z����
/// </summary>
/// <returns>�v�Z����</returns>
DirectX::SimpleMath::Vector3 PushBackBehavior::Calculate()  
{

    if (!m_object)
    {
        return DirectX::SimpleMath::Vector3::Zero;
    }

    DirectX::SimpleMath::Vector3 force = DirectX::SimpleMath::Vector3::Zero;

    DirectX::SimpleMath::Vector3 position = m_object->GetTransform()->GetLocalPosition();

    if (position.x < STAGE_MIN_BOUNDS.x)
    {
        force.x = PUSH_BACK_STRENGTH;
    }
    else if (position.x > STAGE_MAX_BOUNDS.x)
    {
        force.x = -PUSH_BACK_STRENGTH;
    }

    if (position.y < STAGE_MIN_BOUNDS.y)
    {
        force.y = PUSH_BACK_STRENGTH;
    }
    else if (position.y > STAGE_MAX_BOUNDS.y)
    {
        force.y = -PUSH_BACK_STRENGTH;
    }

    if (position.z < STAGE_MIN_BOUNDS.z)
    {
        force.z = PUSH_BACK_STRENGTH;
    }
    else if (position.z > STAGE_MAX_BOUNDS.z)
    {
        force.z = -PUSH_BACK_STRENGTH;
    }

    return force;
}

/// <summary>
/// �L���ɂ���
/// </summary>
void PushBackBehavior::On()
{
    // �t���O���I���ɂ���
    m_isActive = true;
}

/// <summary>
/// �����ɂ���
/// </summary>
void PushBackBehavior::Off()
{
    // �t���O���I�t�ɂ���
    m_isActive = false;
}