#pragma once
#include "Interface/ISteeringBehavior.h"

class Object;

class KnockbackBehavior : public ISteeringBehavior
{

public:

    // �^�[�Q�b�g�I�u�W�F�N�g��ݒ肷��
    void SetTargetObject(Object* target) { m_target = target; }

    // �r�w�C�r�A��L���ɂ���
    void On() override;
    // �r�w�C�r�A�𖳌��ɂ���
    void Off() override;

    // �R���X�g���N�^
    KnockbackBehavior(Object* object);
    // �f�X�g���N�^
    ~KnockbackBehavior() override = default;

    // �X�e�A�����O�͂��v�Z����
    DirectX::SimpleMath::Vector3 Calculate() override;

    // �m�b�N�o�b�N�͈͓����v�Z����
    bool IsWithinKnockbackRange();
  
private:

    // �L�����ǂ����̃t���O
    bool m_isActive;

    // �m�b�N�o�b�N�Ώ�
    Object* m_object;
    // �^�[�Q�b�g
    Object* m_target;

    // �m�b�N�o�b�N��
    int m_knockbackCount;
    // �������a
    float m_knockbackRadius;
    // �m�b�N�o�b�N��
    float m_knockbackFoce;
    // �m�b�N�o�b�N�ς݂�
    bool m_isKnockedBack;

    int m_count;
};