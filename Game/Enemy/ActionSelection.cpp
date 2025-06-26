#include "pch.h"
#include "Game/Enemy/AIConditions.h"
#include "Game/Enemy/ActionSelection.h"
#include "Game/BehaviorTree/SelectorNode.h"
#include "Game/BehaviorTree/SequenceNode.h"
#include "Game/BehaviorTree/ActionNode.h"
#include "Game/Enemy/Enemy.h"
#include "Game/Player/Player.h"
#include "Game/Message/ObjectMessenger.h"


ActionSelection::ActionSelection()
{
	// �C���X�^���X���擾����
	m_aiConditions = AIConditions::GetInstance();
}

void ActionSelection::Initialize(Enemy* enemy)
{
	// �G�̃I�u�W�F�N�g���擾����
	m_enemy = enemy;

	m_aiConditions->SetTargetObject(
	dynamic_cast<Player*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER)[0]));

	// �A�N�V�����m�[�h���쐬����
	this->CreateActionNode();

	// �v���C���[�͈̔͊O�ɂ���Ƃ��@�m�[�h�쐬
	m_outOfRange = std::make_unique<SequenceNode>("OutOfRangeSequence");
	// �q�m�[�h��ǉ�
	m_outOfRange->AddChild(m_isOutRangeCheck.get());
	m_outOfRange->AddChild(m_ChangeIdlingState.get());

	// �v���C���[�͈͓̔��ɂ���Ƃ��@�m�[�h�쐬
	m_inOfRange = std::make_unique<SequenceNode>("InOfRangeSequence");
	
	// �`�F�b�N����A�N�V�����m�[�h��ǉ�
	m_inOfRange->AddChild(m_isInRangeCheck.get());
	m_inOfRange->AddChild(m_ChangeChaseState.get());

	// HP���Ŕ��肷��A�N�V�����m�[�h��ǉ�
	/*m_hpSelectorNode = std::make_unique<SelectorNode>("HpSelector");
	m_hpSelectorNode->AddChild(m_hightHpCheck.get());
	m_hpSelectorNode->AddChild(m_mediumHpCheck.get());
	m_hpSelectorNode->AddChild(m_lowHpCheck.get());*/

	// �g�o�Z���N�^�[��ǉ�
	//m_inOfRange->AddChild(m_hpSelectorNode.get());

	// ���[�g�m�[�h�̍쐬
	m_root = std::make_unique<SelectorNode>("Root");

	// �q��ǉ�����
	m_root->AddChild(m_outOfRange.get());
	m_root->AddChild(m_inOfRange.get());

}


void ActionSelection::CreateActionNode()
{
	// �v���C���[�̈��͈͓��ɂ��邩�ǂ���
	m_isInRangeCheck = std::make_unique<ActionNode>("InRange", [&]()
		{
			return m_aiConditions->IsPlayerInRange(m_enemy, { 0.0f , 2.0f , -1.0f }, 4.0f) ? Result::SUCCESS : Result::FAILURE;
		});
	// �v���C���[�̈��͈͊O�ɂ��邩�ǂ���
	m_isOutRangeCheck = std::make_unique<ActionNode>("OutRange", [&]()
		{
			return !m_aiConditions->IsPlayerInRange(m_enemy, { 0.0f , 2.0f , -1.0f }, 4.0f) ? Result::SUCCESS : Result::FAILURE;
		});

	// �G�̃X�e�[�g��ύX
	m_ChangeIdlingState = std::make_unique<ActionNode>("IdlingState", [&]()
		{
			// �X�e�[�g�ύX�ʒm�𑗂�
			m_enemy->OnMessegeAccepted({ Message::MessageID::ENEMY_WANDER });

			return Result::SUCCESS;
		});

	// �G�̃X�e�[�g��ύX
	m_ChangeChaseState = std::make_unique<ActionNode>("ChaseState", [&]()
		{
			// �X�e�[�g�ύX�ʒm�𑗂�
			m_enemy->OnMessegeAccepted({ Message::MessageID::ENEMY_CHASE });

			return Result::SUCCESS;
		});
}