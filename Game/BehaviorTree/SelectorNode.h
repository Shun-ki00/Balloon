#pragma once
#include "pch.h"
#include "Interface/IBehaviorNode.h"


class SelectorNode : public IBehaviorNode
{

public:

	// 名前を取得する
	std::string GetName() const override { return m_name; }

public:

	// コンストラクタ
	SelectorNode(const std::string& name) : m_name(name) {}
	
	// 子ノードを追加する
	void AddChild(IBehaviorNode* child)
	{
		// ノードを追加する
		m_behaviorNodes.push_back(child);
	}

	// 実行する
	Result Tick() override
	{
		for (const auto& child : m_behaviorNodes)
		{
			// 子ノードを実行する
			Result result = child->Tick();
			if (result != Result::FAILURE)
			{
				// 実行結果を返す
				return result;
			}
		}
		// 失敗を返す
		return Result::FAILURE;
	}

private:

	// 名前
	std::string m_name;
	// ビヘイビアノード配列
	std::vector<IBehaviorNode*> m_behaviorNodes;
};

