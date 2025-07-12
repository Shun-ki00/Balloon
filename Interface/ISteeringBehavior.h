#pragma once
#include "Game/Object/Object.h"

enum BEHAVIOR_TYPE
{
    NONE        = 0x0000,  // 00000000
    WIND        = 0x0001,  // 00000001
    KNOCK_BACK  = 0x0002,  // 00000010
    FLOATING    = 0x0004,  // 00000100
    FLOAT_FORCE = 0x0008,  // 00001000
    PUSH_BACK   = 0x0010,  // 00010000
    SEEK        = 0x0020   // 00100000
};


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