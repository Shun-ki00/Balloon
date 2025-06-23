#include "pch.h"
#include "Game/Balloon/Balloon.h"
#include "Framework/CommonResources.h"
#include "Game/Object/Object.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Game/Buffers.h"
#include "Game/Factorys/BalloonFactory.h"
#include "Game/Balloon/BalloonBody.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="angle"></param>
/// <param name="position"></param>
/// <param name="messageID"></param>
Balloon::Balloon(IObject* root, IObject* parent, IObject::ObjectID objectID,
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
Balloon::~Balloon()
{

}


/// <summary>
/// 初期化処理
/// </summary>
void Balloon::Initialize()
{
	// 当たり判定の初期座標を設定
	m_boundingSphere.Center = m_transform->GetLocalPosition();
	// 当たり判定の大きさを設定
	m_boundingSphere.Radius = 2.0f;

	// 風船の本体を追加
	this->Attach(BalloonFactory::CreateBalloonBody(this, m_objectID,
		{ 0.0f , 14.0f , 0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.055f));
	// 風船のひもを追加
	this->Attach(BalloonFactory::CreateBalloonRope(this, m_objectID,
		{ 0.0f , 6.0f , 0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.02f));
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Balloon::Update(const float& elapsedTime)
{
	(void)elapsedTime;

	// Transformの更新処理
	m_transform->Update();
	// ワールド座標を当たり判定の座標に設定
	m_boundingSphere.Center = m_transform->GetWorldPosition();
	
	// 子オブジェクトの更新処理
	for (const auto& child : m_childs)
	{
		child->Update(elapsedTime);
	}
}

/// <summary>
/// 終了処理
/// </summary>
void Balloon::Finalize()
{

}

void Balloon::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		case Message::MessageID::BALLOON_SCALE:

			this->SetBalloonScale(messageData.dataFloat);
		
		default:
			break;
	}
}

// 通知する
void Balloon::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

/// <summary>
/// パーツを追加する
/// </summary>
/// <param name="object"></param>
void Balloon::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// パーツを削除する
/// </summary>
/// <param name="turretPart"></param>
void Balloon::Detach(std::unique_ptr<IObject> object)
{

}

// 衝突判定を準備する
void Balloon::PrepareCollision(ICollisionVisitor* collision)
{
	// ボディの当たり判定を行う
	for (const auto& child : m_childs)
	{
		dynamic_cast<ICollision*>(child.get())->PrepareCollision(collision);
	}
}

// 衝突判定する
void Balloon::DetectCollision(ICollisionVisitor* collision, IObject* object)
{
	UNREFERENCED_PARAMETER(collision);
	UNREFERENCED_PARAMETER(object);
}

void Balloon::SetBalloonScale(float BalloonScale)
{
	BalloonBody* body = dynamic_cast<BalloonBody*>(m_childs[0].get());
	if (!body) return;

	// 値を 0.025f ~ 0.055f にマッピング
	const float t = std::clamp(BalloonScale, 0.0f, 1.0f);
	const float scale = 0.025f + t * (0.055f - 0.025f);
	const float radius = 0.25f + t * (0.65f - 0.25f);

	// スケールを適用
	body->GetTransform()->SetLocalScale({ scale, scale, scale });

	// 当たり判定半径を適用
	DirectX::BoundingSphere sphere = body->GetBoundingSphere();
	sphere.Radius = radius;
	body->SetBoundingSphere(sphere);
}