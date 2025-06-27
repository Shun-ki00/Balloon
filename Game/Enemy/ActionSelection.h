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

	// ルートノードを取得する
	SelectorNode* GetRootNode() const { return m_root.get(); }

public:

	ActionSelection();
	~ActionSelection() = default;

	// 初期化処理
	void Initialize(Enemy* enemy);

private:

	// アクションノードを作成する
	void CreateActionNode();

private:

	// 敵オブジェクト
	Enemy* m_enemy;

	// 判定処理
	AIConditions* m_aiConditions;

	// ルートノード
	std::unique_ptr<SelectorNode> m_root;

	// ==== シーケンスノード 失敗したら終了 ====

	// プレイヤーの範囲外にいるかどうか
	std::unique_ptr<SequenceNode> m_outOfRange;
	// プレイヤーの範囲内にいるかどうか
	std::unique_ptr<SequenceNode> m_inOfRange;

	// プレイヤーより上にいるとき
	std::unique_ptr<SequenceNode> m_aboveSequenceNode;
	// プレイヤーより下にいるとき
	std::unique_ptr<SequenceNode> m_belowSequenceNode;

	// HPが高い時
	std::unique_ptr<SequenceNode> m_hightHpSequenceNode;
	// HPが中間の時
	std::unique_ptr<SequenceNode> m_mediumHpSequenceNode;
	// HPが低い時
	std::unique_ptr<SequenceNode> m_lowHpSequenceNode;

	// 攻撃ノード
	std::unique_ptr<SequenceNode> m_AttackSequenceNode;


	// ==== セレクターノード　一度成功したら終了 ====

	// 体力のセレクターノード
	std::unique_ptr<SelectorNode> m_hpSelectorNode;

	// 高さのセレクタ
	std::unique_ptr<SelectorNode> m_hightSelectorNode;



	// ==== アクションノード ====

	// プレイヤーより上にいるかどうかチェック
	std::unique_ptr<ActionNode> m_isAboveCheck;
	// プレイヤーより下にいるかどうかチェック
	std::unique_ptr<ActionNode> m_isBelowCheck;

	// プレイヤーの一定範囲内にいるかどうか
	std::unique_ptr<ActionNode> m_isInRangeCheck;
	// プレイヤーの一定範囲外にいるかどうか
	std::unique_ptr<ActionNode> m_isOutRangeCheck;

	// プレイヤーの攻撃範囲内にいるかどうか
	std::unique_ptr<ActionNode> m_isAttackRangeCheck;

	// === ステート変更ノード ===

	// 敵をアイドル状態に変更（徘徊）
	std::unique_ptr<ActionNode> m_ChangeIdlingState;
	// 敵の追いかける処理
	std::unique_ptr<ActionNode> m_ChangeChaseState;

	// 敵を移動状態に変更

	// 敵をアタック状態に変更
	std::unique_ptr<ActionNode> m_ChangeAttackState;

	// === メッセンジャーを送信 === 

	// メッセージ送信風船を膨らませるのをオフにする
	std::unique_ptr<ActionNode> m_messageBalloonScaleOff;
	// メッセージ送信風船を膨らませるのをオンにする
	std::unique_ptr<ActionNode> m_messageBalloonScaleOn;
	

	// 体力のチェックノード
	std::unique_ptr<IBehaviorNode> m_hightHpCheck;
	std::unique_ptr<IBehaviorNode> m_mediumHpCheck;
	std::unique_ptr<IBehaviorNode> m_lowHpCheck;
	

};