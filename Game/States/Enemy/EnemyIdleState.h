// ============================================
// 
// �t�@�C����: EnemyIdleState.h
// �T�v: EnemyIdleState.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class EnemyIdleState : public IState
{
public:
	// �R���X�g���N�^
	EnemyIdleState();
	// �f�X�g���N�^
	~EnemyIdleState() override = default;
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
};