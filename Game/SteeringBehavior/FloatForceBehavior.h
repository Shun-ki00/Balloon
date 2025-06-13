#pragma once
#include "Interface/ISteeringBehavior.h"

class IObject;


class FloatForceBehavior : public ISteeringBehavior
{
public:
    // ������ݒ肷��
    void SetForceStrength(const float& strength) { m_forcePower = strength; }

    // �r�w�C�r�A��L���ɂ���
    void On() override;
    // �r�w�C�r�A�𖳌��ɂ���
    void Off() override;

    // �X�e�A�����O�͂��v�Z����
    DirectX::SimpleMath::Vector3 Calculate() override;

    // �R���X�g���N�^
    FloatForceBehavior();
    // �f�X�g���N�^
    ~FloatForceBehavior() override = default;

private:

    // �L�����ǂ����̃t���O
    bool m_isActive;

    // �͂̌���
    DirectX::SimpleMath::Vector3 m_direction;
    // �͂̑傫��
    float m_forcePower;
};