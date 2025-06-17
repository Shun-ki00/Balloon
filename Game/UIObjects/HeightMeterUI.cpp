// ============================================
// 
// ファイル名: HeightMeterUI.cpp
// 概要: リザルトシーンキーガイドUIオブジェクト
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/HeightMeterUI.h"
#include "Framework/CommonResources.h"
// リソース
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
// レンダリングオブジェクト
#include "Game/RenderableObjects/UIRenderableObject .h"
// ファクトリー
#include "Game/Factorys/UIFactory.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="root">ルートオブジェクト</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <param name="messageID">メッセージID</param>
HeightMeterUI::HeightMeterUI(IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale)
	:
	// 基底クラス
	UIObject(),
	m_isActive(true),
	m_objectNumber(Root::GetInstance()->GetObjectNumber() + UIObject::GetNumber()),
	m_objectID(objectID),
	m_parent(parent),
	m_transform{}
{
	// 共有リソースのインスタンスを取得する
	m_commonResources = CommonResources::GetInstance();

	// Transformを作成
	m_transform = std::make_unique<Transform>();

	// 初期座標設定
	m_transform->SetLocalPosition(position);
	// 初期回転設定
	m_transform->SetLocalRotation(rotation);
	// 初期スケール設定
	m_transform->SetLocalScale(scale);

	// 親がいる場合親を設定
	if (parent != nullptr)
		m_transform->SetParent(parent->GetTransform());
}

/// <summary>
/// 初期化処理
/// </summary>
void HeightMeterUI::Initialize()
{

	// 高さ用のメーターを作成
	this->Attach(UIFactory::CreateMeterUI(
		this, IObject::ObjectID::METER_UI,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One
	));
	// プレイヤーアイコンを作成
	this->Attach(UIFactory::CreatePlayerIconUI(
		this, IObject::ObjectID::PLAYER_ICON_UI,
		{60.0f ,0.0f,0.0f},
		DirectX::SimpleMath::Vector3::Zero,
		{0.5f ,0.5f ,45.0f}
	));

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void HeightMeterUI::Update(const float& elapsedTime)
{
	// Transformの更新処理
	m_transform->Update();
	
	// 子オブジェクトの更新処理
	for (const auto& child : m_childs)
	{
		child->Update(elapsedTime);
	}
}

/// <summary>
/// 終了処理
/// </summary>
void HeightMeterUI::Finalize() {}

/// <summary>
/// オブジェクトをアタッチする
/// </summary>
/// <param name="object">追加オブジェクト</param>
void HeightMeterUI::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// オブジェクトを削除する
/// </summary>
/// <param name="object">削除するオブジェクト</param>
void HeightMeterUI::Detach(std::unique_ptr<IObject> object)
{

}



/// <summary>
/// メッセンジャーを通知する
/// </summary>
/// <param name="messageData">メッセージデータ</param>
void HeightMeterUI::OnMessegeAccepted(Message::MessageData messageData)
{
	UNREFERENCED_PARAMETER(messageData);
}

/// <summary>
/// キーボードのメッセージを通知する
/// </summary>
/// <param name="type">キータイプ</param>
/// <param name="key">キー</param>
void HeightMeterUI::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

