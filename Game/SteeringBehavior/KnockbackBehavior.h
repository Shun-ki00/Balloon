// ============================================
// 
// �t�@�C����: KnockbackBehavior.h
// �T�v: KnockbackBehavior.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/ISteeringBehavior.h"

class Object;

class KnockbackBehavior : public ISteeringBehavior
{

public:

    // �^�[�Q�b�g�I�u�W�F�N�g��ݒ肷��
    void SetTargetObject(Object* target) { m_targets.push_back(target); }

    // �r�w�C�r�A��L���ɂ���
    void On() override;
    // �r�w�C�r�A�𖳌��ɂ���
    void Off() override;

    // �R���X�g���N�^
    KnockbackBehavior(Object* object,const float& knockbackRadius,const int& knockbackCount,const float& knockbackFoce);
    // �f�X�g���N�^
    ~KnockbackBehavior() override = default;

    // �X�e�A�����O�͂��v�Z����
    DirectX::SimpleMath::Vector3 Calculate() override;

private:

    // �m�b�N�o�b�N�͈͓����v�Z����
    bool IsWithinKnockbackRange();
  
private:

    // �L�����ǂ����̃t���O
    bool m_isActive;

    // �m�b�N�o�b�N�Ώ�
    Object* m_object;
    // �^�[�Q�b�g
    std::vector<Object*> m_targets;

    // �������a
    float m_knockbackRadius;
    // �m�b�N�o�b�N��
    int m_knockbackCount;
    // �m�b�N�o�b�N��
    float m_knockbackFoce;
    // �m�b�N�o�b�N�ς݂�
    bool m_isKnockedBack;

    int m_count;
};