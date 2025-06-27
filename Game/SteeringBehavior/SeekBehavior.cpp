#include "pch.h"
#include "Game/SteeringBehavior/SeekBehavior.h"
#include "Game/Object/Object.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="object">自身オブジェクト</param>
/// <param name="target">ターゲットのオブジェクト</param>
SeekBehavior::SeekBehavior(Object* object, Object* target)
{
    m_object = object;
    m_target = target;

    m_predictionMultiplier = 2.0f;
    m_seekSpeed = 3.0f;
    m_distance = 2.0f;
}

/// <summary>
/// 計算処理を行う
/// </summary>
/// <returns>計算結果</returns>
DirectX::SimpleMath::Vector3 SeekBehavior::Calculate()
{
    if (!m_isActive) return DirectX::SimpleMath::Vector3::Zero;

    // 相手の座標
    DirectX::SimpleMath::Vector3 targetPosition = m_target->GetTransform()->GetLocalPosition();
    // 相手の速度
    const DirectX::SimpleMath::Vector3 targetVelocity = m_target->GetVelocity();

    // 相手の座標にオフセット値を加算（オブジェクトの少し後ろ）
    DirectX::SimpleMath::Vector3 offset = DirectX::SimpleMath::Vector3::Transform(
        DirectX::SimpleMath::Vector3::Forward, m_target->GetTransform()->GetLocalRotation());
    offset.Normalize();
    offset *= m_distance;
    targetPosition += offset;

    // 自分と相手の距離ベクトルを計算
    const DirectX::SimpleMath::Vector3 toTarget =
        targetPosition - m_object->GetTransform()->GetLocalPosition();

    // 自分の速度を取得
    float speed = m_object->GetVelocity().Length() + 0.01f;

    // ターゲットまでの距離を取得
    float distance = toTarget.Length();

    // ターゲットの未来位置を予測するための計算
    float lookAheadTime = (distance / speed) * m_predictionMultiplier;

    // 予測位置を計算
    DirectX::SimpleMath::Vector3 predictedPosition =
        targetPosition + targetVelocity * lookAheadTime;

    // 予測位置へ向かうベクトルを計算
    DirectX::SimpleMath::Vector3 desiredVelocity =
        predictedPosition - m_object->GetTransform()->GetLocalPosition();

    // Y方向を無視する
    desiredVelocity.y = 0.0f;

    // 正規化して向きだけを取得
    desiredVelocity.Normalize();

    // 向きを設定
    m_direction = desiredVelocity;

    // 移動速度を乗算
    desiredVelocity *= m_seekSpeed;

    return desiredVelocity;
}

/// <summary>
/// 有効にする
/// </summary>
void SeekBehavior::On()
{
    // フラグをオンにする
    m_isActive = true;
}

/// <summary>
/// 無効にする
/// </summary>
void SeekBehavior::Off()
{
    // フラグをオフにする
    m_isActive = false;
}