#include "pch.h"
#include "Game/Enemy/AIConditions.h"
#include "Game/Enemy/ActionSelection.h"
#include "Game/BehaviorTree/SelectorNode.h"
#include "Game/BehaviorTree/ActionNode.h"
#include "Game/Enemy/Enemy.h"


ActionSelection::ActionSelection()
{
	// インスタンスを取得する
	m_aiConditions = AIConditions::GetInstance();
}

void ActionSelection::Initialize(Enemy* enemy)
{
	// 敵のオブジェクトを取得する
	m_enemy = enemy;

	// HPを3段階に分ける
	// 高HPチェックノードを生成する
	m_hightHpCheck = std::make_unique<ActionNode>("HP >= 70", [&]()
		{
			// HPが70以上は成功を返しそれ以外の場合は失敗を返す
			return (m_enemy->GetHp() >= 70) ? Result::SUCCESS : Result::FAILURE;
		});

	// 中HPチェックノードを生成する
	m_mediumHpCheck = std::make_unique<ActionNode>("50 <= HP < 70", [&]()
		{
			// HPが50以上かつ70未満の場合は成功を返しそれ以外の場合は失敗を返す
			return (m_enemy->GetHp() >= 50 && m_enemy->GetHp() < 70) ? Result::SUCCESS : Result::FAILURE;
		});

	// 低HPチェックノードを生成する
	m_lowHpCheck = std::make_unique<ActionNode>("HP < 50", [&]()
		{
			// HPが50未満の場合は成功を返しそれ以外の場合は失敗を返す
			return (m_enemy->GetHp() < 50) ? Result::SUCCESS : Result::FAILURE;
		});


	// プレイヤーより上にいるかどうかチェック
	m_isAboveCheck = std::make_unique<ActionNode>("Above", [&]()
		{
			return m_aiConditions->IsAbovePlayer(m_enemy, 1.0f) ? Result::SUCCESS : Result::FAILURE;
		});

	// プレイヤーより下にいるかどうかチェック
	m_isBelowCheck = std::make_unique<ActionNode>("Below", [&]()
		{
			return m_aiConditions->IsBelowPlayer(m_enemy, 0.0f) ? Result::SUCCESS : Result::FAILURE;
		});
	
	// プレイヤーの一定範囲にいるかどうか
	m_isInRangeCheck = std::make_unique<ActionNode>("InRange", [&]()
		{
			return m_aiConditions->IsPlayerInRange(m_enemy, {0.0f , 2.0f , -1.0f }, 4.0f) ? Result::SUCCESS : Result::FAILURE;
		});

	m_hpSelectorNode = std::make_unique<SelectorNode>("HpSelector");
	m_hpSelectorNode->AddChild(m_hightHpCheck.get());
	m_hpSelectorNode->AddChild(m_mediumHpCheck.get());
	m_hpSelectorNode->AddChild(m_lowHpCheck.get());

	// ルートノードの作成
	m_root = std::make_unique<SelectorNode>("Root");

	// 子を追加する
	m_root->AddChild(m_hpSelectorNode.get());
	m_root->Tick();
	

}