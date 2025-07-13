// ============================================
// 
// ファイル名: KnockbackBehavior.h
// 概要: ノックバックを行うビヘイビア
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/SteeringBehavior/KnockbackBehavior.h"
#include "Game/Object/Object.h"
#include "Game/Parameters/Parameters.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">オブジェクト</param>
/// <param name="knockbackRadius">ノックバック範囲</param>
/// <param name="knockbackCount">ノックバック回数</param>
/// <param name="knockbackFoce">ノックバックを行う力</param>
KnockbackBehavior::KnockbackBehavior(Object* object,
    const float& knockbackRadius, const int& knockbackCount, const float& knockbackFoce)
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
/// 計算処理
/// </summary>
/// <returns>計算結果</returns>
DirectX::SimpleMath::Vector3 KnockbackBehavior::Calculate() 
{
    // 非アクティブの時は計算しない
    if (!m_isActive) return DirectX::SimpleMath::Vector3::Zero;

    // 範囲外のときは計算を行わない
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

    // 最も近いターゲット方向へノックバック
    const DirectX::SimpleMath::Vector3 myPosition =
        m_object->GetTransform()->GetLocalPosition();
    IObject* nearest = nullptr;
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
/// ノックバックの範囲内かどうか
/// </summary>
/// <returns>結果</returns>
bool KnockbackBehavior::IsWithinKnockbackRange() 
{
  
    // ノックバックするオブジェクトの座標を取得
    const DirectX::SimpleMath::Vector3 myPosition =
        m_object->GetTransform()->GetLocalPosition();

    for (const auto& target : m_targets)
    {
        // ターゲットの座標を取得
        const DirectX::SimpleMath::Vector3 targetPosition =
            target->GetTransform()->GetLocalPosition();

        // 距離を計算
        const float distance = (myPosition - targetPosition).Length();

        if (distance < m_knockbackCount)
        {
            return true;
        }
    }

    return false;
}

/// <summary>
/// 有効にする
/// </summary>
void KnockbackBehavior::On()
{
    // フラグをオンにする
    m_isActive = true;
}

/// <summary>
/// 無効にする
/// </summary>
void KnockbackBehavior::Off()
{
    // フラグをオフにする
    m_isActive = false;
}