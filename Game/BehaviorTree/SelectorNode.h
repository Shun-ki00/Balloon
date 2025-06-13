#pragma once
#include "pch.h"
#include "Interface/IBehaviorNode.h"


class SelectorNode : public IBehaviorNode
{

public:

	// ���O���擾����
	std::string GetName() const override { return m_name; }

public:

	// �R���X�g���N�^
	SelectorNode(const std::string& name) : m_name(name) {}
	
	// �q�m�[�h��ǉ�����
	void AddChild(IBehaviorNode* child)
	{
		// �m�[�h��ǉ�����
		m_behaviorNodes.push_back(child);
	}

	// ���s����
	Result Tick() override
	{
		for (const auto& child : m_behaviorNodes)
		{
			// �q�m�[�h�����s����
			Result result = child->Tick();
			if (result != Result::FAILURE)
			{
				// ���s���ʂ�Ԃ�
				return result;
			}
		}
		// ���s��Ԃ�
		return Result::FAILURE;
	}

private:

	// ���O
	std::string m_name;
	// �r�w�C�r�A�m�[�h�z��
	std::vector<IBehaviorNode*> m_behaviorNodes;
};

