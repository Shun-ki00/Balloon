// ============================================
// 
// ファイル名: Body.h
// 概要: Body.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Game/Object/Object.h"
#include "Interface/IComposite.h"

class Transform;
class IRenderableObject;
class CommonResources;

class Body : public Object , IComposite
{
public:

	// オブジェクトのアクティブ設定
	void SetIsActive(const bool& isActive) { m_isActive = isActive; }
	// オブジェクトのアクティブ状態を取得
	bool GetIsActive() const { return m_isActive; }

	// オブジェクト番号を取得する
	int GetObjectNumber() const  override { return m_objectNumber; }

	// オブジェクトIDを取得する
	IObject::ObjectID GetObjectID() const override { return m_objectID; }
	// Transformを取得する
	Transform* GetTransform() const override { return m_transform.get(); }

	// 親オブジェクトを取得する
	IObject* GetParent() const override { return m_parent; }
	// 子オブジェクトを取得する
	std::vector<IObject*> GetChilds() const;

	// 速度を取得する
	DirectX::SimpleMath::Vector3& GetVelocity() override { return m_velocity; }
	// 速度を設定する
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) override { m_velocity = velocity; }
	// 加速度を取得する
	DirectX::SimpleMath::Vector3& GetAcceralation() override { return m_acceralation; }
	// 加速度を設定する
	void SetAcceralation(const DirectX::SimpleMath::Vector3& accelaration) override { m_acceralation = accelaration; }

	// コンストラクタ
	Body(IObject* root,  IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale,
		Message::MessageID messageID);

	// デストラクタ
	~Body() override = default;

	// 初期化する
	void Initialize() override;
	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageData messageData) override;
	// キーが押下げられたら通知する
	void OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key) override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 後処理を行う
	void Finalize() override;

	// オブジェクトをアタッチする
	void Attach(std::unique_ptr<IObject> object) override;
	// オブジェクトを削除する
	void Detach(std::unique_ptr<IObject> object) override;

private:

	// オブジェクト作成
	void CreateObject();
	
private:

	// 共有リソース
	CommonResources* m_commonResources;

	// アクティブ状態
	bool m_isActive;
	// オブジェクト番号
	int m_objectNumber;
	// オブジェクトID
	IObject::ObjectID m_objectID;
	// 親オブジェクト
	IObject* m_parent;
	// 子オブジェクト
	std::vector<std::unique_ptr<IObject>> m_childs;

	// メッセージID
	Message::MessageID m_messageID;
	// Transform
	std::unique_ptr<Transform> m_transform;
	// 描画オブジェクト
	std::unique_ptr<IRenderableObject> m_renderableObject;

	// プレイヤーの速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// 方向
	DirectX::SimpleMath::Vector3 m_heading;
	// 直横
	DirectX::SimpleMath::Vector3 m_side;
	// プレイヤーの加速度
	DirectX::SimpleMath::Vector3 m_acceralation;
};