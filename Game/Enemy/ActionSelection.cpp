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

	m_AttackSequenceNode = std::make_unique<SequenceNode>("AttackSequenceNode");
	m_AttackSequenceNode->AddChild(m_isAttackRangeCheck.get());
	m_AttackSequenceNode->AddChild(m_ChangeAttackState.get());

	m_aboveSequenceNode = std::make_unique<SequenceNode>("aboveSequence");
	m_aboveSequenceNode->AddChild(m_isAboveCheck.get());
	m_aboveSequenceNode->AddChild(m_messageBalloonScaleOff.get());
	m_aboveSequenceNode->AddChild(m_AttackSequenceNode.get());


	m_belowSequenceNode = std::make_unique<SequenceNode>("belowSequence");
	m_belowSequenceNode->AddChild(m_isBelowCheck.get());
	m_belowSequenceNode->AddChild(m_messageBalloonScaleOn.get());

	m_hightSelectorNode = std::make_unique<SelectorNode>("HightSelectorNode");
	m_hightSelectorNode->AddChild(m_aboveSequenceNode.get());
	m_hightSelectorNode->AddChild(m_belowSequenceNode.get());



	// �v���C���[�͈̔͊O�ɂ���Ƃ��@�m�[�h�쐬
	m_outOfRange = std::make_unique<SequenceNode>("OutOfRangeSequence");
	// �q�m�[�h��ǉ�
	m_outOfRange->AddChild(m_isOutRangeCheck.get());
	m_outOfRange->AddChild(m_ChangeIdlingState.get());

	// �v���C���[�͈͓̔��ɂ���Ƃ��@�m�[�h�쐬
	m_inOfRange = std::make_unique<SequenceNode>("InOfRangeSequence");
	
	// �`�F�b�N����A�N�V�����m�[�h��ǉ�
	m_inOfRange->AddChild(m_isInRangeCheck.get());

	// HP���Ŕ��肷��A�N�V�����m�[�h��ǉ�
	m_hpSelectorNode = std::make_unique<SelectorNode>("HpSelector");
	

	// HP��������
	m_hightHpSequenceNode = std::make_unique<SequenceNode>("HightHpSequence");
	// HP�����Ԃ̎�
	m_mediumHpSequenceNode = std::make_unique<SequenceNode>("MediumHpSequence");
	// HP���Ⴂ��
	m_lowHpSequenceNode = std::make_unique<SequenceNode>("LowHpSequence");

	m_hightHpSequenceNode->AddChild(m_hightHpCheck.get());
	m_hightHpSequenceNode->AddChild(m_ChangeChaseState.get());
	m_hightHpSequenceNode->AddChild(m_hightSelectorNode.get());
	m_hightHpSequenceNode->AddChild(m_AttackSequenceNode.get());
	 
	m_mediumHpSequenceNode->AddChild(m_mediumHpCheck.get());
	m_mediumHpSequenceNode->AddChild(m_ChangeChaseState.get());
	m_mediumHpSequenceNode->AddChild(m_hightSelectorNode.get());
	m_hightHpSequenceNode->AddChild(m_AttackSequenceNode.get());


	m_lowHpSequenceNode->AddChild(m_lowHpCheck.get());
	//m_lowHpSequenceNode->AddChild(m_ChangeChaseState.get());
	//m_lowHpSequenceNode->AddChild(m_messageBalloonScaleOff.get());

	m_hpSelectorNode->AddChild(m_hightHpSequenceNode.get());
	m_hpSelectorNode->AddChild(m_mediumHpSequenceNode.get());
	m_hpSelectorNode->AddChild(m_lowHpSequenceNode.get());

	// �v���C���[�͈͓̔��ɂ���Ȃ��HP�`�F�b�N�m�[�h�𑖂点��
	m_inOfRange->AddChild(m_hpSelectorNode.get());
	

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
			return m_aiConditions->IsPlayerInRange(m_enemy, { 0.0f , 1.0f , 0.0f }, 6.0f) ? Result::SUCCESS : Result::FAILURE;
		});
	// �v���C���[�̈��͈͊O�ɂ��邩�ǂ���
	m_isOutRangeCheck = std::make_unique<ActionNode>("OutRange", [&]()
		{
			return !m_aiConditions->IsPlayerInRange(m_enemy, { 0.0f , 1.0f , 0.0f }, 6.0f) ? Result::SUCCESS : Result::FAILURE;
		});


	// �v���C���[����ɂ��邩
	m_isAboveCheck = std::make_unique<ActionNode>("Above", [&]()
		{
			return m_aiConditions->IsAbovePlayer(m_enemy) ? Result::SUCCESS : Result::FAILURE;
		});
	// �v���C���[��艺�ɂ��邩
	m_isBelowCheck = std::make_unique<ActionNode>("Below", [&]()
		{
			return m_aiConditions->IsBelowPlayer(m_enemy) ? Result::SUCCESS : Result::FAILURE;
		});

	m_isAttackRangeCheck = std::make_unique<ActionNode>("AttackRangeCheck", [&]() {
		return m_aiConditions->IsPlayerInRange(m_enemy, { 0.0f , 4.0f , 0.0f }, 0.8f) ? Result::SUCCESS : Result::FAILURE;
		});


	// ��HP�`�F�b�N�m�[�h�𐶐�����
	m_hightHpCheck = std::make_unique<ActionNode>("HP >= 0.8", [&]() {
		return (m_enemy->GetHp() >= 0.8f) ? Result::SUCCESS : Result::FAILURE;
		});

	// ��HP�`�F�b�N�m�[�h�𐶐�����
	m_mediumHpCheck = std::make_unique<ActionNode>("0.8 > HP >= 0.4", [&]() {
		return (m_enemy->GetHp() < 0.8f && m_enemy->GetHp() >= 0.4f) ? Result::SUCCESS : Result::FAILURE;
		});

	// ��HP�`�F�b�N�m�[�h�𐶐�����
	m_lowHpCheck = std::make_unique<ActionNode>("HP < 0.4", [&]() {
		return (m_enemy->GetHp() < 0.4f) ? Result::SUCCESS : Result::FAILURE;
		});


	// ���b�Z�[�W���M
	m_messageBalloonScaleOn = std::make_unique<ActionNode>("MessageBalloonScaleOn", [&]()
		{
			// �X�e�[�g�ύX�ʒm�𑗂�
			m_enemy->OnMessegeAccepted({ Message::MessageID::ENEMY_ON_BALLOON_SCALE });

			return Result::SUCCESS;
		});
	// ���b�Z�[�W���M
	m_messageBalloonScaleOff = std::make_unique<ActionNode>("MessageBalloonScaleOff", [&]()
		{
			// �X�e�[�g�ύX�ʒm�𑗂�
			m_enemy->OnMessegeAccepted({ Message::MessageID::ENEMY_OFF_BALLOON_SCALE });

			return Result::SUCCESS;
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

	// �G�̃X�e�[�g��ύX
	m_ChangeAttackState = std::make_unique<ActionNode>("AttackState", [&]()
		{
			// �X�e�[�g�ύX�ʒm�𑗂�
			m_enemy->OnMessegeAccepted({ Message::MessageID::ENEMY_ATTACK });

			return Result::SUCCESS;
		}); 



	// HP�A�N�V�����m�[�h

	// �v���C���[�̍���
}