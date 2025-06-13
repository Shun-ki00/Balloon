#include "pch.h"
#include "Game/Message/ObjectMessenger.h"

ObjectMessenger::ObjectMessenger()
{
	m_isAttach = false;
}


// オブジェクトを登録する
void ObjectMessenger::Register(const IObject::ObjectID& objectId, const int& objectNumber, IObject* object)
{
	// アタッチが許可されてなければ登録を行わない
	if (!m_isAttach) return;

	// オブジェクトIDをもとに番号とオブジェクトを登録する
	m_objects[objectId].emplace(objectNumber, object);
}

// オブジェクトにメッセージを送信する
void ObjectMessenger::Dispatch(const IObject::ObjectID& objectId, const int& objectNumber
	, Message::MessageData messageData)
{
	// アタッチ中の場合メッセージの送信を行わない
	if (m_isAttach) return;
	
	// メッセージを送信するオブジェクトを検索する
	auto typeIt = m_objects.find(objectId);

	// メッセージを送信するオブジェクトが見つかった場合
	if (typeIt != m_objects.end())
	{
		// 個体IDで検索
		auto instanceIt = typeIt->second.find(objectNumber);

		// 個体が見つかった場合はポインタを返す
		if (instanceIt != typeIt->second.end())
		{
			// 送信するオブジェクトのメッセージハンドラを呼び出す
			instanceIt->second->OnMessegeAccepted(messageData);
		}
	}
}

// オブジェクトにメッセージを送信する
void ObjectMessenger::Dispatch(const IObject::ObjectID& objectId, const int& objectNumber
	, Message::MessageID messageID)
{
	// アタッチ中の場合メッセージの送信を行わない
	if (m_isAttach) return;

	Message::MessageData messageData(messageID);

	// メッセージを送信するオブジェクトを検索する
	auto typeIt = m_objects.find(objectId);

	// メッセージを送信するオブジェクトが見つかった場合
	if (typeIt != m_objects.end())
	{
		// 個体IDで検索
		auto instanceIt = typeIt->second.find(objectNumber);

		// 個体が見つかった場合はポインタを返す
		if (instanceIt != typeIt->second.end())
		{
			// 送信するオブジェクトのメッセージハンドラを呼び出す
			instanceIt->second->OnMessegeAccepted(messageData);
		}
	}
}


// オブジェクトを取得する
IObject* ObjectMessenger::FindObject(const IObject::ObjectID& objectId, const int& objectNumber)
{
	// 種類ごとのオブジェクトマップを検索
	auto typeIt = m_objects.find(objectId);

	// 種類が見つかった場合
	if (typeIt != m_objects.end())
	{
		// 個体IDで検索
		auto instanceIt = typeIt->second.find(objectNumber);

		// 個体が見つかった場合はポインタを返す
		if (instanceIt != typeIt->second.end())
		{
			return instanceIt->second;
		}
	}

	// 見つからなかった場合は nullptr を返す
	return nullptr;
}

void ObjectMessenger::Begin()
{
	// アタッチを許可
	m_isAttach = true;
	// リスト削除
	this->Clear();

}

void ObjectMessenger::End()
{
	// アタッチ終了
	m_isAttach = false;
}

void ObjectMessenger::Clear()
{
	m_objects.clear();
}