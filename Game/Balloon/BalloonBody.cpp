#include "pch.h"
#include "Game/Balloon/BalloonBody.h"
#include "Framework/CommonResources.h"
#include "Game/Object/Object.h"
#include "Game/RenderableObjects/BalloonRenderableObject.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Game/Buffers.h"

/// <summary>
/// �R���X�g���N�^
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
	// ���N���X
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
	// ���L���\�[�X�̃C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();

	// Transform���쐬
	m_transform = std::make_unique<Transform>();
	
	// �������W�ݒ�
	m_transform->SetLocalPosition(position);
	// ������]�ݒ�
	m_transform->SetLocalRotation(rotation);
	// �����X�P�[���ݒ�
	m_transform->SetLocalScale(scale);

	// �e������ꍇ�e��ݒ�
	if (parent != nullptr)
		m_transform->SetParent(parent->GetTransform());
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BalloonBody::~BalloonBody()
{

}


/// <summary>
/// ����������
/// </summary>
void BalloonBody::Initialize()
{
	// �����蔻��̏������W��ݒ�
	m_boundingSphere.Center = m_transform->GetLocalPosition();
	// �����蔻��̑傫����ݒ�
	m_boundingSphere.Radius = 2.0f;

	// ����������
	PBRLitConstantBuffer buffer{
		DirectX::SimpleMath::Vector4::One,
		0.2f,
		1.0f,
		5.0f,
		0.0f
	};

	// �`��I�u�W�F�N�g�쐬
	m_renderableObject = std::make_unique<BalloonRenderableObject>(true,
		Resources::GetInstance()->GetModelResources()->GetModel(ModelKeyID::BalloonBody));
	// ����������
	dynamic_cast<BalloonRenderableObject*>(m_renderableObject.get())->Initialize(buffer);
	
	// �`��I�u�W�F�N�g��n��
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BalloonBody::Update(const float& elapsedTime)
{
	(void)elapsedTime;

	// Transform�̍X�V����
	m_transform->Update();
	// ���[���h���W�𓖂��蔻��̍��W�ɐݒ�
	m_boundingSphere.Center = m_transform->GetWorldPosition();
	// �`��I�u�W�F�N�g�X�V����
	m_renderableObject->Update(m_commonResources->GetDeviceResources()->GetD3DDeviceContext(), m_transform->GetWorldMatrix());
}

/// <summary>
/// �I������
/// </summary>
void BalloonBody::Finalize()
{

}

void BalloonBody::OnMessegeAccepted(Message::MessageData messageData)
{
	(void)messageData;
}

// �ʒm����
void BalloonBody::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

// �Փ˔������������
void BalloonBody::PrepareCollision(ICollisionVisitor* collision)
{
	// ����v���C���[�݂̂̓����蔻��Ȃ̂ōċA�����͍s��Ȃ�
	collision->PrepareCollision(this, DirectX::SimpleMath::Vector3::Zero, 0.3f);
}

// �Փ˔��肷��
void BalloonBody::DetectCollision(ICollisionVisitor* collision, IObject* object)
{
	UNREFERENCED_PARAMETER(collision);
	UNREFERENCED_PARAMETER(object);
}