#pragma once
#include "Interface/IBehaviorNode.h"
#include "Game/BehaviorTree/ActionNode.h"

class AIConditions;
class SelectorNode;
class Enemy;

class ActionSelection
{

public:

	ActionSelection();
	~ActionSelection() = default;

	// ����������
	void Initialize(Enemy* enemy);

private:

	// �G�I�u�W�F�N�g
	Enemy* m_enemy;

	// ���菈��
	AIConditions* m_aiConditions;

	// �A�N�V�����m�[�h

	// ���[�g�m�[�h
	std::unique_ptr<SelectorNode> m_root;

	// �v���C���[����ɂ��邩�ǂ����`�F�b�N
	std::unique_ptr<IBehaviorNode> m_isAboveCheck;
	// �v���C���[��艺�ɂ��邩�ǂ����`�F�b�N
	std::unique_ptr<IBehaviorNode> m_isBelowCheck;
	// �v���C���[�̈��͈͂ɂ��邩�ǂ���
	std::unique_ptr<IBehaviorNode> m_isInRangeCheck;

	// �̗͂̃Z���N�^�[�m�[�h
	std::unique_ptr<SelectorNode> m_hpSelectorNode;

	// �̗͂̃`�F�b�N�m�[�h
	std::unique_ptr<IBehaviorNode> m_hightHpCheck;
	std::unique_ptr<IBehaviorNode> m_mediumHpCheck;
	std::unique_ptr<IBehaviorNode> m_lowHpCheck;

};