#pragma once
#include "pch.h"
#include "Interface/IBehaviorNode.h"


class ActionNode : public IBehaviorNode
{
public:
	// 名前を取得する
	std::string GetName() const override { return m_name; }

	// 型を定義する
	using ActionFunction = std::function<Result()>;

	// コンストラクタ
	ActionNode(const std::string& name, ActionFunction condition)
		:
		m_name(name),
		m_condition(condition)
	{

	}

	// 実行する
	Result Tick() override
	{
		// コンディションを確認する
		return m_condition();
	}


private:

	// 名前
	std::string m_name;
	// コンディション
	ActionFunction m_condition;

};
