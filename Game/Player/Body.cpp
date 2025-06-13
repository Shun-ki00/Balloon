// ============================================
// 
// ファイル名: Body.cpp
// 概要: プレイヤー、敵の体オブジェクト
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/Player/Body.h"
#include "Framework/CommonResources.h"
// リソース
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
// レンダリングオブジェクト
#include "Game/RenderableObjects/PlayerRenderableObject.h"
#include "Game/RenderableObjects/EnemyRenderableObject.h"
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
Body::Body(IObject* root, IObject* parent, IObject::ObjectID objectID,
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
	m_transform{},
	m_childs{},
	m_renderableObject{},
	m_velocity{},
	m_heading{},
	m_side{},
	m_acceralation{}
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
void Body::Initialize()
{
	// 定数バッファ
	PBRLitConstantBuffer buffer{
		DirectX::SimpleMath::Vector4::One,
		0.1f,
		1.0f,
		1.0f,
		0.0f
	};

	if (m_parent->GetObjectID() == ObjectID::PLAYER)
	{
		// 描画オブジェクト作成
		m_renderableObject = std::make_unique<PlayerRenderableObject>(true,
			Resources::GetInstance()->GetModelResources()->GetModel(ModelKeyID::Body));
		// 初期化処理
		dynamic_cast<PlayerRenderableObject*>(m_renderableObject.get())->Initialize(buffer);
	}
	else
	{
		// 描画オブジェクト作成
		m_renderableObject = std::make_unique<EnemyRenderableObject>(true,
			Resources::GetInstance()->GetModelResources()->GetModel(ModelKeyID::Body));
		// 初期化処理
		dynamic_cast<EnemyRenderableObject*>(m_renderableObject.get())->Initialize(buffer);
	}
		
	// オブジェクトの作成
	this->CreateObject();

	// 描画オブジェクトを渡す
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Body::Update(const float& elapsedTime)
{
	// Transformの更新処理
	m_transform->Update();
	// 描画オブジェクト更新処理
	m_renderableObject->Update(m_commonResources->GetDeviceResources()->GetD3DDeviceContext() , m_transform->GetWorldMatrix());

	// 子オブジェクトの更新処理
	for (const auto &child : m_childs)
	{
		child->Update(elapsedTime);
	}
}

/// <summary>
/// 終了処理
/// </summary>
void Body::Finalize() {}

/// <summary>
/// オブジェクトをアタッチする
/// </summary>
/// <param name="object">オブジェクト</param>
void Body::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// オブジェクトを削除する
/// </summary>
/// <param name="object">削除するオブジェクト</param>
void Body::Detach(std::unique_ptr<IObject> object)
{

}

/// <summary>
/// 子オブジェクトを取得する
/// </summary>
/// <returns>子オブジェクト</returns>
std::vector<IObject*> Body::GetChilds() const
{
	std::vector<IObject*> result;
	result.reserve(m_childs.size());
	for (const auto& child : m_childs)
	{
		result.push_back(child.get());
	}
	return result;
}

/// <summary>
/// メッセンジャーを通知する
/// </summary>
/// <param name="messageData">メッセージデータ</param>
void Body::OnMessegeAccepted(Message::MessageData messageData)
{
	UNREFERENCED_PARAMETER(messageData);
}

/// <summary>
/// キーボードのメッセージを通知する
/// </summary>
/// <param name="type">キータイプ</param>
/// <param name="key">キー</param>
void Body::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

/// <summary>
/// オブジェクトを作成する
/// </summary>
void Body::CreateObject()
{
	// プレイヤーの場合
	if (m_parent->GetObjectID() == ObjectID::PLAYER)
	{
		// プレイヤーの頭を追加
		this->Attach(PlayerFactory::CreatePlayerHead(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
		// プレイヤーの頭を追加
		this->Attach(PlayerFactory::CreatePlayerLeftArm(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
		// プレイヤーの頭を追加
		this->Attach(PlayerFactory::CreatePlayerLeftFoot(this,
			DirectX::SimpleMath::Vector3::Zero, { 0.0f ,0.0f ,45.0f }, DirectX::SimpleMath::Vector3::One));
		// プレイヤーの頭を追加
		this->Attach(PlayerFactory::CreatePlayerRightArm(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
		// プレイヤーの頭を追加
		this->Attach(PlayerFactory::CreatePlayerRightFoot(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
	}
	else
	{
		// プレイヤーの頭を追加
		this->Attach(EnemyFactory::CreateEnemyHead(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
		// プレイヤーの頭を追加
		this->Attach(EnemyFactory::CreateEnemyLeftArm(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
		// プレイヤーの頭を追加
		this->Attach(EnemyFactory::CreateEnemyLeftFoot(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
		// プレイヤーの頭を追加
		this->Attach(EnemyFactory::CreateEnemyRightArm(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
		// プレイヤーの頭を追加
		this->Attach(EnemyFactory::CreateEnemyRightFoot(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
	}
}