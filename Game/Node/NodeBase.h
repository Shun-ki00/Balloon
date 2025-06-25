#pragma once
#include "Interface/IObject.h"
#include "Interface/IComposite.h"

class Transform;

class NodeBase : public IObject
{
public:

	// オブジェクトのアクティブ設定
	void SetIsActive(const bool& isActive) override { m_isActive = isActive; }
	// オブジェクトのアクティブ状態を取得
	bool GetIsActive() const override { return m_isActive; }

	// オブジェクトIDを取得する
	IObject::ObjectID GetObjectID() const override { return m_objectID; }
	// Transformを取得する
	Transform* GetTransform() const override { return nullptr; }


public:

	// コンストラクタ
	NodeBase();
	// デストラクタ
	~NodeBase();
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 後処理を行う
	void Finalize() override;

	// オブジェクトをアタッチする
	void Attach(std::unique_ptr<IObject> node);
	// オブジェクトを削除する
	void Detach(IObject* node);

	// シーン単体でノードの削除
	void ResetSceneNode(int nodeCount);

public:
	// ノードカウントのカウントアップ後ノードカウントを取得する(1から開始する)
	static int GetNodeCountAfterCountUp() 
	{
		return s_nodeCount + 1000;
	}
	// ノードカウントを取得する
	static int GetNodeCount() { return s_nodeCount; }
	// ノードカウントをリセットする
	static void ResetNodeCount() { s_nodeCount = 1000; }

private:
	// ノードカウント
	static int s_nodeCount;

	// ノード配列
	std::vector<std::unique_ptr<IObject>> m_nodes;

	// オブジェクトID
	IObject::ObjectID m_objectID;
	// 状態
	bool m_isActive;
};