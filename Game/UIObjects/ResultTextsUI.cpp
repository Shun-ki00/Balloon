// ============================================
// 
// ファイル名: ResultTextUI.cpp
// 概要: リザルトシーンテキストUIオブジェクト
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/ResultTextUI.h"
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
ResultTextUI::ResultTextUI(IObject* root, IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale,
	ResultTextUI::TextID textId)
	:
	// 基底クラス
	UIObject(),
	m_isActive(true),
	m_objectNumber(root->GetObjectNumber() + UIObject::GetNumber()),
	m_objectID(objectID),
	m_textId(textId),
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
void ResultTextUI::Initialize()
{
	// テクスチャサイズを取得する
	float width = 0.0f, height = 0.0f;
	Resources::GetInstance()->GetTextureResources()->GetTextureSize(TextureKeyID::ResultText, width, height);

	// シートは縦に2枚なので高さを二つに割る
	height /= 2.0f;
	
	// 横に1枚
	float uvScaleX = 1.0f / 1.0f; 
	// 縦に2枚
	float uvScaleY = 1.0f / 2.0f;

	// 横に1枚なのでオフセットは常に0
	float uvOffsetX = 0.0f;                      
	float uvOffsetY = 0.0f;           

	// テキストIDをもとにY軸のオフセット値を決める
	switch (m_textId)
	{
		case ResultTextUI::TextID::CLEAR:
			uvOffsetY = uvScaleY * 0;
			break;
		case ResultTextUI::TextID::FAILED:
			uvOffsetY = uvScaleY * 1;
			break;
		default:
			break;
	}
	
	// 初期頂点バッファデータ
	UIVertexBuffer vertexBuffer =
	{
		{m_transform->GetLocalPosition().x , m_transform->GetLocalPosition().y ,
		m_transform->GetLocalPosition().z ,0.0f}, 
		{m_transform->GetLocalScale().x ,m_transform->GetLocalScale().y , 0.0f},						 
		{width , height},							  
		{uvOffsetX ,uvOffsetY , uvScaleX ,uvScaleY }, 
		{1.0f ,1.0f ,1.0f ,1.0f },					  
		{0.0f ,0.0f ,1.0f ,0.0f}					  
	};

	// 描画オブジェクト作成
	m_renderableObject = std::make_unique<UIRenderableObject>();
	// 初期化
	m_renderableObject->Initialize(vertexBuffer, TextureKeyID::ResultText, TextureKeyID::Rule,PS_ID::UI_PS);

	// 描画管理者に渡す
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void ResultTextUI::Update(const float& elapsedTime)
{
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
void ResultTextUI::Finalize() {}


/// <summary>
/// メッセンジャーを通知する
/// </summary>
/// <param name="messageData">メッセージデータ</param>
void ResultTextUI::OnMessegeAccepted(Message::MessageData messageData)
{
	UNREFERENCED_PARAMETER(messageData);
}

/// <summary>
/// キーボードのメッセージを通知する
/// </summary>
/// <param name="type">キータイプ</param>
/// <param name="key">キー</param>
void ResultTextUI::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}



