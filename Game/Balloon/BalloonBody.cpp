#include "pch.h"
#include "Game/Balloon/BalloonBody.h"
#include "Framework/CommonResources.h"
#include "Game/Object/Object.h"
#include "Game/RenderableObjects/BalloonRenderableObject.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Game/Buffers.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="angle"></param>
/// <param name="position"></param>
/// <param name="messageID"></param>
BalloonBody::BalloonBody(IObject* root, IObject* parent, IObject::ObjectID objectID,
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
BalloonBody::~BalloonBody()
{

}


/// <summary>
/// 初期化処理
/// </summary>
void BalloonBody::Initialize()
{
	// 当たり判定の初期座標を設定
	m_boundingSphere.Center = { 0.0f , 130.0f , 0.0f };
	// 当たり判定の大きさを設定
	m_boundingSphere.Radius = 0.25f;

	// 初期化処理
	PBRLitConstantBuffer buffer{
		DirectX::SimpleMath::Vector4::One,
		0.0f,
		1.0f,
		1.0f,
		0.0f
	};

	// 描画オブジェクト作成
	m_renderableObject = std::make_unique<BalloonRenderableObject>(true,
		Resources::GetInstance()->GetModelResources()->GetModel(ModelKeyID::BalloonBody));
	// 初期化処理
	dynamic_cast<BalloonRenderableObject*>(m_renderableObject.get())->Initialize(buffer);
	
	// 描画オブジェクトを渡す
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BalloonBody::Update(const float& elapsedTime)
{
	(void)elapsedTime;

	// Transformの更新処理
	m_transform->Update();
	// 描画オブジェクト更新処理
	m_renderableObject->Update(m_commonResources->GetDeviceResources()->GetD3DDeviceContext(), m_transform->GetWorldMatrix());
}

/// <summary>
/// 終了処理
/// </summary>
void BalloonBody::Finalize()
{

}

void BalloonBody::OnMessegeAccepted(Message::MessageData messageData)
{
	(void)messageData;
}

// 通知する
void BalloonBody::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

// 衝突判定を準備する
void BalloonBody::PrepareCollision(ICollisionVisitor* collision)
{
	// 今回プレイヤーのみの当たり判定なので再帰処理は行わない
	collision->PrepareCollision(this, m_boundingSphere);
}

// 衝突判定する
void BalloonBody::DetectCollision(ICollisionVisitor* collision, IObject* object)
{
	UNREFERENCED_PARAMETER(collision);
	UNREFERENCED_PARAMETER(object);
}