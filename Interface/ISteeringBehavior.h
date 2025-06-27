#pragma once
#include "Game/Object/Object.h"

// �s���^�C�v
enum BEHAVIOR_TYPE
{
	NONE        = 0x0000,			// �Ȃ�
	KNOCK_BACK  = 0x0001,
    FLOATING    = 0x0002,
	FLOAT_FORCE = 0x0004,
	PUSH_BACK   = 0x00010,
    SEEK        = 0x00020
};


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