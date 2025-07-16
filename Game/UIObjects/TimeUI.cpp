// ============================================
// 
// ファイル名: TimeUI.cpp
// 概要: タイマーUIオブジェクト
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/TimeUI.h"
#include "Framework/CommonResources.h"
// リソース
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
// レンダリングオブジェクト
#include "Game/RenderableObjects/UIRenderableObject .h"

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
TimeUI::TimeUI(IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale)
	:
	// 基底クラス
	UIObject(),
	m_commonResources{},
	m_isActive(true),
	m_objectNumber(Root::GetInstance()->GetObjectNumber() + UIObject::GetNumber()),
	m_objectID(objectID),
	m_parent(parent),
	m_transform{},
	m_renderableObject{},
	m_currentTime{}
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
void TimeUI::Initialize()
{
	// 時間を初期化
	m_currentTime = 120.0f;
	// 初期はタイマーを止めておくメッセージで通知を受け取った際にアクティブにする
	m_isActiveTimer = false;

	// テクスチャサイズを取得する
	float width, height;
	Resources::GetInstance()->GetTextureResources()->GetTextureSize(TextureKeyID::Numbers, width, height);

	UIVertexBuffer vertexBuffer =
	{
		{m_transform->GetLocalPosition().x , m_transform->GetLocalPosition().y ,0.0f ,0.0f},
		{m_transform->GetLocalScale().x ,m_transform->GetLocalScale().y , 0.0f},
		{width / 4.0f , height},
		{1.0f ,0.0f , 1.0f ,1.0f },
		{1.0f ,1.0f ,1.0f ,1.0f },
		{0.0f ,0.0f ,1.0f ,0.0f}
	};

	// 描画オブジェクト作成
	m_renderableObject = std::make_unique<UIRenderableObject>();
	// 初期化
	m_renderableObject->Initialize(vertexBuffer, TextureKeyID::Numbers, TextureKeyID::Rule,PS_ID::NumberUI_PS);

	// 描画管理者に渡す
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void TimeUI::Update(const float& elapsedTime)
{
	// Transformの更新処理
	m_transform->Update();

	// ワールド座標を設定
	m_renderableObject->SetPosition(m_transform->GetWorldPosition());
	// スケールを設定
	m_renderableObject->SetScale({ m_transform->GetWorldScale().x , m_transform->GetWorldScale().y });

	// 時間を更新
	if (m_isActiveTimer)
	{
		m_currentTime -= elapsedTime;
		if (m_currentTime <= 0.0f)
		{
			m_currentTime = 0.0f;
			m_isActiveTimer = false;
			SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_GAME_OVER_SCENE);
		}
			

		this->SplitTimeToDigits();
	}
	

	// 描画オブジェクト更新処理
	m_renderableObject->Update(
		m_commonResources->GetDeviceResources()->GetD3DDeviceContext(),
		m_transform->GetWorldMatrix());
}

/// <summary>
/// 終了処理
/// </summary>
void TimeUI::Finalize() {}


/// <summary>
/// メッセンジャーを通知する
/// </summary>
/// <param name="messageData">メッセージデータ</param>
void TimeUI::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		case Message::MessageID::START_TIME:
			m_isActiveTimer = true;
		default:
			break;
	}
}

/// <summary>
/// キーボードのメッセージを通知する
/// </summary>
/// <param name="type">キータイプ</param>
/// <param name="key">キー</param>
void TimeUI::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

void TimeUI::SplitTimeToDigits()
{
	// 現在の時間を整数で取得
	int currentTime = static_cast<int>(m_currentTime);

	int seconds = currentTime % 60;
	int minutes = (currentTime / 60);

	// 各桁を分解
	float x = static_cast<float>((minutes / 10) % 10); // 分の十の位
	float y = static_cast<float>(minutes % 10);        // 分の一の位

	float z = static_cast<float>((seconds / 10) % 10); // 秒の十の位
	float w = static_cast<float>(seconds % 10);		   // 秒の一の位

	// Rectを設定
	m_renderableObject->SetUvOffset({ x,y });
	m_renderableObject->SetUvScale({ z,w });
}
