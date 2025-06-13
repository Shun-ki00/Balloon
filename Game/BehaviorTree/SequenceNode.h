#pragma once
#include "pch.h"
#include "Interface/IBehaviorNode.h"

class SequenceNode : public IBehaviorNode
{
public:
	// 名前を取得する
	std::string GetName() const override { return m_name; }

public:
	// コンストラクタ
	SequenceNode(const std::string& name)
		:
		m_name(name)
	{
	}

	// 子ノードを追加する
	void AddChild(std::unique_ptr<IBehaviorNode> child)
	{
		// ノードを追加する
		m_behaviorNodes.push_back(std::move(child));
	}

	// 実行する
	Result Tick() override
	{
		for (const auto& child : m_behaviorNodes)
		{
			// 子ノードを実行する
			Result result = child->Tick();
			if (result != Result::SUCCESS)
			{
				// 実行結果を返す
				return result;
			}
		}
		// 成功を返す
		return Result::SUCCESS;
	}

private:

	// 名前
	std::string m_name;
	// ビヘイビアノード配列
	std::vector<std::unique_ptr<IBehaviorNode>> m_behaviorNodes;

};