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

    // �L�����ǂ����̃t���O
    bool m_isActive;

    // �ΏۃI�u�W�F�N�g
    IObject* m_object;     

    // �X�e�[�W�ŏ����W
    DirectX::SimpleMath::Vector3 m_stageMinBounds; 
    // �X�e�[�W�ő���W
    DirectX::SimpleMath::Vector3 m_stageMaxBounds;  
    // �����߂���
    float m_pushBackStrength;                     
};