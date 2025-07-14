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
/// �R���X�g���N�^
/// </summary>
/// <param name="angle"></param>
/// <param name="position"></param>
/// <param name="messageID"></param>
Balloon::Balloon(IObject* root, IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale,
	const float& colorIndex)
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
	m_colorIndex(colorIndex),
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
		{ 0.0f , 14.0f , 0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.055f,m_colorIndex));
	// ���D�̂Ђ���ǉ�
	this->Attach(BalloonFactory::CreateBalloonRope(this, m_objectID,
		{ 0.0f , 6.0f , 0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.02f));
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Balloon::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

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

/// <summary>
/// �q�I�u�W�F�N�g���擾����
/// </summary>
/// <returns>�q�I�u�W�F�N�g</returns>
std::vector<IObject*> Balloon::GetChilds() const
{
	std::vector<IObject*> result;
	result.reserve(m_childs.size());
	for (const auto& child : m_childs)
	{
		result.push_back(child.get());
	}
	return result;
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

void Balloon::SetBalloonScale(float BalloonScale)
{
	BalloonBody* body = dynamic_cast<BalloonBody*>(m_childs[0].get());
	if (!body) return;

	// �l�� 0.025f ~ 0.055f �Ƀ}�b�s���O
	const float t = std::clamp(BalloonScale, 0.0f, 1.0f);
	const float scale = 0.025f + t * (0.055f - 0.025f);
	const float radius = 0.25f + t * (0.65f - 0.25f);

	// �X�P�[����K�p
	body->GetTransform()->SetLocalScale({ scale, scale, scale });

	// �����蔻�蔼�a��K�p
	body->SetBoundingSphereRadius(radius);

}