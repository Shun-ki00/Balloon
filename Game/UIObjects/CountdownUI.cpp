// ============================================
// 
// ファイル名: CountdownUI.cpp
// 概要: タイムフレームUIオブジェクト
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/CountdownUI.h"
#include "Framework/CommonResources.h"
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
CountdownUI::CountdownUI(IObject* parent, IObject::ObjectID objectID,
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
void CountdownUI::Initialize()
{
	
	// テクスチャサイズを取得する
	float width, height;
	Resources::GetInstance()->GetTextureResources()->GetTextureSize(TextureKeyID::ReadyGo, width, height);

	// 横に1枚
	float uvScaleX = 1.0f / 1.0f;
	// 縦に2枚
	float uvScaleY = 1.0f / 2.0f;

	// 横に1枚なのでオフセットは常に0
	float uvOffsetX = 0.0f;
	float uvOffsetY = uvScaleY * 0;

	UIVertexBuffer vertexBuffer =
	{
		{m_transform->GetLocalPosition().x , m_transform->GetLocalPosition().y ,0.0f ,0.0f},
		{m_transform->GetLocalScale().x ,m_transform->GetLocalScale().y , 0.0f},
		{width  , height / 2.0f },
		{ uvOffsetX ,uvOffsetY , uvScaleX ,uvScaleY },
		{1.0f ,1.0f ,1.0f ,1.0f },
		{0.0f ,0.0f ,1.0f ,0.0f}
	};

	// 描画オブジェクト作成
	m_renderableObject = std::make_unique<UIRenderableObject>();
	// 初期化
	m_renderableObject->Initialize(vertexBuffer, TextureKeyID::ReadyGo , TextureKeyID::Rule , PS_ID::UI_PS);

	// 描画管理者に渡す
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void CountdownUI::Update(const float& elapsedTime)
{
	static bool active = false;

	if (!active)
	{
		this->PlayCoundown();
		active = true;
	}
		
	// Transformの更新処理
	m_transform->Update();

	m_transform->SetLocalScale({ m_transform->GetLocalScale().x ,m_transform->GetLocalScale().y , 0.0f });

	// 座標を更新
	m_renderableObject->SetPosition(m_transform->GetLocalPosition());
	// 大きさを更新
	m_renderableObject->SetScale({ m_transform->GetLocalScale().x ,m_transform->GetLocalScale().y });
	// 回転を更新
	m_renderableObject->SetRotate(m_transform->GetLocalScale().z);
	// 色を更新
	m_renderableObject->SetColor({ 1.0f ,1.0f ,1.0f , m_transform->GetLocalPosition().z });

	// 描画オブジェクト更新処理
	m_renderableObject->Update(
		m_commonResources->GetDeviceResources()->GetD3DDeviceContext(),
		m_transform->GetWorldMatrix());
}

/// <summary>
/// 終了処理
/// </summary>

void CountdownUI::Finalize() {}


/// <summary>
/// メッセンジャーを通知する
/// </summary>
/// <param name="messageData">メッセージデータ</param>
void CountdownUI::OnMessegeAccepted(Message::MessageData messageData)
{
	UNREFERENCED_PARAMETER(messageData);
}

/// <summary>
/// キーボードのメッセージを通知する
/// </summary>
/// <param name="type">キータイプ</param>
/// <param name="key">キー</param>
void CountdownUI::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

/// <summary>
/// カウントダウンを開始する
/// </summary>
void CountdownUI::PlayCoundown()
{

	// 「Ready」を右から中央　アニメーション
	m_transform->GetTween()->DOMoveX(1280.0f / 2.0f, 1.0f).SetEase(Tween::EasingType::EaseOutBack).OnComplete([this] {

		// 「Ready」を中央から左　アニメーション
		m_transform->GetTween()->DOMoveX(-300.0f, 1.0f).SetDelay(0.5f).SetEase(Tween::EasingType::EaseInBack).OnComplete([this] {
			// オフセットを変更
			float uvScaleY = (1.0f / 2.0f) * 1.0f;
			m_renderableObject->SetUvOffset({ 0.0f , uvScaleY });

			// 大きさをゼロにする
			m_transform->SetLocalScale({ 0.0f ,0.0f ,0.0f });

			// 座標を画面中心にする
			m_transform->SetLocalPosition({ 1280.0f / 2.0f ,720.0f / 2.0f , 1.0f });

			// 「Go」を中央から大きくする　アニメーション
			m_transform->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One, 1.0f).SetDelay(0.5f).SetEase(Tween::EasingType::EaseOutBounce).OnComplete([this] {
				// 「Go」回転しながら小さくする　アニメーション
				m_transform->GetTween()->DOMoveZ(0.0f, 0.5f).SetDelay(0.5f).OnComplete([this] { m_isActive = false; });
				});

			});
		});
}

