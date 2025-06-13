#include "pch.h"
#include "Game/Node/NodeBase.h"

// オブジェクト番号
int NodeBase::s_nodeCount = 0;


// コンストラクタ
NodeBase::NodeBase()		
{
}

// デストラクタ
NodeBase::~NodeBase()
{
}

// 初期化する
void NodeBase::Initialize()
{
}

// 更新する
void NodeBase::Update(const float& elapsedTime)
{
	// ノードを更新する
	for (auto& node : m_nodes)
	{
		node->Update(elapsedTime);
	}
}


// 後処理を行う
void NodeBase::Finalize()
{
}

void NodeBase::Attach(std::unique_ptr<IObject> node)
{
	// ノードを追加する
	m_nodes.emplace_back(std::move(node));
}



void NodeBase::Detach(IObject* node)
{
	// 削除するノードを見つける
	auto it = std::find_if(m_nodes.begin(), m_nodes.end(),
		[&](const std::unique_ptr<IObject>& node_part)
		{
			return node_part.get() == node;
		}
	);
	// 削除する部品が見つかった場合はノードを削除する
	if (it != m_nodes.end())
	{
		m_nodes.erase(it);
	}
}


void NodeBase::ResetSceneNode(int nodeCount)
{
	// ノードの数分先頭から削除する
	for (int i = 0; i < nodeCount; i++)
	{
		// ノードを削除する
		m_nodes.erase(m_nodes.begin());
	}
}