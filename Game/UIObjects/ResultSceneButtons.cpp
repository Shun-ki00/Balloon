// ============================================
// 
// ファイル名: ResultSceneButtons.cpp
// 概要: リザルトシーンボタンUIオブジェクト
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/ResultSceneButtons.h"
#include "Framework/CommonResources.h"
// リソース
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
// レンダリングオブジェクト
#include "Game/RenderableObjects/UIRenderableObject .h"

#include "Game/Factorys/UIFactory.h"
#include "Game/UIObjects/ResultButtonTextUI.h"

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
ResultSceneButtons::ResultSceneButtons(IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale)
	:
	// 基底クラス
	UIObject(),
	m_commonResources{},
	m_isActive(true),
	m_objectNumber(Root::GetInstance()->GetObjectNumber() + UIObject::CountUpNumber()),
	m_objectID(objectID),
	m_parent(parent),
	m_childs{},
	m_transform{},
	m_buttonIndex{}
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
void ResultSceneButtons::Initialize()
{
	std::unique_ptr<ResultButtonTextUI> uiObject;

	m_buttonIndex = 1;

	// ボタンオブジェクトを二つ作成する
	for (int i = 0; i < 2; i++)
	{
		this->Attach(UIFactory::CreateResultButtonText(this, ObjectID::RESULT_BUTTON_TEXT,
			{ m_transform->GetLocalPosition().x , m_transform->GetLocalPosition().y + (i * 100.0f) , 0.0f },
			DirectX::SimpleMath::Vector3::Zero,
			m_transform->GetLocalScale(),
			static_cast<ResultButtonTextUI::TextID>(i)));
	}

	// オブジェクト番号リセット
	UIObject::ResetNumber();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void ResultSceneButtons::Update(const float& elapsedTime)
{
	// Transformの更新処理
	m_transform->Update();


	for (int i = 1; i < 3; i++)
	{
		if (m_buttonIndex == i)
		{
			// ボタンをアクティブにする
			ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::RESULT_BUTTON_TEXT,
				m_objectNumber + i , Message::MessageID::BUTTON_ON);
		}
		else
		{
			// 非アクティブにする
			ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::RESULT_BUTTON_TEXT, 
				m_objectNumber + i , Message::MessageID::BUTTON_OFF);
		}
	}

	// 子オブジェクトの更新処理
	for (auto& child : m_childs)
	{
		child->Update(elapsedTime);
	}

}

/// <summary>
/// 終了処理
/// </summary>
void ResultSceneButtons::Finalize() {}

/// <summary>
/// オブジェクトをアタッチする
/// </summary>
/// <param name="object">追加オブジェクト</param>
void ResultSceneButtons::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// オブジェクトを削除する
/// </summary>
/// <param name="object">削除するオブジェクト</param>
void ResultSceneButtons::Detach(std::unique_ptr<IObject> object)
{

}


/// <summary>
/// メッセンジャーを通知する
/// </summary>
/// <param name="messageData">メッセージデータ</param>
void ResultSceneButtons::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		case Message::MessageID::CHANGE_SCENE:

			if (m_buttonIndex == 1)
				SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_SELECT_SCEEN);
			else
				SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_PLAY_SCENE);
			break;
		case Message::MessageID::BUTTON_NEXT:
			// ボタンの番号を減算
			m_buttonIndex--;
			if (m_buttonIndex < 1)
				m_buttonIndex = 2;
			break;
		case Message::MessageID::BUTTON_BACK:
			// ボタンの番号を加算
			m_buttonIndex++;
			if (m_buttonIndex > 2)
				m_buttonIndex = 1;
			break;
		default:
			break;
	}
}

/// <summary>
/// キーボードのメッセージを通知する
/// </summary>
/// <param name="type">キータイプ</param>
/// <param name="key">キー</param>
void ResultSceneButtons::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);

	switch (key)
	{
		case DirectX::Keyboard::Keys::Up:

			// ボタンの番号を減算
			m_buttonIndex--;
			if (m_buttonIndex < 1)
				m_buttonIndex = 2;

			break;
		case DirectX::Keyboard::Keys::Down:

			// ボタンの番号を加算
			m_buttonIndex++;
			if (m_buttonIndex > 2)
				m_buttonIndex = 1;

			break;

		default:
			break;
	}

}

