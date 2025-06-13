#pragma once
#include "Interface/IObject.h"
#include "Interface/IState.h"

class UIObject : public IObject
{
public:
	// オブジェクトをカウントアップする
	static int CountUpNumber();
	// 現在のオブジェクトカウントを取得
	static int ResetNumber();
	// 現在のオブジェクト番号を取得する
	static int GetNumber();

public:

	// コンストラクタ
	UIObject();
	// デストラクタ
	~UIObject() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 後処理を行う
	void Finalize() override;

private:
	// オブジェクト番号
	static int s_objectNumber;
	// 現在のメッセージ
	Message m_currentMessage;
};