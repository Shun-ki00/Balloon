// ============================================
// 
// ファイル名: ObjectMessenger.cpp
// 概要: オブジェクトのメッセンジャー（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/Message/ObjectMessenger.h"

/// <summary>
/// コンストラクタ
/// </summary>
ObjectMessenger::ObjectMessenger()
	:
	m_objects{},
	m_isAttach{}
{
	m_isAttach = false;
}


/// <summary>
/// オブジェクトを登録する
/// </summary>
/// <param name="objectId">オブジェクトID</param>
/// <param name="objectNumber">オブジェクト番号</param>
/// <param name="object">オブジェクト</param>
void ObjectMessenger::Register(const IObject::ObjectID& objectId, const int& objectNumber, IObject* object)
{
	// アタッチが許可されてなければ登録を行わない
	if (!m_isAttach) return;

	// オブジェクトIDをもとに番号とオブジェクトを登録する
	m_objects[objectId].emplace(objectNumber, object);
}



/// <summary>
/// オブジェクトにメッセージを送信する
/// </summary>
/// <param name="objectId">オブジェクトID</param>
/// <param name="objectNumber">オブジェクト番号</param>
/// <param name="messageData">メッセージデータ</param>
void ObjectMessenger::Dispatch(const IObject::ObjectID& objectId, const int& objectNumber, const Message::MessageData& messageData)
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
/// <summary>
/// オブジェクトにメッセージを送信する
/// </summary>
/// <param name="objectId">オブジェクトID</param>
/// <param name="objectNumber">オブジェクト番号</param>
/// <param name="messageID">メッセージID</param>
void ObjectMessenger::Dispatch(const IObject::ObjectID& objectId, const int& objectNumber, const Message::MessageID& messageID)
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
/// <summary>
/// オブジェクトにメッセージを送信する
/// </summary>
/// <param name="objectId">オブジェクトID</param>
/// <param name="messageData">メッセージデータ</param>
void ObjectMessenger::Dispatch(const IObject::ObjectID& objectId, const Message::MessageData& messageData)
{
	// メッセージを送信するオブジェクトを検索する
	auto typeIt = m_objects.find(objectId);

	// メッセージを送信するオブジェクトが見つかった場合
	if (typeIt != m_objects.end())
	{
		for (const auto it : typeIt->second)
		{
			// 送信するオブジェクトのメッセージハンドラを呼び出す
			it.second->OnMessegeAccepted(messageData);
		}
	}
}


/// <summary>
/// オブジェクトを取得する
/// </summary>
/// <param name="objectId">オブジェクトID</param>
/// <param name="objectNumber">オブジェクト番号</param>
/// <returns>オブジェクト</returns>
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

/// <summary>
/// オブジェクトを取得する
/// </summary>
/// <param name="objectId">オブジェクトID</param>
/// <returns>オブジェクト</returns>
std::vector<IObject*> ObjectMessenger::FindObject(const IObject::ObjectID& objectId)
{
	std::vector<IObject*> objects;

	// オブジェクトIDに対応するマップが存在するか確認
	auto typeIt = m_objects.find(objectId);
	if (typeIt != m_objects.end());

	// 対象のオブジェクトを配列に詰めて返す
	for (const auto& [objectNumber, object] : typeIt->second)
	{
		if (object->GetObjectID() == objectId)
			objects.push_back(object);
	}

	return objects;
}

/// <summary>
/// アタッチを許可
/// </summary>
void ObjectMessenger::Begin()
{
	// アタッチを許可
	m_isAttach = true;
	// リスト削除
	this->Clear();

}

/// <summary>
/// アタッチ終了
/// </summary>
void ObjectMessenger::End()
{
	// アタッチ終了
	m_isAttach = false;
}


/// <summary>
/// 登録してあるものを削除
/// </summary>
void ObjectMessenger::Clear()
{
	m_objects.clear();
}