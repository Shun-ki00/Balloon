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
	// インスタンスを取得する
	m_aiConditions = AIConditions::GetInstance();
}

void ActionSelection::Initialize(Enemy* enemy)
{
	// 敵のオブジェクトを取得する
	m_enemy = enemy;

	m_aiConditions->SetTargetObject(
	dynamic_cast<Player*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER)[0]));

	// アクションノードを作成する
	this->CreateActionNode();

	// プレイヤーの範囲外にいるとき　ノード作成
	m_outOfRange = std::make_unique<SequenceNode>("OutOfRangeSequence");
	// 子ノードを追加
	m_outOfRange->AddChild(m_isOutRangeCheck.get());
	m_outOfRange->AddChild(m_ChangeIdlingState.get());

	// プレイヤーの範囲内にいるとき　ノード作成
	m_inOfRange = std::make_unique<SequenceNode>("InOfRangeSequence");
	
	// チェックするアクションノードを追加
	m_inOfRange->AddChild(m_isInRangeCheck.get());

	// HPをで判定するアクションノードを追加
	/*m_hpSelectorNode = std::make_unique<SelectorNode>("HpSelector");
	m_hpSelectorNode->AddChild(m_hightHpCheck.get());
	m_hpSelectorNode->AddChild(m_mediumHpCheck.get());
	m_hpSelectorNode->AddChild(m_lowHpCheck.get());*/

	// ＨＰセレクターを追加
	//m_inOfRange->AddChild(m_hpSelectorNode.get());

	// ルートノードの作成
	m_root = std::make_unique<SelectorNode>("Root");

	// 子を追加する
	m_root->AddChild(m_outOfRange.get());
	m_root->AddChild(m_inOfRange.get());

}


void ActionSelection::CreateActionNode()
{
	// プレイヤーの一定範囲内にいるかどうか
	m_isInRangeCheck = std::make_unique<ActionNode>("InRange", [&]()
		{
			return m_aiConditions->IsPlayerInRange(m_enemy, { 0.0f , 2.0f , -1.0f }, 4.0f) ? Result::SUCCESS : Result::FAILURE;
		});
	// プレイヤーの一定範囲外にいるかどうか
	m_isOutRangeCheck = std::make_unique<ActionNode>("OutRange", [&]()
		{
			return !m_aiConditions->IsPlayerInRange(m_enemy, { 0.0f , 2.0f , -1.0f }, 4.0f) ? Result::SUCCESS : Result::FAILURE;
		});

	// 敵のステートを変更
	m_ChangeIdlingState = std::make_unique<ActionNode>("OutRange", [&]()
		{
			// ステート変更通知を送る
			m_enemy->OnMessegeAccepted({ Message::MessageID::ENEMY_WANDER });

			return Result::SUCCESS;
		});
}