#include "pch.h"
#include "Game/AmbientLight/AmbientLight.h"
#include "Framework/CommonResources.h"
#include "Game/Object/Object.h"
#include "Game/RenderableObjects/PlayerRenderableObject.h"
#include "Game/RenderableObjects/EnemyRenderableObject.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Game/Buffers.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="angle"></param>
/// <param name="position"></param>
/// <param name="messageID"></param>
AmbientLight::AmbientLight()
	:
	// 基底クラス
	Object(
		0.0f,
		0.0f,
		0.0f,
		0.0f
	),
	m_isActive(true),
	m_objectID(IObject::ObjectID::SUN),
	m_parent(nullptr),
	m_transform{}
{
	// 共有リソースのインスタンスを取得する
	m_commonResources = CommonResources::GetInstance();
	m_context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
}


/// <summary>
/// 初期化処理
/// </summary>
void AmbientLight::Initialize()
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// Transformを作成
	m_transform = std::make_unique<Transform>();

	// 初期座標設定
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	// 初期回転設定
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	// 初期スケール設定
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);

	// 親がいる場合親を設定
	if (m_parent != nullptr)
		m_transform->SetParent(m_parent->GetTransform());	

	// 定数バッファオブジェクトの作成
	m_constantBuffer = std::make_unique<ConstantBuffer<AmbientLightParameters>>();
	m_constantBuffer->Initialize(device);

	m_ambientLightData.ambientLightColor = DirectX::SimpleMath::Vector3::One;
	m_ambientLightData.ambientLightIntensity = 0.7f;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void AmbientLight::Update(const float& elapsedTime)
{
	(void)elapsedTime;

	m_constantBuffer->UpdateIfNeeded(m_context, m_ambientLightData);
}

/// <summary>
/// 終了処理
/// </summary>
void AmbientLight::Finalize()
{

}

void AmbientLight::OnMessegeAccepted(Message::MessageData messageData)
{
	(void)messageData;
}


// 通知する
void AmbientLight::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}