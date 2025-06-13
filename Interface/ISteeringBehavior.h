#pragma once
#include "Game/Object/Object.h"

class ISteeringBehavior
{
public:
    virtual ~ISteeringBehavior() = default;

    // オン
    virtual void On()  = 0;
    // オフ
    virtual void Off()  = 0;

    /// ステアリング力を計算
    virtual DirectX::SimpleMath::Vector3 Calculate()  = 0;
};