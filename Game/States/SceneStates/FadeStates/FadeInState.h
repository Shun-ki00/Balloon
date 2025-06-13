#pragma once
#include "Interface/IState.h"
#include "Game/Message/Message.h"

class ObjectMessenger;
class Message;

class FadeInState : public IState
{
public:
	// コンストラクタ
	FadeInState(int fadeObjectNumber);
	// デストラクタ
	~FadeInState() = default;
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