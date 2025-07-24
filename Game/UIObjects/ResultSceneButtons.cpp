// ============================================
// 
// �t�@�C����: ResultSceneButtons.cpp
// �T�v: ���U���g�V�[���{�^��UI�I�u�W�F�N�g
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/ResultSceneButtons.h"
#include "Framework/CommonResources.h"
// ���\�[�X
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
// �����_�����O�I�u�W�F�N�g
#include "Game/RenderableObjects/UIRenderableObject .h"

#include "Game/Factorys/UIFactory.h"
#include "Game/UIObjects/ResultButtonTextUI.h"

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
ResultSceneButtons::ResultSceneButtons(IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale)
	:
	// ���N���X
	UIObject(),
	m_commonResources{},
	m_isActive(true),
	m_objectNumber(Root::GetInstance()->GetObjectNumber() + UIObject::CountUpNumber()),
	m_objectID(objectID),
	m_parent(parent),
	m_childs{},
	m_transform{},
	m_buttonIndex{}
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
void ResultSceneButtons::Initialize()
{
	std::unique_ptr<ResultButtonTextUI> uiObject;

	m_buttonIndex = 1;

	// �{�^���I�u�W�F�N�g���쐬����
	for (int i = 0; i < 2; i++)
	{
		this->Attach(UIFactory::CreateResultButtonText(this, ObjectID::RESULT_BUTTON_TEXT,
			{ m_transform->GetLocalPosition().x , m_transform->GetLocalPosition().y + (i * 100.0f) , 0.0f },
			DirectX::SimpleMath::Vector3::Zero,
			m_transform->GetLocalScale(),
			static_cast<ResultButtonTextUI::TextID>(i)));
	}

	// �I�u�W�F�N�g�ԍ����Z�b�g
	UIObject::ResetNumber();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void ResultSceneButtons::Update(const float& elapsedTime)
{
	// Transform�̍X�V����
	m_transform->Update();


	for (int i = 1; i < 3; i++)
	{
		if (m_buttonIndex == i)
		{
			// �{�^�����A�N�e�B�u�ɂ���
			ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::RESULT_BUTTON_TEXT,
				m_objectNumber + i , Message::MessageID::BUTTON_ON);
		}
		else
		{
			// ��A�N�e�B�u�ɂ���
			ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::RESULT_BUTTON_TEXT, 
				m_objectNumber + i , Message::MessageID::BUTTON_OFF);
		}
	}

	// �q�I�u�W�F�N�g�̍X�V����
	for (auto& child : m_childs)
	{
		child->Update(elapsedTime);
	}

}

/// <summary>
/// �I������
/// </summary>
void ResultSceneButtons::Finalize() {}

/// <summary>
/// �I�u�W�F�N�g���A�^�b�`����
/// </summary>
/// <param name="object">�ǉ��I�u�W�F�N�g</param>
void ResultSceneButtons::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// �I�u�W�F�N�g���폜����
/// </summary>
/// <param name="object">�폜����I�u�W�F�N�g</param>
void ResultSceneButtons::Detach(std::unique_ptr<IObject> object)
{

}


/// <summary>
/// ���b�Z���W���[��ʒm����
/// </summary>
/// <param name="messageData">���b�Z�[�W�f�[�^</param>
void ResultSceneButtons::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		case Message::MessageID::CHANGE_SCENE:

			if (m_buttonIndex == 1)
				SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_SELECT_SCEEN);
			else
				SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_PLAY_SCENE);
			break;
		case Message::MessageID::BUTTON_NEXT:
			// �{�^���̔ԍ������Z
			m_buttonIndex--;
			if (m_buttonIndex < 1)
				m_buttonIndex = 2;
			break;
		case Message::MessageID::BUTTON_BACK:
			// �{�^���̔ԍ������Z
			m_buttonIndex++;
			if (m_buttonIndex > 2)
				m_buttonIndex = 1;
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
void ResultSceneButtons::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);

	switch (key)
	{
		case DirectX::Keyboard::Keys::Up:

			// �{�^���̔ԍ������Z
			m_buttonIndex--;
			if (m_buttonIndex < 1)
				m_buttonIndex = 2;

			break;
		case DirectX::Keyboard::Keys::Down:

			// �{�^���̔ԍ������Z
			m_buttonIndex++;
			if (m_buttonIndex > 2)
				m_buttonIndex = 1;

			break;

		default:
			break;
	}

}

