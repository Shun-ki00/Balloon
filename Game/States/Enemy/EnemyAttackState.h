// ============================================
// 
// �t�@�C����: EnemyAttackState.h
// �T�v: EnemyAttackState.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class Object;

class EnemyAttackState : public IState
{
public:
	// �R���X�g���N�^
	EnemyAttackState(Object* enemy);
	// �f�X�g���N�^
	~EnemyAttackState() = default;
	// ����������
	void Initialize() override;
	// ���O�X�V����
	void PreUpdate() override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// ����X�V����
	void PostUpdate() override;
	// �㏈�����s��
	void Finalize() override;

private:

	// �G�I�u�W�F�N�g
	Object* m_enemy;
	// �o�ߎ���
	float m_elapsedTime;
	// �ړ�����
	float m_moveingTime;
};