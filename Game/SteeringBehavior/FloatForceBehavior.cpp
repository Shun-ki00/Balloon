#include "pch.h"
#include "Game/SteeringBehavior/FloatForceBehavior.h"


/// <summary>
/// コンストラクタ
/// </summary>
FloatForceBehavior::FloatForceBehavior()
    :
    m_isActive{},
    m_direction{},
    m_forcePower{}
{
}


/// <summary>
/// 計算処理を行う
/// </summary>
/// <returns>計算結果</returns>
DirectX::SimpleMath::Vector3 FloatForceBehavior::Calculate()
{
    DirectX::SimpleMath::Vector3 force = DirectX::SimpleMath::Vector3::Zero;

    // 指定した方向に力を加える
    force = m_direction * m_forcePower;

    // 力を返す
    return force;
}

/// <summary>
/// 有効にする
/// </summary>
void FloatForceBehavior::On()
{
    // フラグをオンにする
    m_isActive = true;
}

/// <summary>
/// 無効にする
/// </summary>
void FloatForceBehavior::Off()
{
    // フラグをオフにする
    m_isActive = false;
}