// ============================================
// 
// �t�@�C����: PushBackBehavior.h
// �T�v: PushBackBehavior.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/ISteeringBehavior.h"


class PushBackBehavior : public ISteeringBehavior
{
public:

    // �r�w�C�r�A��L���ɂ���
    void On() override;
    // �r�w�C�r�A�𖳌��ɂ���
    void Off() override;

    // �X�e�A�����O�͂��v�Z����
    DirectX::SimpleMath::Vector3 Calculate() override;

    // �R���X�g���N�^
    PushBackBehavior(IObject* object);
    // �f�X�g���N�^
    ~PushBackBehavior() override = default;

private:

    // �X�e�[�W�͈̔�
    static const DirectX::SimpleMath::Vector3 STAGE_MIN_BOUNDS;
    static const DirectX::SimpleMath::Vector3 STAGE_MAX_BOUNDS;
    // �����߂���
    static const float PUSH_BACK_STRENGTH;



private:

    // �L�����ǂ����̃t���O
    bool m_isActive;

    // �ΏۃI�u�W�F�N�g
    IObject* m_object;            
};