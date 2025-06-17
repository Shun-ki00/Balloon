// ============================================
// 
// �t�@�C����: HealthGaugeUI.cpp
// �T�v: HPUI�I�u�W�F�N�g
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/BalloonHPUI.h"
#include "Framework/CommonResources.h"
// ���\�[�X
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
// �����_�����O�I�u�W�F�N�g
#include "Game/RenderableObjects/UIRenderableObject .h"
#include "Game/Factorys/UIFactory.h"

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
BalloonHPUI::BalloonHPUI(IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale)
	:
	// ���N���X
	UIObject(),
	m_isActive(true),
	m_objectNumber(Root::GetInstance()->GetObjectNumber() + UIObject::GetNumber()),
	m_objectID(objectID),
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
/// ����������
/// </summary>
void BalloonHPUI::Initialize()
{

	// �o�[�̍쐬
	this->Attach(UIFactory::CreateBalloonGaugeUI(
		this, ObjectID::BALLOON_HP_GAUGE_UI,
		{ 0.0f , -70.0f ,0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.5f
	));

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BalloonHPUI::Update(const float& elapsedTime)
{
	// Transform�̍X�V����
	m_transform->Update();

	// �q�I�u�W�F�N�g�̍X�V����
	for (const auto& child : m_childs)
	{
		child->Update(elapsedTime);
	}
}

/// <summary>
/// �I������
/// </summary>
void BalloonHPUI::Finalize() {}


/// <summary>
/// �I�u�W�F�N�g���A�^�b�`����
/// </summary>
/// <param name="object">�ǉ��I�u�W�F�N�g</param>
void BalloonHPUI::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// �I�u�W�F�N�g���폜����
/// </summary>
/// <param name="object">�폜����I�u�W�F�N�g</param>
void BalloonHPUI::Detach(std::unique_ptr<IObject> object)
{

}


/// <summary>
/// ���b�Z���W���[��ʒm����
/// </summary>
/// <param name="messageData">���b�Z�[�W�f�[�^</param>
void BalloonHPUI::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		case Message::MessageID::BALLOON_SCALE:

			// ���D�̑傫����ݒ肷��
			m_transform->SetLocalScale({ 0.1f + (0.6f - 0.1f) * messageData.dataFloat , 0.1f + (0.6f - 0.1f) * messageData.dataFloat , 0.0f});

			break;
		default:
			break;
	}
}

/// <summary>
/// �L�[�{�[�h�̃��b�Z�[�W��ʒm����
/// </summary>
/// <param name="type">�L�[�^�C�v</param>
/// <param name="key">�L�[</param>
void BalloonHPUI::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

