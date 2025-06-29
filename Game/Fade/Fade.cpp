// ============================================
// 
// ファイル名: Body.cpp
// 概要: プレイヤー、敵の体オブジェクト
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/Fade/Fade.h"
#include "Framework/CommonResources.h"
#include "Framework/SceneManager.h"
#include "Game/Message/Message.h"
// リソース
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
// レンダリングオブジェクト
#include "Game/RenderableObjects/UIRenderableObject .h"
// ファクトリー
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/EnemyFactory.h"

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
Fade::Fade(IObject* root, IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale)
	:
	// 基底クラス
	UIObject(),
	m_isActive(true),
	m_objectNumber(root->GetObjectNumber() + UIObject::GetNumber()),
	m_objectID(objectID),
	m_parent(parent),
	m_transform{}
{
	// 共有リソースのインスタンスを取得する
	m_commonResources = CommonResources::GetInstance();
	// シーンマネージャーのインスタンスを取得する
	m_sceneManager = SceneManager::GetInstance();

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
void Fade::Initialize()
{
	// 頂点バッファ
	UIVertexBuffer vertexBuffer =
	{
		{1280.0f / 2.0f , 720.0f / 2.0f ,0.0f ,0.0f},
		{1.0f , 1.0f , 0.0f},
		{1280.0f , 720.0f},
		{0.0f ,0.0f , 1.0f ,1.0f },
		{1.0f ,1.0f ,1.0f ,1.0f },
		{1.0f, 1.1f ,0.0f ,0.0f}
	};

	// 描画オブジェクト作成
	m_renderableObject = std::make_unique<UIRenderableObject>();
	// 初期化
	m_renderableObject->Initialize(vertexBuffer, TextureKeyID::FadeMain, TextureKeyID::Rule,PS_ID::UI_PS);

	// 描画管理者に渡す
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Fade::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// ルール画像進行度設定
	m_renderableObject->SetRuleProgress(m_transform->GetLocalScale().z);

	// Transformの更新処理
	m_transform->Update();

	// 描画オブジェクト更新処理
	m_renderableObject->Update(
		m_commonResources->GetDeviceResources()->GetD3DDeviceContext(),
		m_transform->GetWorldMatrix());
}

/// <summary>
/// 終了処理
/// </summary>
void Fade::Finalize() {}


/// <summary>
/// メッセンジャーを通知する
/// </summary>
/// <param name="messageData">メッセージデータ</param>
void Fade::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		case Message::MessageID::FADE_IN :

			// 値の初期化処理
			m_transform->SetLocalScale({ 1.0f ,1.0f ,1.1f });

			// スケールのZ成分をルール画像の進行度を設定
			m_transform->GetTween()->DOScaleZ(0.0f, 1.0f).OnComplete([this] {

				// シーン切り替え
				m_sceneManager->Dispatch(Message::SceneMessageID::MAIN);

				});
			break;
		case Message::MessageID::FADE_OUT:

			// スケールのZ成分をルール画像の進行度を設定
			m_transform->GetTween()->DOScaleZ(1.1f, 1.0f).OnComplete([this] {

				// シーン切り替え
				SceneManager::GetInstance()->ChageScene();

			});

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
void Fade::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

