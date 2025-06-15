#pragma once
#include "Game/UIObject/UIObject.h"

class Transform;
class CommonResources;
class UIRenderableObject;

class TimeUI : public UIObject
{
public:
	// オブジェクトのアクティブ設定
	void SetIsActive(const bool& isActive) override { m_isActive = isActive; }
	// オブジェクトのアクティブ状態を取得
	bool GetIsActive() const override { return m_isActive; }

	// オブジェクト番号を取得する
	int GetObjectNumber() const  override { return m_objectNumber; }

	// オブジェクトIDを取得する
	IObject::ObjectID GetObjectID() const override { return m_objectID; }
	// Transformを取得する
	Transform* GetTransform() const override { return m_transform.get(); }

	// 親オブジェクトを取得する
	IObject* GetParent() const override { return m_parent; }

public:

	// コンストラクタ
	TimeUI(IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale);

	// デストラクタ
	~TimeUI() override = default;

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

private:

	// 時間を設定する
	void SplitTimeToDigits();

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

	// Transform
	std::unique_ptr<Transform> m_transform;
	// 描画オブジェクト
	std::unique_ptr<UIRenderableObject> m_renderableObject;

	// 現在の時間
	float m_currentTime;

};