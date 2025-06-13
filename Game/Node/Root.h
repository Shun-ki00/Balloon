#pragma once
#include "Interface/IObject.h"
#include "Game/Node/NodeBase.h"
#include "Interface/IComposite.h"

class Transform;

class Root : public NodeBase, public IComposite
{
public:

	// オブジェクトのアクティブ設定
	void SetIsActive(const bool& isActive) override { m_isActive = isActive; }
	// オブジェクトのアクティブ状態を取得
	bool GetIsActive() const override { return m_isActive; }

	// オブジェクトIDを取得する
	IObject::ObjectID GetObjectID() const override { return m_objectID; }
	// Transformを取得する
	Transform* GetTransform() const override { return m_transform.get(); }

	// 親オブジェクトを取得する
	IObject* GetParent() const override { return nullptr; }

	// ノード番号を取得する
	int GetObjectNumber() const override { return NodeBase::GetNodeCount(); }

	// 現状のノードの数を設定
	void SetNodeNumber() { m_nodeNumber = NodeBase::GetNodeCount(); }
	// ノード番号をリセット
	void ResetNodeNumber() { NodeBase::ResetNodeCount(); }

	// アタッチの許可
	void Begin();
	// アタッチの終了
	void End();

	// オブジェクトの削除
	void Reset();


private:
	// コンストラクタ
	Root(IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale
	);

	//	デストラクタ
	~Root() = default;
public:
	Root(const Root&) = delete;             // コピー禁止
	Root& operator=(const Root&) = delete;  // コピー代入禁止
	Root(const Root&&) = delete;            // ムーブ禁止
	Root& operator=(const Root&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static Root* GetInstance()
	{
		static Root instance(
			nullptr,IObject::ObjectID::NODE_BASE,
			DirectX::SimpleMath::Vector3::Zero,
			DirectX::SimpleMath::Quaternion::Identity,
			DirectX::SimpleMath::Vector3::One
		);
		return &instance;
	}

public:

	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 後処理を行う
	void Finalize() override;

	// オブジェクトをアタッチする
	void Attach(std::unique_ptr<IObject> node) override;
	// オブジェクトを削除する
	void Detach(std::unique_ptr<IObject> node) override;

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageData messageData) override;
	// キーが押下げられたら通知する
	void OnKeyPressed(KeyType type , const DirectX::Keyboard::Keys& key) override;

private:

	// 状態
	bool m_isActive;
	// オブジェクトID
	IObject::ObjectID m_objectID;
	// Transform
	std::unique_ptr<Transform> m_transform;

	// ノードの数
	int m_nodeNumber;

	// アタッチの許可
	bool m_isAttach;

};