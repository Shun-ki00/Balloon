// ============================================
// 
// ファイル名: ObjectMessenger.h
// 概要: ObjectMessenger.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IObject.h"
#include "Game/Message/Message.h"

class ObjectMessenger
{
public:

	// オブジェクト取得
	IObject* FindObject(const IObject::ObjectID& objectId, const int& objectNumber);
	// オブジェクト取得 可変長配列
	std::vector<IObject*> FindObject(const IObject::ObjectID& objectId);


	// オブジェクトを登録する
	void Register(const IObject::ObjectID& objectId ,const int& objectNumber, IObject* object);

	// メッセージを送信する
	void Dispatch(const IObject::ObjectID& objectId, const int& objectNumber , const Message::MessageData& messageData);
	// メッセージを送信する IDのみ
	void Dispatch(const IObject::ObjectID& objectId, const int& objectNumber,const Message::MessageID& messageID);
	// オブジェクトIDのみでメッセージを送信する
	void Dispatch(const IObject::ObjectID& objectId,const Message::MessageData& messageData);

private:
	//	コンストラクタ
	ObjectMessenger();
	//	デストラクタ
	~ObjectMessenger() = default;
public:
	ObjectMessenger(const ObjectMessenger&) = delete;             // コピー禁止
	ObjectMessenger& operator=(const ObjectMessenger&) = delete;  // コピー代入禁止
	ObjectMessenger(const ObjectMessenger&&) = delete;            // ムーブ禁止
	ObjectMessenger& operator=(const ObjectMessenger&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static ObjectMessenger* GetInstance()
	{
		static ObjectMessenger instance;
		return &instance;
	}

	// アタッチ開始
	void Begin();
	// アタッチ終了
	void End();

	// リストの削除
	void Clear();

private:

	// アタッチ許可
	bool m_isAttach;
	
	// オブジェクトIDをキーにオブジェクト番号とオブジェクトをマッピング
	std::unordered_map<IObject::ObjectID, std::unordered_map<int, IObject*>> m_objects;
};