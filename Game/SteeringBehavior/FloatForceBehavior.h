#pragma once
#include "Interface/ISteeringBehavior.h"

class IObject;


class FloatForceBehavior : public ISteeringBehavior
{
public:
    // 強さを設定する
    void SetForceStrength(const float& strength) { m_forcePower = strength; }
    // 力の向きを設定
    void SetForceDirection(const DirectX::SimpleMath::Vector3& direction) { m_direction = direction; }

    // ビヘイビアを有効にする
    void On() override;
    // ビヘイビアを無効にする
    void Off() override;

    // ステアリング力を計算する
    DirectX::SimpleMath::Vector3 Calculate() override;

    // コンストラクタ
    FloatForceBehavior();
    // デストラクタ
    ~FloatForceBehavior() override = default;

private:

    // 有効かどうかのフラグ
    bool m_isActive;

    // 力の向き
    DirectX::SimpleMath::Vector3 m_direction;
    // 力の大きさ
    float m_forcePower;
};