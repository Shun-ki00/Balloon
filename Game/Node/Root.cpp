#include "pch.h"
#include "Game/Node/Root.h"
#include "Game/Transform/Transform.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">�������W�i���_�j</param>
/// <param name="rotation">������]</param>
/// <param name="scale">�����X�P�[��</param>
Root::Root(IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale
)
	:
	NodeBase(),
	m_objectID(objectID),
	m_isActive(true)
{
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
void Root::Initialize() {}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Root::Update(const float& elapsedTime)
{
	// �m�[�h���X�V����
	NodeBase::Update(elapsedTime);
}


/// <summary>
/// �I������
/// </summary>
void Root::Finalize()
{
}


/// <summary>
/// �A�^�b�`������
/// </summary>
void Root::Begin()
{
	// �A�^�b�`������
	m_isAttach = true;

	// ���݂̃m�[�h�̐���ۑ�
	this->SetNodeNumber();

	// �m�[�h�ԍ������Z�b�g
	NodeBase::ResetNodeCount();

}

/// <summary>
/// �A�^�b�`�̏I��
/// </summary>
void Root::End()
{
	// �A�^�b�`�I��
	m_isAttach = false;

	// �ۑ������m�[�h�̐��폜
	NodeBase::ResetSceneNode(m_nodeNumber - 1);

	// �m�[�h�̐������Z�b�g
	m_nodeNumber = 0;

}

/// <summary>
/// �I�u�W�F�N�g�̍폜
/// </summary>
void Root::Reset()
{

}


void Root::OnMessegeAccepted(Message::MessageData messageData)
{
	(void)messageData;
}

// �ʒm����
void Root::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	(void)type;
	(void)key;
}

void Root::Attach(std::unique_ptr<IObject> node)
{
	// �m�[�h��ǉ�����
	NodeBase::Attach(std::move(node));
	// �m�[�h�ԍ����X�V
	NodeBase::GetNodeCountAfterCountUp();
}


void Root::Detach(std::unique_ptr<IObject> node)
{
	// ���i���폜����
	NodeBase::Detach(node.get());
}