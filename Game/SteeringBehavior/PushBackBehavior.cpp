// ============================================
// 
// ファイル名: PushBackBehavior.h
// 概要: ステージないに戻すビヘイビア
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/SteeringBehavior/PushBackBehavior.h"
#include "Interface/IObject.h"

const DirectX::SimpleMath::Vector3 PushBackBehavior::STAGE_MIN_BOUNDS = { -10.0f , -10.0f , -10.0f };
const DirectX::SimpleMath::Vector3 PushBackBehavior::STAGE_MAX_BOUNDS = {  10.0f ,  10.0f ,  10.0f };

const float PushBackBehavior::PUSH_BACK_STRENGTH = 10.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">対象のオブジェクト</param>
PushBackBehavior::PushBackBehavior(IObject* object)
    :
    m_object(object)
{
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