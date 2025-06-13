#pragma once
#include "Game/Object/Object.h"

class ISteeringBehavior
{
public:
    virtual ~ISteeringBehavior() = default;

    // �I��
    virtual void On()  = 0;
    // �I�t
    virtual void Off()  = 0;

    /// �X�e�A�����O�͂��v�Z
    virtual DirectX::SimpleMath::Vector3 Calculate()  = 0;
};