// ============================================
// 
// ファイル名: WoodBox.cpp
// 概要: 木箱オブジェクト
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/WoodBox/WoodBox.h"
#include "Game/Object/Object.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Game/RenderableObjects/WoodBoxRenderableObject.h"
#include "Game/SteeringBehavior/FloatBehavior.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="angle"></param>
/// <param name="position"></param>
/// <param name="messageID"></param>
WoodBox::WoodBox(IObject* root, IObject* parent, IObject::ObjectID objectID,
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

	// オブジェクトのカウントをリセット
	Object::ResetNumber();
}

/// <summary>
/// デストラクタ
/// </summary>
WoodBox::~WoodBox()
{

}


/// <summary>
/// 初期化処理
/// </summary>
void WoodBox::Initialize()
{
	// 当たり判定の初期座標を設定
	m_boundingSphere.Center = m_transform->GetLocalPosition();
	// 当たり判定の大きさを設定
	m_boundingSphere.Radius = 2.0f;

	// 初期化処理
	PBRLitConstantBuffer buffer{
		DirectX::SimpleMath::Vector4::One,
		0.0f,
		1.0f,
		1.0f,
		1.0f
	};

	// 描画オブジェクト作成
	m_renderableObject = std::make_unique<WoodBoxRenderableObject>(true,
		Resources::GetInstance()->GetModelResources()->GetModel(ModelKeyID::WoodBox));
	// 初期化処理
	dynamic_cast<WoodBoxRenderableObject*>(m_renderableObject.get())->Initialize(buffer);

	// 描画オブジェクトを渡す
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());

	// 揺れる処理
	m_floatBehavior = std::make_unique<FloatBehavior>(2.5f,1.0f,0.5f,DirectX::SimpleMath::Vector3::Up);
	m_floatBehavior->On();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void WoodBox::Update(const float& elapsedTime)
{
	(void)elapsedTime;

	m_floatBehavior->On();
	DirectX::SimpleMath::Vector3 acceleration = m_floatBehavior->Calculate();

	// 速度に加速度を加算する
	m_velocity += acceleration * elapsedTime;
	// 現在の位置を更新する
	m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);

	m_velocity = m_velocity * (1.0f - 2.0f * elapsedTime);

	// Transformの更新のみ行う
	m_transform->Update();

	// ワールド座標を当たり判定の座標に設定
	m_boundingSphere.Center = m_transform->GetWorldPosition();
	// 描画オブジェクト更新処理
	m_renderableObject->Update(m_commonResources->GetDeviceResources()->GetD3DDeviceContext(), m_transform->GetWorldMatrix());
}

/// <summary>
/// 終了処理
/// </summary>
void WoodBox::Finalize()
{
}

void WoodBox::OnMessegeAccepted(Message::MessageData messageData)
{
	UNREFERENCED_PARAMETER(messageData);
}

// 通知する
void WoodBox::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}