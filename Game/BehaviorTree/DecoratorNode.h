#pragma once
#include "pch.h"
#include "Interface/IBehaviorNode.h"

class DecoratorNode : public IBehaviorNode
{
public:
	// 名前を取得する
	std::string GetName() const override { return m_name; }

public:
	// 型を定義する
	using DecoratorFunction = std::function<Result(Result)>;
	// コンストラクタ
	DecoratorNode(const std::string& name, std::unique_ptr<IBehaviorNode> child, DecoratorFunction decorator)
		:
		m_name(name),
		m_child(std::move(child)),
		m_decorator(decorator)
	{
	}

	// 実行する
	Result Tick() override
	{
		// 子ノードを実行する
		return m_decorator(m_child->Tick());
	}

private:
	// 名前
	std::string m_name;
	// 子ノード
	std::unique_ptr<IBehaviorNode> m_child;
	// デコレータ
	DecoratorFunction m_decorator;
};