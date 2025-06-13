#include "pch.h"
#include "Game/Node/NodeBase.h"

// �I�u�W�F�N�g�ԍ�
int NodeBase::s_nodeCount = 0;


// �R���X�g���N�^
NodeBase::NodeBase()		
{
}

// �f�X�g���N�^
NodeBase::~NodeBase()
{
}

// ����������
void NodeBase::Initialize()
{
}

// �X�V����
void NodeBase::Update(const float& elapsedTime)
{
	// �m�[�h���X�V����
	for (auto& node : m_nodes)
	{
		node->Update(elapsedTime);
	}
}


// �㏈�����s��
void NodeBase::Finalize()
{
}

void NodeBase::Attach(std::unique_ptr<IObject> node)
{
	// �m�[�h��ǉ�����
	m_nodes.emplace_back(std::move(node));
}



void NodeBase::Detach(IObject* node)
{
	// �폜����m�[�h��������
	auto it = std::find_if(m_nodes.begin(), m_nodes.end(),
		[&](const std::unique_ptr<IObject>& node_part)
		{
			return node_part.get() == node;
		}
	);
	// �폜���镔�i�����������ꍇ�̓m�[�h���폜����
	if (it != m_nodes.end())
	{
		m_nodes.erase(it);
	}
}


void NodeBase::ResetSceneNode(int nodeCount)
{
	// �m�[�h�̐����擪����폜����
	for (int i = 0; i < nodeCount; i++)
	{
		// �m�[�h���폜����
		m_nodes.erase(m_nodes.begin());
	}
}