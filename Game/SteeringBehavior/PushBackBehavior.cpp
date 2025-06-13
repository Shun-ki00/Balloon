#include "pch.h"
#include "Game/SteeringBehavior/PushBackBehavior.h"
#include "Interface/IObject.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">対象のオブジェクト</param>
PushBackBehavior::PushBackBehavior(IObject* object)
    :
    m_object(object)
{
    m_pushBackStrength = 10.0f;
    m_stageMinBounds = { -5.0f , -5.0f , -5.0f };
    m_stageMaxBounds = { 5.0f , 5.0f , 5.0f };
}

/// <summary>
/// 計算処理
/// </summary>
/// <returns>計算結果</returns>
DirectX::SimpleMath::Vector3 PushBackBehavior::Calculate()  
{

    if (!m_object)
    {
        return DirectX::SimpleMath::Vector3::Zero;
    }

    DirectX::SimpleMath::Vector3 force = DirectX::SimpleMath::Vector3::Zero;

    DirectX::SimpleMath::Vector3 position = m_object->GetTransform()->GetLocalPosition();

    if (position.x < m_stageMinBounds.x) 
    {
        force.x = m_pushBackStrength;
    }
    else if (position.x > m_stageMaxBounds.x) 
    {
        force.x = -m_pushBackStrength;
    }

    if (position.y < m_stageMinBounds.y)
    {
        force.y = m_pushBackStrength;
    }
    else if (position.y > m_stageMaxBounds.y)
    {
        force.y = -m_pushBackStrength;
    }

    if (position.z < m_stageMinBounds.z) 
    {
        force.z = m_pushBackStrength;
    }
    else if (position.z > m_stageMaxBounds.z) 
    {
        force.z = -m_pushBackStrength;
    }

    return force;
}

/// <summary>
/// 有効にする
/// </summary>
void PushBackBehavior::On()
{
    // フラグをオンにする
    m_isActive = true;
}

/// <summary>
/// 無効にする
/// </summary>
void PushBackBehavior::Off()
{
    // フラグをオフにする
    m_isActive = false;
}