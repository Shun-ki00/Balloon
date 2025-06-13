#include "pch.h"
#include "Game/Balloon/Balloon.h"
#include "Framework/CommonResources.h"
#include "Game/Object/Object.h"
#include "Game/RenderableObjects/PlayerRenderableObject.h"
#include "Game/RenderableObjects/EnemyRenderableObject.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Game/Buffers.h"
#include "Game/Factorys/BalloonFactory.h"

/// <summary>
/// �R���X�g���N�^
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
Balloon::~Balloon()
{

}


/// <summary>
/// ����������
/// </summary>
void Balloon::Initialize()
{
	// �����蔻��̏������W��ݒ�
	m_boundingSphere.Center = m_transform->GetLocalPosition();
	// �����蔻��̑傫����ݒ�
	m_boundingSphere.Radius = 2.0f;

	// ���D�̖{�̂�ǉ�
	this->Attach(BalloonFactory::CreateBalloonBody(this, m_objectID,
		{ 0.0f , 14.0f , -7.0f }, DirectX::SimpleMath::Vector3::UnitX * -30.0f, DirectX::SimpleMath::Vector3::One * 0.04f));
	// ���D�̂Ђ���ǉ�
	this->Attach(BalloonFactory::CreateBalloonRope(this, m_objectID,
		{ 0.0f , 6.0f , -2.0f }, DirectX::SimpleMath::Vector3::UnitX * -30.0f, DirectX::SimpleMath::Vector3::One * 0.02f));
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Balloon::Update(const float& elapsedTime)
{
	(void)elapsedTime;

	// Transform�̍X�V����
	m_transform->Update();
	// ���[���h���W�𓖂��蔻��̍��W�ɐݒ�
	m_boundingSphere.Center = m_transform->GetWorldPosition();
	
	// �q�I�u�W�F�N�g�̍X�V����
	for (const auto& child : m_childs)
	{
		child->Update(elapsedTime);
	}
}

/// <summary>
/// �I������
/// </summary>
void Balloon::Finalize()
{

}

void Balloon::OnMessegeAccepted(Message::MessageData messageData)
{
	(void)messageData;
}

// �ʒm����
void Balloon::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

/// <summary>
/// �p�[�c��ǉ�����
/// </summary>
/// <param name="object"></param>
void Balloon::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// �p�[�c���폜����
/// </summary>
/// <param name="turretPart"></param>
void Balloon::Detach(std::unique_ptr<IObject> object)
{

}

// �Փ˔������������
void Balloon::PrepareCollision(ICollisionVisitor* collision)
{
	// �{�f�B�̓����蔻����s��
	for (const auto& child : m_childs)
	{
		dynamic_cast<ICollision*>(child.get())->PrepareCollision(collision);
	}
}

// �Փ˔��肷��
void Balloon::DetectCollision(ICollisionVisitor* collision, IObject* object)
{
	UNREFERENCED_PARAMETER(collision);
	UNREFERENCED_PARAMETER(object);
}