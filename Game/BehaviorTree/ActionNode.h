#pragma once
#include "pch.h"
#include "Interface/IBehaviorNode.h"


class ActionNode : public IBehaviorNode
{
public:
	// ���O���擾����
	std::string GetName() const override { return m_name; }

	// �^���`����
	using ActionFunction = std::function<Result()>;

	// �R���X�g���N�^
	ActionNode(const std::string& name, ActionFunction condition)
		:
		m_name(name),
		m_condition(condition)
	{

	}

	// ���s����
	Result Tick() override
	{
		// �R���f�B�V�������m�F����
		return m_condition();
	}


private:

	// ���O
	std::string m_name;
	// �R���f�B�V����
	ActionFunction m_condition;

};
