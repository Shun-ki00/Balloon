#pragma once
#include "Interface/IState.h"

class Object;

class EnemyAttackState : public IState
{
public:
	// �R���X�g���N�^
	EnemyAttackState(Object* player);
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

public:

private:

	Object* m_player;

	float m_elapsedTime;

	float m_moveingTime;
};