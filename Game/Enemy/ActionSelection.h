#pragma once
#include "Interface/IBehaviorNode.h"
#include "Game/BehaviorTree/ActionNode.h"

class AIConditions;
class SelectorNode;
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

	// 敵オブジェクト
	Enemy* m_enemy;

	// 判定処理
	AIConditions* m_aiConditions;

	// アクションノード

	// ルートノード
	std::unique_ptr<SelectorNode> m_root;

	// プレイヤーより上にいるかどうかチェック
	std::unique_ptr<IBehaviorNode> m_isAboveCheck;
	// プレイヤーより下にいるかどうかチェック
	std::unique_ptr<IBehaviorNode> m_isBelowCheck;
	// プレイヤーの一定範囲にいるかどうか
	std::unique_ptr<IBehaviorNode> m_isInRangeCheck;

	// 体力のセレクターノード
	std::unique_ptr<SelectorNode> m_hpSelectorNode;

	// 体力のチェックノード
	std::unique_ptr<IBehaviorNode> m_hightHpCheck;
	std::unique_ptr<IBehaviorNode> m_mediumHpCheck;
	std::unique_ptr<IBehaviorNode> m_lowHpCheck;

};