// ============================================
// 
// ファイル名: ResultButtonTextUI.h
// 概要: ResultButtonTextUI.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Game/UIObject/UIObject.h"

class Transform;
class CommonResources;
class UIRenderableObject;

class ResultButtonTextUI : public UIObject
{
public:

	enum class TextID
	{
		STAGE_SELECT = 0,
		REPLAY,
	};


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

	// 描画オブジェクトを取得する
	UIRenderableObject* GetUIRenderableObject() const { return m_renderableObject.get(); }

	// ボタンアクティブ設定
	void SetButtonActive(const bool& isButton);

public:

	// コンストラクタ
	ResultButtonTextUI(IObject* root, IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale,
		ResultButtonTextUI::TextID textId);

	// デストラクタ
	~ResultButtonTextUI() override = default;

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

	// ステージセレクトテクスチャの横のサイズ
	static const int STAGE_SELECT_WIDTH;
	static const int REPLAY_WIDTH;
	static const int NEXT_STAGE_WIDTH;
	
	static const int TEXTURE_HEIGHT;

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
	
	// テキストID
	TextID m_textId;

	// Transform
	std::unique_ptr<Transform> m_transform;
	// 描画オブジェクト
	std::unique_ptr<UIRenderableObject> m_renderableObject;

	bool m_isButton;

};