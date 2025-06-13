// ============================================
// 
// ファイル名: LeftArm.cpp
// 概要: プレイヤー、敵の左腕オブジェクト
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/Player/LeftArm.h"
#include "Game/Object/Object.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Game/RenderableObjects/PlayerRenderableObject.h"
#include "Game/RenderableObjects/EnemyRenderableObject.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="angle"></param>
/// <param name="position"></param>
/// <param name="messageID"></param>
LeftArm::LeftArm(IObject* root, IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale,
	Message::MessageID messageID)
	:
	// 基底クラス
	Object(
		0.0f,
		0.0f,
		0.0f,
		0.0f
	),
	m_isActive(true),
	m_objectNumber(root->GetObjectNumber() + Object::CountUpNumber()),
	m_objectID(objectID),
	m_messageID(messageID),
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
/// デストラクタ
/// </summary>
LeftArm::~LeftArm()
{

}


/// <summary>
/// 初期化処理
/// </summary>
void LeftArm::Initialize()
{
	// 当たり判定の初期座標を設定
	m_boundingSphere.Center = m_transform->GetLocalPosition();
	// 当たり判定の大きさを設定
	m_boundingSphere.Radius = 2.0f;

	// 初期化処理
	PBRLitConstantBuffer buffer{
		DirectX::SimpleMath::Vector4::One,
		0.1f,
		1.0f,
		1.0f,
		0.0f
	};

	if (m_objectID == ObjectID::PLAYER_LEFT_ARM)
	{
		// 描画オブジェクト作成
		m_renderableObject = std::make_unique<PlayerRenderableObject>(true,
			Resources::GetInstance()->GetModelResources()->GetModel(ModelKeyID::LeftArm));
		// 初期化処理
		dynamic_cast<PlayerRenderableObject*>(m_renderableObject.get())->Initialize(buffer);
	}
	else
	{
		// 描画オブジェクト作成
		m_renderableObject = std::make_unique<EnemyRenderableObject>(true,
			Resources::GetInstance()->GetModelResources()->GetModel(ModelKeyID::LeftArm));
		// 初期化処理
		dynamic_cast<EnemyRenderableObject*>(m_renderableObject.get())->Initialize(buffer);
	}

	// 描画オブジェクトを渡す
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void LeftArm::Update(const float& elapsedTime)
{
	(void)elapsedTime;

	// Transformの更新処理
	m_transform->Update();
	// ワールド座標を当たり判定の座標に設定
	m_boundingSphere.Center = m_transform->GetWorldPosition();
	// 描画オブジェクト更新処理
	m_renderableObject->Update(m_commonResources->GetDeviceResources()->GetD3DDeviceContext(), m_transform->GetWorldMatrix());
}

/// <summary>
/// 終了処理
/// </summary>
void LeftArm::Finalize()
{

}

void LeftArm::OnMessegeAccepted(Message::MessageData messageData)
{
	(void)messageData;
}

// 通知する
void LeftArm::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}