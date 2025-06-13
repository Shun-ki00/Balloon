#include "pch.h"
#include "Game/SteeringBehavior/KnockbackBehavior.h"
#include "Game/Object/Object.h"
#include "Game/Parameters/Parameters.h"




KnockbackBehavior::KnockbackBehavior(Object* object)
	:
	m_object(object),
	m_target{},
    m_count{}
{
    // パラメータの設定
    m_knockbackRadius = Parameters::GetInstance()->GetParameter(ParametersID::STEERING_BEHAVIOR,ParameterKeysF::KnockbackRadius);
    m_knockbackFoce   = Parameters::GetInstance()->GetParameter(ParametersID::STEERING_BEHAVIOR, ParameterKeysF::KnockbackFoce);
    m_knockbackCount  = Parameters::GetInstance()->GetParameter(ParametersID::STEERING_BEHAVIOR, ParameterKeysF::KnockbackCount);
    m_isKnockedBack   = false;
}

DirectX::SimpleMath::Vector3 KnockbackBehavior::Calculate() 
{
    // デバッグの時のみパラメータを更新し続ける
#ifdef _DEBUG

     // パラメータの設定
    m_knockbackRadius = Parameters::GetInstance()->GetParameter(ParametersID::STEERING_BEHAVIOR, ParameterKeysF::KnockbackRadius);
    m_knockbackFoce = Parameters::GetInstance()->GetParameter(ParametersID::STEERING_BEHAVIOR, ParameterKeysF::KnockbackFoce);
    m_knockbackCount = Parameters::GetInstance()->GetParameter(ParametersID::STEERING_BEHAVIOR, ParameterKeysF::KnockbackCount);

#endif

    // 範囲外のときは計算を行わない
    if (!IsWithinKnockbackRange() || m_isKnockedBack)
    {
        m_isKnockedBack = false;
        return DirectX::SimpleMath::Vector3::Zero;
    }

    // ノックバックカウント追加
    m_count++;
    // ノックバック回数上限を超えた場合
    if (m_count >= m_knockbackCount)
    {
        m_count = 0;
        m_isKnockedBack = true;
    }

    // オブジェクトの進行方向（または向き）を取得
    DirectX::SimpleMath::Vector3 forward = m_object->GetVelocity();

    // オブジェクトの速度をリセット
    // m_object->SetVelocity(DirectX::SimpleMath::Vector3::Zero);

    forward = { forward.x , 0.0f , forward.z };

    // もし速度がない場合回転からノックバックする方向を決定する
    if (forward.Length() < 0.001f) 
    {
        forward = DirectX::SimpleMath::Vector3::Transform(
            DirectX::SimpleMath::Vector3::UnitX,
            m_object->GetTransform()->GetLocalRotation()
        );
    }

    // 正規化
    forward.Normalize();

    // 逆方向へノックバックさせる
    return -forward * m_knockbackFoce;
}


bool KnockbackBehavior::IsWithinKnockbackRange() 
{
    if (!m_target) return false;

    // 自分の座標
    auto myPosition = m_object->GetTransform()->GetLocalPosition();
    // ターゲットの座標
    auto targetPosition = m_target->GetTransform()->GetLocalPosition();

    // 距離を計算
    float distance = (myPosition - targetPosition).Length();

    // 範囲内かどうか
    return distance < m_knockbackRadius;
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