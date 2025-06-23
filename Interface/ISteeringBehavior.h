#pragma once
#include "Game/Object/Object.h"

// 行動タイプ
enum BEHAVIOR_TYPE
{
	NONE        = 0x0000,			// なし
	KNOCK_BACK  = 0x0001,
    FLOATING    = 0x0002,
	FLOAT_FORCE = 0x0004,
	PUSH_BACK   = 0x00010,
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