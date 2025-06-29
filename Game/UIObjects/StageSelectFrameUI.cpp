// ============================================
// 
// ファイル名: StageSelectFrameUI.cpp
// 概要: プレイヤーアイコンUIオブジェクト
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/StageSelectFrameUI.h"
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
StageSelectFrameUI::StageSelectFrameUI(IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale, int stageIndex)
	:
	// 基底クラス
	UIObject(),
	m_commonResources{},
	m_isActive(true),
	m_objectNumber(Root::GetInstance()->GetObjectNumber() + UIObject::GetNumber()),
	m_objectID(objectID),
	m_parent(parent),
	m_stageIndex(stageIndex),
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
void StageSelectFrameUI::Initialize()
{
	// テクスチャサイズを取得する
	float width, height;
	Resources::GetInstance()->GetTextureResources()->GetTextureSize(TextureKeyID::StageSelectFrames, width, height);

	// 横に1枚
	float uvScaleX = 1.0f / 1.0f;
	// 縦に3枚
	float uvScaleY = 1.0f / 3.0f;

	// 横に1枚なのでX軸オフセットは常に0
	float uvOffsetX = 0.0f;
	float uvOffsetY = 0.0f;

	// シートを決める
	uvOffsetY = uvScaleY * m_stageIndex;

	UIVertexBuffer vertexBuffer =
	{
		{m_transform->GetLocalPosition().x , m_transform->GetLocalPosition().y ,0.0f ,0.0f},
		{m_transform->GetLocalScale().x ,m_transform->GetLocalScale().y , 0.0f},
		{width , height / 3.0f},
		{uvOffsetX ,uvOffsetY , uvScaleX ,uvScaleY },
		{1.0f ,1.0f ,1.0f ,1.0f },
		{0.0f ,0.0f ,1.0f ,0.0f}
	};

	// 描画オブジェクト作成
	m_renderableObject = std::make_unique<UIRenderableObject>();
	// 初期化
	m_renderableObject->Initialize(vertexBuffer, TextureKeyID::StageSelectFrames, TextureKeyID::Rule, PS_ID::UI_PS);

	// 描画管理者に渡す
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void StageSelectFrameUI::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// Transformの更新処理
	m_transform->Update();

	// 座標を設定
	m_renderableObject->SetPosition(m_transform->GetWorldPosition());
	// 大きさを設定
	m_renderableObject->SetScale({ m_transform->GetWorldScale().x, m_transform->GetWorldScale().y });
	// 回転を適応
	m_renderableObject->SetRotate(DirectX::XMConvertToRadians(m_transform->GetLocalPosition().z));

}

/// <summary>
/// 終了処理
/// </summary>
void StageSelectFrameUI::Finalize() {}


/// <summary>
/// メッセンジャーを通知する
/// </summary>
/// <param name="messageData">メッセージデータ</param>
void StageSelectFrameUI::OnMessegeAccepted(Message::MessageData messageData)
{
	UNREFERENCED_PARAMETER(messageData);
}

/// <summary>
/// キーボードのメッセージを通知する
/// </summary>
/// <param name="type">キータイプ</param>
/// <param name="key">キー</param>
void StageSelectFrameUI::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

