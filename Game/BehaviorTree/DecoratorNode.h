#pragma once
#include "pch.h"
#include "Interface/IBehaviorNode.h"

class DecoratorNode : public IBehaviorNode
{
public:
	// ���O���擾����
	std::string GetName() const override { return m_name; }

public:
	// �^���`����
	using DecoratorFunction = std::function<Result(Result)>;
	// �R���X�g���N�^
	DecoratorNode(const std::string& name, std::unique_ptr<IBehaviorNode> child, DecoratorFunction decorator)
		:
		m_name(name),
		m_child(std::move(child)),
		m_decorator(decorator)
	{
	}

	// ���s����
	Result Tick() override
	{
		// �q�m�[�h�����s����
		return m_decorator(m_child->Tick());
	}

private:
	// ���O
	std::string m_name;
	// �q�m�[�h
	std::unique_ptr<IBehaviorNode> m_child;
	// �f�R���[�^
	DecoratorFunction m_decorator;
};