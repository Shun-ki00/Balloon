// ============================================
// 
// �t�@�C����: SeekBehavior.h
// �T�v: SeekBehavior.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/ISteeringBehavior.h"

class Object;


class SeekBehavior : public ISteeringBehavior
{
public:
    // �x�N�g���̌������擾����
    DirectX::SimpleMath::Vector3 GetDirection() const { return m_direction; }

    // �r�w�C�r�A��L���ɂ���
    void On() override;
    // �r�w�C�r�A�𖳌��ɂ���
    void Off() override;

    // �X�e�A�����O�͂��v�Z����
    DirectX::SimpleMath::Vector3 Calculate() override;

    // �R���X�g���N�^
    SeekBehavior(Object* object , Object* target,
        const DirectX::SimpleMath::Vector3& offset ,const float& predictionMultiplier , const float& speed);
    // �f�X�g���N�^
    ~SeekBehavior() override = default;

private:

    // �L�����ǂ����̃t���O
    bool m_isActive;

    // �I�u�W�F�N�g
    Object* m_object;
    // �ǔ�����I�u�W�F�N�g
    Object* m_target;

    // �x�N�g���̌���
    DirectX::SimpleMath::Vector3 m_direction;
    
    // �ʒu�̃I�t�Z�b�g
    DirectX::SimpleMath::Vector3 m_offset;
    // �\�����Ԃ̔{��
    float m_predictionMultiplier;
    // �ړ����x
    float m_seekSpeed;
};