#pragma once
#include "Interface/IState.h"
#include "Framework/SceneManager.h"

class ObjectMessenger;

class FadeOutState : public IState
{
public:
	// コンストラクタ
	FadeOutState(Message::MessageData data);
	// デストラクタ
	~FadeOutState() = default;
	// 初期化する
	void Initialize() override;
	// 事前更新する
	void PreUpdate() override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 事後更新する
	void PostUpdate() override;
	// 後処理を行う
	void Finalize() override;

public:

	// オブジェクトメッセンジャー
	ObjectMessenger* m_objectMessenger;

	// フェードオブジェクト番号
	int m_fadeObjectNumber;

	// メッセージデータ
	Message::MessageData m_messageData;

};