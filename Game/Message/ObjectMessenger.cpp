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
	// アタッチ中は送信禁止
	if (m_isAttach) return;

	// 対象オブジェクトを取得して通知
	if (IObject* target = this->FindObject(objectId, objectNumber))
	{
		target->OnMessegeAccepted(messageData);
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
	// アタッチ中は送信禁止
	if (m_isAttach) return;

	this->Dispatch(objectId, objectNumber, Message::MessageData{ messageID });
}
/// <summary>
/// オブジェクトにメッセージを送信する
/// </summary>
/// <param name="objectId">オブジェクトID</param>
/// <param name="messageData">メッセージデータ</param>
void ObjectMessenger::Dispatch(const IObject::ObjectID& objectId, const Message::MessageData& messageData)
{
	// アタッチ中は送信禁止
	if (m_isAttach) return;

	// 対象オブジェクトを取得
	const auto objects = this->FindObject(objectId);

	// 各オブジェクトにメッセージを送信
	for (const auto& object : objects)
	{
		if (object) object->OnMessegeAccepted(messageData);
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
	// 指定されたオブジェクトIDに対応するマップを探す
	const auto idIt = m_objects.find(objectId);
	// 該当するオブジェクトIDが存在しなければ nullptr を返す
	if (idIt == m_objects.end()) return nullptr;
	// オブジェクト番号を使って、該当するオブジェクトを検索する
	const auto objectIt = idIt->second.find(objectNumber);
	// 見つかればポインタを返し、見つからなければ nullptr を返す
	return (objectIt != idIt->second.end()) ? objectIt->second : nullptr;
}

/// <summary>
/// オブジェクトを取得する
/// </summary>
/// <param name="objectId">オブジェクトID</param>
/// <returns>オブジェクト</returns>
std::vector<IObject*> ObjectMessenger::FindObject(const IObject::ObjectID& objectId)
{
	// 検索結果を格納するための配列を用意
	std::vector<IObject*> results = {};

	// 指定されたオブジェクトIDに対応するマップを探す
	const auto idIt = m_objects.find(objectId);
	// グループが存在しない場合は空のリストを返す
	if (idIt == m_objects.end()) return results;

	// 対象のIDに対応するすべてのオブジェクトを走査
	for (const auto& [_, object] : idIt->second)
	{
		// nullptr チェック
		if (object) results.push_back(object); // 有効なオブジェクトのみリストに追加
	}

	// 検索結果を返す
	return results;
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