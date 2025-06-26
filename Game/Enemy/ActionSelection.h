#pragma once
#include "Interface/IBehaviorNode.h"
#include "Game/BehaviorTree/ActionNode.h"
#include "Game/BehaviorTree/SequenceNode.h"

class AIConditions;
class SelectorNode;
class SequenceNode;
class ActionNode;
class Enemy;

class ActionSelection
{
public:

	// ���[�g�m�[�h���擾����
	SelectorNode* GetRootNode() const { return m_root.get(); }

public:

	ActionSelection();
	~ActionSelection() = default;

	// ����������
	void Initialize(Enemy* enemy);

private:

	// �A�N�V�����m�[�h���쐬����
	void CreateActionNode();

private:

	// �G�I�u�W�F�N�g
	Enemy* m_enemy;

	// ���菈��
	AIConditions* m_aiConditions;

	// �A�N�V�����m�[�h

	// ���[�g�m�[�h
	std::unique_ptr<SelectorNode> m_root;

	// ==== �V�[�P���X�m�[�h ====

	// �v���C���[�͈̔͊O�ɂ��邩�ǂ���
	std::unique_ptr<SequenceNode> m_outOfRange;
	// �v���C���[�͈͓̔��ɂ��邩�ǂ���
	std::unique_ptr<SequenceNode> m_inOfRange;


	// ==== �Z���N�^�[�m�[�h ====

	// �̗͂̃Z���N�^�[�m�[�h
	std::unique_ptr<SelectorNode> m_hpSelectorNode;


	// ==== �A�N�V�����m�[�h ====

	// �v���C���[����ɂ��邩�ǂ����`�F�b�N
	std::unique_ptr<ActionNode> m_isAboveCheck;
	// �v���C���[��艺�ɂ��邩�ǂ����`�F�b�N
	std::unique_ptr<ActionNode> m_isBelowCheck;

	// �v���C���[�̈��͈͓��ɂ��邩�ǂ���
	std::unique_ptr<ActionNode> m_isInRangeCheck;
	// �v���C���[�̈��͈͊O�ɂ��邩�ǂ���
	std::unique_ptr<ActionNode> m_isOutRangeCheck;

	// === �X�e�[�g�ύX�m�[�h ===

	// �G���A�C�h����ԂɕύX�i�p�j�j
	std::unique_ptr<ActionNode> m_ChangeIdlingState;
	// �G�̒ǂ������鏈��
	std::unique_ptr<ActionNode> m_ChangeChaseState;

	// �G���ړ���ԂɕύX

	// �G���A�^�b�N��ԂɕύX

	
	// �̗͂̃`�F�b�N�m�[�h
	std::unique_ptr<IBehaviorNode> m_hightHpCheck;
	std::unique_ptr<IBehaviorNode> m_mediumHpCheck;
	std::unique_ptr<IBehaviorNode> m_lowHpCheck;

};