// ============================================
// 
// �t�@�C����: PLayerIconUI.cpp
// �T�v: �v���C���[�A�C�R��UI�I�u�W�F�N�g
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/PLayerIconUI.h"
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
PLayerIconUI::PLayerIconUI(IObject* parent, IObject::ObjectID objectID,
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
	m_renderableObject{}
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
void PLayerIconUI::Initialize()
{

	// �e�N�X�`���T�C�Y���擾����
	float width, height;
	Resources::GetInstance()->GetTextureResources()->GetTextureSize(TextureKeyID::PlayerIcon, width, height);

	UIVertexBuffer vertexBuffer =
	{
		{m_transform->GetLocalPosition().x , m_transform->GetLocalPosition().y ,0.0f ,0.0f},
		{m_transform->GetLocalScale().x ,m_transform->GetLocalScale().y , 0.0f},
		{width * 0.3f , height * 0.3f},
		{0.0f ,0.0f , 1.0f ,1.0f },
		{1.0f ,1.0f ,1.0f ,1.0f },
		{0.0f ,0.0f ,1.0f ,0.0f}
	};

	// �`��I�u�W�F�N�g�쐬
	m_renderableObject = std::make_unique<UIRenderableObject>();
	// ������
	m_renderableObject->Initialize(vertexBuffer, TextureKeyID::PlayerIcon, TextureKeyID::Rule,PS_ID::UI_PS);

	// �`��Ǘ��҂ɓn��
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void PLayerIconUI::Update(const float& elapsedTime)
{
	// Transform�̍X�V����
	m_transform->Update();

	// ���[���h���W��ݒ�
	m_renderableObject->SetPosition(m_transform->GetWorldPosition());
	// �X�P�[����ݒ�
	m_renderableObject->SetScale({ m_transform->GetWorldScale().x , m_transform->GetWorldScale().y });
	
	// ��]��ݒ�
	m_renderableObject->SetRotate(DirectX::XMConvertToRadians(m_transform->GetLocalScale().z));

	// �`��I�u�W�F�N�g�X�V����
	m_renderableObject->Update(
		m_commonResources->GetDeviceResources()->GetD3DDeviceContext(),
		m_transform->GetWorldMatrix());
}

/// <summary>
/// �I������
/// </summary>
void PLayerIconUI::Finalize() {}


/// <summary>
/// ���b�Z���W���[��ʒm����
/// </summary>
/// <param name="messageData">���b�Z�[�W�f�[�^</param>
void PLayerIconUI::OnMessegeAccepted(Message::MessageData messageData)
{
	// �v���C���[�̍���
	float playerHeight = 0.0f;

	switch (messageData.messageId)
	{
		case Message::MessageID::PLAYER_HEIGHT:

			// ������ݒ肷��
			playerHeight = messageData.dataFloat;
			playerHeight = std::clamp(playerHeight, -10.0f, 10.0f);

			// UI�̍�����ݒ�
			m_transform->SetLocalPosition({
				m_transform->GetLocalPosition().x,
				-playerHeight * (240.0f / 10.0f),
				m_transform->GetLocalPosition().z
				});
			break;
		default:
			break;

		case Message::MessageID::PLAY_PLAYER_ICON_ANIMATION:
			
			// �A�j���[�V�����J�n
			m_transform->GetTween()->DOScaleZ(-45.0f, 1.5f).SetLoops(10000, Tween::LoopType::Yoyo);
	}
}

/// <summary>
/// �L�[�{�[�h�̃��b�Z�[�W��ʒm����
/// </summary>
/// <param name="type">�L�[�^�C�v</param>
/// <param name="key">�L�[</param>
void PLayerIconUI::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

