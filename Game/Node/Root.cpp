#include "pch.h"
#include "Game/Node/Root.h"
#include "Game/Transform/Transform.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">初期座標（原点）</param>
/// <param name="rotation">初期回転</param>
/// <param name="scale">初期スケール</param>
Root::Root(IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale
)
	:
	NodeBase(),
	m_objectID(objectID),
	m_isActive(true)
{
	m_transform = std::make_unique<Transform>();

	// 初期座標設定
	m_transform->SetLocalPosition(position);
	// 初期回転設定
	m_transform->SetLocalRotation(rotation);
	// 初期スケール設定
	m_transform->SetLocalScale(scale);

	// 親がいる場合親を設定
	if (parent != nullptr)
		m_transform->SetParent(parent->GetTransform());
}


/// <summary>
/// 初期化処理
/// </summary>
void Root::Initialize() {}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Root::Update(const float& elapsedTime)
{
	// ノードを更新する
	NodeBase::Update(elapsedTime);
}


/// <summary>
/// 終了処理
/// </summary>
void Root::Finalize()
{
}


/// <summary>
/// アタッチを許可
/// </summary>
void Root::Begin()
{
	// アタッチを許可
	m_isAttach = true;

	// 現在のノードの数を保存
	this->SetNodeNumber();

	// ノード番号をリセット
	NodeBase::ResetNodeCount();

}

/// <summary>
/// アタッチの終了
/// </summary>
void Root::End()
{
	// アタッチ終了
	m_isAttach = false;

	// 保存したノードの数削除
	NodeBase::ResetSceneNode(m_nodeNumber);

	// ノードの数をリセット
	m_nodeNumber = 0;

}

/// <summary>
/// オブジェクトの削除
/// </summary>
void Root::Reset()
{

}


void Root::OnMessegeAccepted(Message::MessageData messageData)
{
	(void)messageData;
}

// 通知する
void Root::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	(void)type;
	(void)key;
}

void Root::Attach(std::unique_ptr<IObject> node)
{
	// ノードを追加する
	NodeBase::Attach(std::move(node));
	// ノード番号を更新
	NodeBase::GetNodeCountAfterCountUp();
}


void Root::Detach(std::unique_ptr<IObject> node)
{
	// 部品を削除する
	NodeBase::Detach(node.get());
}