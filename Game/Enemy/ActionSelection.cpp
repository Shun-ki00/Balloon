#include "pch.h"
#include "Game/Enemy/AIConditions.h"
#include "Game/Enemy/ActionSelection.h"
#include "Game/BehaviorTree/SelectorNode.h"
#include "Game/BehaviorTree/ActionNode.h"
#include "Game/Enemy/Enemy.h"


ActionSelection::ActionSelection()
{
	// �C���X�^���X���擾����
	m_aiConditions = AIConditions::GetInstance();
}

void ActionSelection::Initialize(Enemy* enemy)
{
	// �G�̃I�u�W�F�N�g���擾����
	m_enemy = enemy;

	// HP��3�i�K�ɕ�����
	// ��HP�`�F�b�N�m�[�h�𐶐�����
	m_hightHpCheck = std::make_unique<ActionNode>("HP >= 70", [&]()
		{
			// HP��70�ȏ�͐�����Ԃ�����ȊO�̏ꍇ�͎��s��Ԃ�
			return (m_enemy->GetHp() >= 70) ? Result::SUCCESS : Result::FAILURE;
		});

	// ��HP�`�F�b�N�m�[�h�𐶐�����
	m_mediumHpCheck = std::make_unique<ActionNode>("50 <= HP < 70", [&]()
		{
			// HP��50�ȏォ��70�����̏ꍇ�͐�����Ԃ�����ȊO�̏ꍇ�͎��s��Ԃ�
			return (m_enemy->GetHp() >= 50 && m_enemy->GetHp() < 70) ? Result::SUCCESS : Result::FAILURE;
		});

	// ��HP�`�F�b�N�m�[�h�𐶐�����
	m_lowHpCheck = std::make_unique<ActionNode>("HP < 50", [&]()
		{
			// HP��50�����̏ꍇ�͐�����Ԃ�����ȊO�̏ꍇ�͎��s��Ԃ�
			return (m_enemy->GetHp() < 50) ? Result::SUCCESS : Result::FAILURE;
		});


	// �v���C���[����ɂ��邩�ǂ����`�F�b�N
	m_isAboveCheck = std::make_unique<ActionNode>("Above", [&]()
		{
			return m_aiConditions->IsAbovePlayer(m_enemy, 1.0f) ? Result::SUCCESS : Result::FAILURE;
		});

	// �v���C���[��艺�ɂ��邩�ǂ����`�F�b�N
	m_isBelowCheck = std::make_unique<ActionNode>("Below", [&]()
		{
			return m_aiConditions->IsBelowPlayer(m_enemy, 0.0f) ? Result::SUCCESS : Result::FAILURE;
		});
	
	// �v���C���[�̈��͈͂ɂ��邩�ǂ���
	m_isInRangeCheck = std::make_unique<ActionNode>("InRange", [&]()
		{
			return m_aiConditions->IsPlayerInRange(m_enemy, {0.0f , 2.0f , -1.0f }, 4.0f) ? Result::SUCCESS : Result::FAILURE;
		});

	m_hpSelectorNode = std::make_unique<SelectorNode>("HpSelector");
	m_hpSelectorNode->AddChild(m_hightHpCheck.get());
	m_hpSelectorNode->AddChild(m_mediumHpCheck.get());
	m_hpSelectorNode->AddChild(m_lowHpCheck.get());

	// ���[�g�m�[�h�̍쐬
	m_root = std::make_unique<SelectorNode>("Root");

	// �q��ǉ�����
	m_root->AddChild(m_hpSelectorNode.get());


}