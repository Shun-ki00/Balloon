#include "pch.h"
#include "Game/Enemy/AIConditions.h"
#include "Game/Enemy/ActionSelection.h"
#include "Game/BehaviorTree/SelectorNode.h"
#include "Game/BehaviorTree/SequenceNode.h"
#include "Game/BehaviorTree/ActionNode.h"
#include "Game/Enemy/Enemy.h"
#include "Game/Player/Player.h"
#include "Game/Message/ObjectMessenger.h"

/// <summary>
/// コンストラクタ
/// </summary>
ActionSelection::ActionSelection()
	:
    m_enemy{},
    m_aiConditions{},
    m_root{},
    m_outOfRange{},
    m_inOfRange{},
    m_aboveSequenceNode{},
    m_belowSequenceNode{},
    m_hightHpSequenceNode{},
    m_mediumHpSequenceNode{},
    m_lowHpSequenceNode{},
    m_AttackSequenceNode{},
    m_hpSelectorNode{},
    m_hightSelectorNode{},
    m_isAboveCheck{},
    m_isBelowCheck{},
    m_isInRangeCheck{},
    m_isOutRangeCheck{},
    m_isAttackRangeCheck{},
    m_ChangeIdlingState{},
    m_ChangeChaseState{},
    m_ChangeAttackState{},
    m_messageBalloonScaleOff{},
    m_messageBalloonScaleOn{},
    m_hightHpCheck{},
    m_mediumHpCheck{},
    m_lowHpCheck{}
{
	// インスタンスを取得する
	m_aiConditions = AIConditions::GetInstance();
}

void ActionSelection::Initialize(Enemy* enemy)
{
    // ===========================================
    // 初期設定
    // ===========================================
    // 敵のオブジェクトを取得する
    m_enemy = enemy;

    // AI条件にターゲットプレイヤーを設定する
    m_aiConditions->SetTargetObject(
        dynamic_cast<Player*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER)[0])
    );

    // 基本アクションノードを作成する
    this->CreateActionNode();

    // ===========================================
    // 攻撃関連ノードの作成
    // ===========================================
    // 攻撃シーケンスノード（攻撃範囲チェック → 攻撃状態変更）
    m_AttackSequenceNode = std::make_unique<SequenceNode>("AttackSequenceNode");
    m_AttackSequenceNode->AddChild(m_isAttackRangeCheck.get());
    m_AttackSequenceNode->AddChild(m_ChangeAttackState.get());

    // プレイヤーより上にいる時のシーケンス（上チェック → メッセージバルーンOFF → 攻撃）
    m_aboveSequenceNode = std::make_unique<SequenceNode>("AboveSequenceNode");
    m_aboveSequenceNode->AddChild(m_isAboveCheck.get());
    m_aboveSequenceNode->AddChild(m_messageBalloonScaleOff.get());
    m_aboveSequenceNode->AddChild(m_AttackSequenceNode.get());

    // プレイヤーより下にいる時のシーケンス（下チェック → メッセージバルーンON）
    m_belowSequenceNode = std::make_unique<SequenceNode>("BelowSequenceNode");
    m_belowSequenceNode->AddChild(m_isBelowCheck.get());
    m_belowSequenceNode->AddChild(m_messageBalloonScaleOn.get());

    // 高さ判定セレクター（上 または 下）
    m_hightSelectorNode = std::make_unique<SelectorNode>("HeightSelectorNode");
    m_hightSelectorNode->AddChild(m_aboveSequenceNode.get());
    m_hightSelectorNode->AddChild(m_belowSequenceNode.get());

    // ===========================================
    // HP判定ノードの作成
    // ===========================================
    // HP高い時のシーケンス（HPチェック → 追跡状態 → 高さ判定 → 攻撃）
    m_hightHpSequenceNode = std::make_unique<SequenceNode>("HighHpSequenceNode");
    m_hightHpSequenceNode->AddChild(m_hightHpCheck.get());
    m_hightHpSequenceNode->AddChild(m_ChangeChaseState.get());
    m_hightHpSequenceNode->AddChild(m_hightSelectorNode.get());
    m_hightHpSequenceNode->AddChild(m_AttackSequenceNode.get());

    // HP中間時のシーケンス（HPチェック → 追跡状態 → 高さ判定 → 攻撃）
    m_mediumHpSequenceNode = std::make_unique<SequenceNode>("MediumHpSequenceNode");
    m_mediumHpSequenceNode->AddChild(m_mediumHpCheck.get());
    m_mediumHpSequenceNode->AddChild(m_ChangeChaseState.get());
    m_mediumHpSequenceNode->AddChild(m_hightSelectorNode.get());
    m_mediumHpSequenceNode->AddChild(m_AttackSequenceNode.get());

    // HP低い時のシーケンス（HPチェックのみ - 将来の拡張用）
    m_lowHpSequenceNode = std::make_unique<SequenceNode>("LowHpSequenceNode");
    m_lowHpSequenceNode->AddChild(m_lowHpCheck.get());

    // m_lowHpSequenceNode->AddChild(m_ChangeChaseState.get());
    // m_lowHpSequenceNode->AddChild(m_messageBalloonScaleOff.get());

    // HPセレクター（高HP または 中HP または 低HP）
    m_hpSelectorNode = std::make_unique<SelectorNode>("HpSelectorNode");
    m_hpSelectorNode->AddChild(m_hightHpSequenceNode.get());
    m_hpSelectorNode->AddChild(m_mediumHpSequenceNode.get());
    m_hpSelectorNode->AddChild(m_lowHpSequenceNode.get());

    // ===========================================
    // 範囲判定ノードの作成
    // ===========================================
    // プレイヤー範囲外時のシーケンス（範囲外チェック → アイドル状態変更）
    m_outOfRange = std::make_unique<SequenceNode>("OutOfRangeSequenceNode");
    m_outOfRange->AddChild(m_isOutRangeCheck.get());
    m_outOfRange->AddChild(m_ChangeIdlingState.get());

    // プレイヤー範囲内時のシーケンス（範囲内チェック → HP判定実行）
    m_inOfRange = std::make_unique<SequenceNode>("InOfRangeSequenceNode");
    m_inOfRange->AddChild(m_isInRangeCheck.get());
    m_inOfRange->AddChild(m_hpSelectorNode.get());

    // ===========================================
    // ルートノードの作成と全体構成
    // ===========================================
    // ルートセレクター（範囲外処理 または 範囲内処理）
    m_root = std::make_unique<SelectorNode>("RootSelectorNode");
    m_root->AddChild(m_outOfRange.get());
    m_root->AddChild(m_inOfRange.get());
}


void ActionSelection::CreateActionNode()
{
	// プレイヤーの一定範囲内にいるかどうか
	m_isInRangeCheck = std::make_unique<ActionNode>("InRange", [&]()
		{
			return m_aiConditions->IsPlayerInRange(m_enemy, { 0.0f , 1.0f , 0.0f }, 6.0f) ? Result::SUCCESS : Result::FAILURE;
		});
	// プレイヤーの一定範囲外にいるかどうか
	m_isOutRangeCheck = std::make_unique<ActionNode>("OutRange", [&]()
		{
			return !m_aiConditions->IsPlayerInRange(m_enemy, { 0.0f , 1.0f , 0.0f }, 6.0f) ? Result::SUCCESS : Result::FAILURE;
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

	m_isAttackRangeCheck = std::make_unique<ActionNode>("AttackRangeCheck", [&]() {
		return m_aiConditions->IsPlayerInRange(m_enemy, { 0.0f , 4.0f , 0.0f }, 0.8f) ? Result::SUCCESS : Result::FAILURE;
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