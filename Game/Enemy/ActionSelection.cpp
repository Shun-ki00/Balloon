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

	m_aboveSequenceNode = std::make_unique<SequenceNode>("aboveSequence");
	m_aboveSequenceNode->AddChild(m_isAboveCheck.get());
	m_aboveSequenceNode->AddChild(m_messageBalloonScaleOff.get());

	m_belowSequenceNode = std::make_unique<SequenceNode>("belowSequence");
	m_belowSequenceNode->AddChild(m_isBelowCheck.get());
	m_belowSequenceNode->AddChild(m_messageBalloonScaleOn.get());

	m_hightSelectorNode = std::make_unique<SelectorNode>("HightSelectorNode");
	m_hightSelectorNode->AddChild(m_aboveSequenceNode.get());
	m_hightSelectorNode->AddChild(m_belowSequenceNode.get());

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
	m_hpSelectorNode = std::make_unique<SelectorNode>("HpSelector");
	

	// HPが高い時
	m_hightHpSequenceNode = std::make_unique<SequenceNode>("HightHpSequence");
	// HPが中間の時
	m_mediumHpSequenceNode = std::make_unique<SequenceNode>("MediumHpSequence");
	// HPが低い時
	m_lowHpSequenceNode = std::make_unique<SequenceNode>("LowHpSequence");

	m_hightHpSequenceNode->AddChild(m_hightHpCheck.get());
	m_hightHpSequenceNode->AddChild(m_ChangeChaseState.get());
	m_hightHpSequenceNode->AddChild(m_hightSelectorNode.get());

	m_mediumHpSequenceNode->AddChild(m_mediumHpCheck.get());
	m_mediumHpSequenceNode->AddChild(m_ChangeChaseState.get());
	m_mediumHpSequenceNode->AddChild(m_hightSelectorNode.get());

	m_lowHpSequenceNode->AddChild(m_lowHpCheck.get());
	m_lowHpSequenceNode->AddChild(m_ChangeChaseState.get());
	//m_lowHpSequenceNode->AddChild(m_messageBalloonScaleOff.get());

	m_hpSelectorNode->AddChild(m_hightHpSequenceNode.get());
	m_hpSelectorNode->AddChild(m_mediumHpSequenceNode.get());
	m_hpSelectorNode->AddChild(m_lowHpSequenceNode.get());

	// プレイヤーの範囲内にいるならばHPチェックノードを走らせる
	m_inOfRange->AddChild(m_hpSelectorNode.get());
	

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
			return m_aiConditions->IsPlayerInRange(m_enemy, { 0.0f , 2.0f , -1.0f }, 2.0f) ? Result::SUCCESS : Result::FAILURE;
		});
	// プレイヤーの一定範囲外にいるかどうか
	m_isOutRangeCheck = std::make_unique<ActionNode>("OutRange", [&]()
		{
			return !m_aiConditions->IsPlayerInRange(m_enemy, { 0.0f , 2.0f , -1.0f }, 2.0f) ? Result::SUCCESS : Result::FAILURE;
		});


	// プレイヤーより上にいるか
	m_isAboveCheck = std::make_unique<ActionNode>("Above", [&]()
		{
			return m_aiConditions->IsAbovePlayer(m_enemy) ? Result::SUCCESS : Result::FAILURE;
		});
	// プレイヤーより下にいるか
	m_isBelowCheck = std::make_unique<ActionNode>("Below", [&]()
		{
			return m_aiConditions->IsBelowPlayer(m_enemy) ? Result::SUCCESS : Result::FAILURE;
		});


	// 高HPチェックノードを生成する
	m_hightHpCheck = std::make_unique<ActionNode>("HP >= 0.8", [&]() {
		return (m_enemy->GetHp() >= 0.8f) ? Result::SUCCESS : Result::FAILURE;
		});

	// 中HPチェックノードを生成する
	m_mediumHpCheck = std::make_unique<ActionNode>("0.8 > HP >= 0.4", [&]() {
		return (m_enemy->GetHp() < 0.8f && m_enemy->GetHp() >= 0.4f) ? Result::SUCCESS : Result::FAILURE;
		});

	// 低HPチェックノードを生成する
	m_lowHpCheck = std::make_unique<ActionNode>("HP < 0.4", [&]() {
		return (m_enemy->GetHp() < 0.4f) ? Result::SUCCESS : Result::FAILURE;
		});


	// メッセージ送信
	m_messageBalloonScaleOn = std::make_unique<ActionNode>("MessageBalloonScaleOn", [&]()
		{
			// ステート変更通知を送る
			m_enemy->OnMessegeAccepted({ Message::MessageID::ENEMY_ON_BALLOON_SCALE });

			return Result::SUCCESS;
		});
	// メッセージ送信
	m_messageBalloonScaleOff = std::make_unique<ActionNode>("MessageBalloonScaleOff", [&]()
		{
			// ステート変更通知を送る
			m_enemy->OnMessegeAccepted({ Message::MessageID::ENEMY_OFF_BALLOON_SCALE });

			return Result::SUCCESS;
		});


	// 敵のステートを変更
	m_ChangeIdlingState = std::make_unique<ActionNode>("IdlingState", [&]()
		{
			// ステート変更通知を送る
			m_enemy->OnMessegeAccepted({ Message::MessageID::ENEMY_WANDER });

			return Result::SUCCESS;
		});

	// 敵のステートを変更
	m_ChangeChaseState = std::make_unique<ActionNode>("ChaseState", [&]()
		{
			// ステート変更通知を送る
			m_enemy->OnMessegeAccepted({ Message::MessageID::ENEMY_CHASE });

			return Result::SUCCESS;
		});

	// 敵のステートを変更
	m_ChangeAttackState = std::make_unique<ActionNode>("AttackState", [&]()
		{
			// ステート変更通知を送る
			m_enemy->OnMessegeAccepted({ Message::MessageID::ENEMY_ATTACK });

			return Result::SUCCESS;
		});



	// HPアクションノード

	// プレイヤーの高さ
}