// ============================================
// 
// ファイル名: ResultTextUI.cpp
// 概要: リザルトシーンテキストUIオブジェクト
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/ResultButtonTextUI.h"
#include "Framework/CommonResources.h"
// リソース
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
// レンダリングオブジェクト
#include "Game/RenderableObjects/UIRenderableObject .h"
// ファクトリー
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/EnemyFactory.h"


const int ResultButtonTextUI::STAGE_SELECT_WIDTH = 828;
const int ResultButtonTextUI::REPLAY_WIDTH       = 828;
const int ResultButtonTextUI::NEXT_STAGE_WIDTH   = 828;

const int ResultButtonTextUI::TEXTURE_HEIGHT = 151;


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
ResultButtonTextUI::ResultButtonTextUI(IObject* root, IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale,
	ResultButtonTextUI::TextID textId)
	:
	// 基底クラス
	UIObject(),
	m_commonResources{},
	m_isActive(true),
	m_objectNumber(root->GetObjectNumber() + UIObject::CountUpNumber()),
	m_objectID(objectID),
	m_textId(textId),
	m_parent(parent),
	m_transform{},
	m_renderableObject{},
	m_isButton{}
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
void ResultButtonTextUI::Initialize()
{
	// テクスチャサイズ
	float width = 0.0f, height = 0.0f;

	// 横に1枚
	float uvScaleX = 1.0f / 1.0f; 
	// 縦に6枚
	float uvScaleY = 1.0f / 6.0f;

	// 横に1枚なのでオフセットは常に0
	float uvOffsetX = 0.0f;                      
	float uvOffsetY = 0.0f;           

	height = static_cast<float>(TEXTURE_HEIGHT);

	switch (m_textId)
	{
		case ResultButtonTextUI::TextID::STAGE_SELECT:
			width = static_cast<float>(STAGE_SELECT_WIDTH);
			uvOffsetY = uvScaleY * 1;
			break;
		case ResultButtonTextUI::TextID::REPLAY:
			width = static_cast<float>(REPLAY_WIDTH);
			uvOffsetY = uvScaleY * 3;
			break;
		default:
			break;
	}



	UIVertexBuffer vertexBuffer =
	{
		{m_transform->GetLocalPosition().x , m_transform->GetLocalPosition().y ,
		m_transform->GetLocalPosition().z ,0.0f}, // 中心座標（スクリーン空間）
		{m_transform->GetLocalScale().x ,m_transform->GetLocalScale().y , 0.0f},						  // rotate.xy = scale、rotate.z = rotation角
		{width , height},							  // テクスチャ表示サイズ（スクリーン座標系）
		{uvOffsetX ,uvOffsetY , uvScaleX ,uvScaleY },  // xy: UV offset, zw: UV scale
		{1.0f ,1.0f ,1.0f ,1.0f },					  // RGBAカラー
		{0.0f ,0.0f ,1.0f ,0.0f}					  // x: useRule, y: ruleProgress, z: inverse, w: reserved
	};

	// 描画オブジェクト作成
	m_renderableObject = std::make_unique<UIRenderableObject>();
	// 初期化
	m_renderableObject->Initialize(vertexBuffer, TextureKeyID::ResultButtonText, TextureKeyID::Rule,PS_ID::UI_PS);

	// 描画管理者に渡す
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void ResultButtonTextUI::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

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
void ResultButtonTextUI::Finalize() {}


/// <summary>
/// メッセンジャーを通知する
/// </summary>
/// <param name="messageData">メッセージデータ</param>
void ResultButtonTextUI::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		case Message::MessageID::BUTTON_ON:
			// ボタンをアクティブにする
			this->SetButtonActive(true);
			break;
		case Message::MessageID::BUTTON_OFF:
			// ボタンを非アクティブにする
			this->SetButtonActive(false);
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
void ResultButtonTextUI::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}


/// <summary>
/// ボタンのアクティブ設定
/// </summary>
/// <param name="isButton">アクティブ</param>
void ResultButtonTextUI::SetButtonActive(const bool& isButton)
{
	// 横に1枚なのでオフセットは常に0
	float uvOffsetX = 0.0f;
	float uvOffsetY = 0.0f;

	float uvScaleY = 1.0f / 6.0f;

	if (isButton)
	{
		switch (m_textId)
		{
			case ResultButtonTextUI::TextID::STAGE_SELECT:
				uvOffsetY = uvScaleY * 0;
				break;
			case ResultButtonTextUI::TextID::REPLAY:
				uvOffsetY = uvScaleY * 2;
				break;
			default:
				break;
		}
	}
	else
	{
		switch (m_textId)
		{
			case ResultButtonTextUI::TextID::STAGE_SELECT:
				uvOffsetY = uvScaleY * 1;
				break;
			case ResultButtonTextUI::TextID::REPLAY:
				uvOffsetY = uvScaleY * 3;
				break;
			default:
				break;
		}
	}

	// UVのオフセットを設定
	m_renderableObject->SetUvOffset({ uvOffsetX, uvOffsetY });
}
