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

	// アクションノード

	// ルートノード
	std::unique_ptr<SelectorNode> m_root;

	// ==== シーケンスノード ====

	// プレイヤーの範囲外にいるかどうか
	std::unique_ptr<SequenceNode> m_outOfRange;
	// プレイヤーの範囲内にいるかどうか
	std::unique_ptr<SequenceNode> m_inOfRange;


	// ==== セレクターノード ====

	// 体力のセレクターノード
	std::unique_ptr<SelectorNode> m_hpSelectorNode;


	// ==== アクションノード ====

	// プレイヤーより上にいるかどうかチェック
	std::unique_ptr<ActionNode> m_isAboveCheck;
	// プレイヤーより下にいるかどうかチェック
	std::unique_ptr<ActionNode> m_isBelowCheck;

	// プレイヤーの一定範囲内にいるかどうか
	std::unique_ptr<ActionNode> m_isInRangeCheck;
	// プレイヤーの一定範囲外にいるかどうか
	std::unique_ptr<ActionNode> m_isOutRangeCheck;

	// === ステート変更ノード ===

	// 敵をアイドル状態に変更（徘徊）
	std::unique_ptr<ActionNode> m_ChangeIdlingState;

	// 敵を移動状態に変更

	// 敵をアタック状態に変更

	
	// 体力のチェックノード
	std::unique_ptr<IBehaviorNode> m_hightHpCheck;
	std::unique_ptr<IBehaviorNode> m_mediumHpCheck;
	std::unique_ptr<IBehaviorNode> m_lowHpCheck;

};