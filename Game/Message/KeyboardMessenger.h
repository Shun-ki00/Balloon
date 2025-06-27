// ============================================
// 
// ファイル名: KeyboardMessenger.h
// 概要: KeyboardMessenger.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IObject.h"

class InputManager;
class IObject;

class KeyboardMessenger
{
public:
	// 観察者をアタッチする
	void Attach(const KeyType& type, const DirectX::Keyboard::Keys& keys, IObject* observer);
	
	// メッセージを送信する
	void Dispatch();

	// アタッチ開始
	void Begin();
	//　アタッチ終了
	void End();

	// 登録してあるものを全て削除
	void Clear();


private:
	//	コンストラクタ
	KeyboardMessenger();
	//	デストラクタ
	~KeyboardMessenger() = default;
public:
	KeyboardMessenger(const KeyboardMessenger&) = delete;             // コピー禁止
	KeyboardMessenger& operator=(const KeyboardMessenger&) = delete;  // コピー代入禁止
	KeyboardMessenger(const KeyboardMessenger&&) = delete;            // ムーブ禁止
	KeyboardMessenger& operator=(const KeyboardMessenger&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static KeyboardMessenger* GetInstance()
	{
		static KeyboardMessenger instance;
		return &instance;
	}

private:

	// アタッチ許可
	bool m_isAttach;

	// キーボード管理者
	InputManager* m_inputManager;

	// キーボード観察者リスト
	std::unordered_map<KeyType,
		std::unordered_multimap<DirectX::Keyboard::Keys, IObject*>> m_keyList;
};