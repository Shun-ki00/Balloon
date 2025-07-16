// ============================================
// 
// �t�@�C����: TimeUI.cpp
// �T�v: �^�C�}�[UI�I�u�W�F�N�g
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/TimeUI.h"
#include "Framework/CommonResources.h"
// ���\�[�X
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
// �����_�����O�I�u�W�F�N�g
#include "Game/RenderableObjects/UIRenderableObject .h"

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
TimeUI::TimeUI(IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale)
	:
	// ���N���X
	UIObject(),
	m_commonResources{},
	m_isActive(true),
	m_objectNumber(Root::GetInstance()->GetObjectNumber() + UIObject::GetNumber()),
	m_objectID(objectID),
	m_parent(parent),
	m_transform{},
	m_renderableObject{},
	m_currentTime{}
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
void TimeUI::Initialize()
{
	// ���Ԃ�������
	m_currentTime = 120.0f;
	// �����̓^�C�}�[���~�߂Ă������b�Z�[�W�Œʒm���󂯎�����ۂɃA�N�e�B�u�ɂ���
	m_isActiveTimer = false;

	// �e�N�X�`���T�C�Y���擾����
	float width, height;
	Resources::GetInstance()->GetTextureResources()->GetTextureSize(TextureKeyID::Numbers, width, height);

	UIVertexBuffer vertexBuffer =
	{
		{m_transform->GetLocalPosition().x , m_transform->GetLocalPosition().y ,0.0f ,0.0f},
		{m_transform->GetLocalScale().x ,m_transform->GetLocalScale().y , 0.0f},
		{width / 4.0f , height},
		{1.0f ,0.0f , 1.0f ,1.0f },
		{1.0f ,1.0f ,1.0f ,1.0f },
		{0.0f ,0.0f ,1.0f ,0.0f}
	};

	// �`��I�u�W�F�N�g�쐬
	m_renderableObject = std::make_unique<UIRenderableObject>();
	// ������
	m_renderableObject->Initialize(vertexBuffer, TextureKeyID::Numbers, TextureKeyID::Rule,PS_ID::NumberUI_PS);

	// �`��Ǘ��҂ɓn��
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void TimeUI::Update(const float& elapsedTime)
{
	// Transform�̍X�V����
	m_transform->Update();

	// ���[���h���W��ݒ�
	m_renderableObject->SetPosition(m_transform->GetWorldPosition());
	// �X�P�[����ݒ�
	m_renderableObject->SetScale({ m_transform->GetWorldScale().x , m_transform->GetWorldScale().y });

	// ���Ԃ��X�V
	if (m_isActiveTimer)
	{
		m_currentTime -= elapsedTime;
		if (m_currentTime <= 0.0f)
		{
			m_currentTime = 0.0f;
			m_isActiveTimer = false;
			SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_GAME_OVER_SCENE);
		}
			

		this->SplitTimeToDigits();
	}
	

	// �`��I�u�W�F�N�g�X�V����
	m_renderableObject->Update(
		m_commonResources->GetDeviceResources()->GetD3DDeviceContext(),
		m_transform->GetWorldMatrix());
}

/// <summary>
/// �I������
/// </summary>
void TimeUI::Finalize() {}


/// <summary>
/// ���b�Z���W���[��ʒm����
/// </summary>
/// <param name="messageData">���b�Z�[�W�f�[�^</param>
void TimeUI::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		case Message::MessageID::START_TIME:
			m_isActiveTimer = true;
		default:
			break;
	}
}

/// <summary>
/// �L�[�{�[�h�̃��b�Z�[�W��ʒm����
/// </summary>
/// <param name="type">�L�[�^�C�v</param>
/// <param name="key">�L�[</param>
void TimeUI::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

void TimeUI::SplitTimeToDigits()
{
	// ���݂̎��Ԃ𐮐��Ŏ擾
	int currentTime = static_cast<int>(m_currentTime);

	int seconds = currentTime % 60;
	int minutes = (currentTime / 60);

	// �e���𕪉�
	float x = static_cast<float>((minutes / 10) % 10); // ���̏\�̈�
	float y = static_cast<float>(minutes % 10);        // ���̈�̈�

	float z = static_cast<float>((seconds / 10) % 10); // �b�̏\�̈�
	float w = static_cast<float>(seconds % 10);		   // �b�̈�̈�

	// Rect��ݒ�
	m_renderableObject->SetUvOffset({ x,y });
	m_renderableObject->SetUvScale({ z,w });
}
