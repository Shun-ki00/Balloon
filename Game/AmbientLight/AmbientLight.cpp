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
/// �R���X�g���N�^
/// </summary>
/// <param name="angle"></param>
/// <param name="position"></param>
/// <param name="messageID"></param>
AmbientLight::AmbientLight()
	:
	// ���N���X
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
	// ���L���\�[�X�̃C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();
	m_context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
}


/// <summary>
/// ����������
/// </summary>
void AmbientLight::Initialize()
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// Transform���쐬
	m_transform = std::make_unique<Transform>();

	// �������W�ݒ�
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	// ������]�ݒ�
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	// �����X�P�[���ݒ�
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);

	// �e������ꍇ�e��ݒ�
	if (m_parent != nullptr)
		m_transform->SetParent(m_parent->GetTransform());	

	// �萔�o�b�t�@�I�u�W�F�N�g�̍쐬
	m_constantBuffer = std::make_unique<ConstantBuffer<AmbientLightParameters>>();
	m_constantBuffer->Initialize(device);

	m_ambientLightData.ambientLightColor = DirectX::SimpleMath::Vector3::One;
	m_ambientLightData.ambientLightIntensity = 0.7f;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void AmbientLight::Update(const float& elapsedTime)
{
	(void)elapsedTime;

	m_constantBuffer->UpdateIfNeeded(m_context, m_ambientLightData);
}

/// <summary>
/// �I������
/// </summary>
void AmbientLight::Finalize()
{

}

void AmbientLight::OnMessegeAccepted(Message::MessageData messageData)
{
	(void)messageData;
}


// �ʒm����
void AmbientLight::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}