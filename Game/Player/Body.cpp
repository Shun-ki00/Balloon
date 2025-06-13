// ============================================
// 
// �t�@�C����: Body.cpp
// �T�v: �v���C���[�A�G�̑̃I�u�W�F�N�g
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/Player/Body.h"
#include "Framework/CommonResources.h"
// ���\�[�X
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
// �����_�����O�I�u�W�F�N�g
#include "Game/RenderableObjects/PlayerRenderableObject.h"
#include "Game/RenderableObjects/EnemyRenderableObject.h"
// �t�@�N�g���[
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/EnemyFactory.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="root">���[�g�I�u�W�F�N�g</param>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <param name="messageID">���b�Z�[�WID</param>
Body::Body(IObject* root, IObject* parent, IObject::ObjectID objectID,
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
	m_transform{},
	m_childs{},
	m_renderableObject{},
	m_velocity{},
	m_heading{},
	m_side{},
	m_acceralation{}
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
/// ����������
/// </summary>
void Body::Initialize()
{
	// �萔�o�b�t�@
	PBRLitConstantBuffer buffer{
		DirectX::SimpleMath::Vector4::One,
		0.1f,
		1.0f,
		1.0f,
		0.0f
	};

	if (m_parent->GetObjectID() == ObjectID::PLAYER)
	{
		// �`��I�u�W�F�N�g�쐬
		m_renderableObject = std::make_unique<PlayerRenderableObject>(true,
			Resources::GetInstance()->GetModelResources()->GetModel(ModelKeyID::Body));
		// ����������
		dynamic_cast<PlayerRenderableObject*>(m_renderableObject.get())->Initialize(buffer);
	}
	else
	{
		// �`��I�u�W�F�N�g�쐬
		m_renderableObject = std::make_unique<EnemyRenderableObject>(true,
			Resources::GetInstance()->GetModelResources()->GetModel(ModelKeyID::Body));
		// ����������
		dynamic_cast<EnemyRenderableObject*>(m_renderableObject.get())->Initialize(buffer);
	}
		
	// �I�u�W�F�N�g�̍쐬
	this->CreateObject();

	// �`��I�u�W�F�N�g��n��
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Body::Update(const float& elapsedTime)
{
	// Transform�̍X�V����
	m_transform->Update();
	// �`��I�u�W�F�N�g�X�V����
	m_renderableObject->Update(m_commonResources->GetDeviceResources()->GetD3DDeviceContext() , m_transform->GetWorldMatrix());

	// �q�I�u�W�F�N�g�̍X�V����
	for (const auto &child : m_childs)
	{
		child->Update(elapsedTime);
	}
}

/// <summary>
/// �I������
/// </summary>
void Body::Finalize() {}

/// <summary>
/// �I�u�W�F�N�g���A�^�b�`����
/// </summary>
/// <param name="object">�I�u�W�F�N�g</param>
void Body::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// �I�u�W�F�N�g���폜����
/// </summary>
/// <param name="object">�폜����I�u�W�F�N�g</param>
void Body::Detach(std::unique_ptr<IObject> object)
{

}

/// <summary>
/// �q�I�u�W�F�N�g���擾����
/// </summary>
/// <returns>�q�I�u�W�F�N�g</returns>
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
/// ���b�Z���W���[��ʒm����
/// </summary>
/// <param name="messageData">���b�Z�[�W�f�[�^</param>
void Body::OnMessegeAccepted(Message::MessageData messageData)
{
	UNREFERENCED_PARAMETER(messageData);
}

/// <summary>
/// �L�[�{�[�h�̃��b�Z�[�W��ʒm����
/// </summary>
/// <param name="type">�L�[�^�C�v</param>
/// <param name="key">�L�[</param>
void Body::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

/// <summary>
/// �I�u�W�F�N�g���쐬����
/// </summary>
void Body::CreateObject()
{
	// �v���C���[�̏ꍇ
	if (m_parent->GetObjectID() == ObjectID::PLAYER)
	{
		// �v���C���[�̓���ǉ�
		this->Attach(PlayerFactory::CreatePlayerHead(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
		// �v���C���[�̓���ǉ�
		this->Attach(PlayerFactory::CreatePlayerLeftArm(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
		// �v���C���[�̓���ǉ�
		this->Attach(PlayerFactory::CreatePlayerLeftFoot(this,
			DirectX::SimpleMath::Vector3::Zero, { 0.0f ,0.0f ,45.0f }, DirectX::SimpleMath::Vector3::One));
		// �v���C���[�̓���ǉ�
		this->Attach(PlayerFactory::CreatePlayerRightArm(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
		// �v���C���[�̓���ǉ�
		this->Attach(PlayerFactory::CreatePlayerRightFoot(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
	}
	else
	{
		// �v���C���[�̓���ǉ�
		this->Attach(EnemyFactory::CreateEnemyHead(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
		// �v���C���[�̓���ǉ�
		this->Attach(EnemyFactory::CreateEnemyLeftArm(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
		// �v���C���[�̓���ǉ�
		this->Attach(EnemyFactory::CreateEnemyLeftFoot(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
		// �v���C���[�̓���ǉ�
		this->Attach(EnemyFactory::CreateEnemyRightArm(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
		// �v���C���[�̓���ǉ�
		this->Attach(EnemyFactory::CreateEnemyRightFoot(this,
			DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
	}
}