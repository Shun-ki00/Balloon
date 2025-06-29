// ============================================
// 
// �t�@�C����: StageSelectTextUI.cpp
// �T�v: �X�^�[�g�����e�L�X�gUI�I�u�W�F�N�g
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/StageSelectTextUI.h"
#include "Framework/CommonResources.h"
// ���\�[�X
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
// �����_�����O�I�u�W�F�N�g
#include "Game/RenderableObjects/UIRenderableObject .h"
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
StageSelectTextUI::StageSelectTextUI(IObject* parent, IObject::ObjectID objectID,
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
void StageSelectTextUI::Initialize()
{
	// �e�N�X�`���T�C�Y���擾����
	float width, height;
	Resources::GetInstance()->GetTextureResources()->GetTextureSize(TextureKeyID::StageSelectTexts, width, height);

	// �������_�o�b�t�@�f�[�^�쐬
	UIVertexBuffer vertexBuffer =
	{
		{1280.0f / 2.0f , 720.0f / 2.0f ,0.0f ,0.0f},
		{m_transform->GetLocalScale().x ,m_transform->GetLocalScale().y , 0.0f},
		{width , height},
		{0.0f ,0.0f , 1.0f ,1.0f },
		{1.0f ,1.0f ,1.0f ,1.0f },
		{0.0f ,0.0f ,1.0f ,0.0f}
	};

	// �`��I�u�W�F�N�g�쐬
	m_renderableObject = std::make_unique<UIRenderableObject>();
	// ������
	m_renderableObject->Initialize(vertexBuffer, TextureKeyID::StageSelectTexts, TextureKeyID::Rule,PS_ID::UI_PS);

	// �`��Ǘ��҂ɓn��
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void StageSelectTextUI::Update(const float& elapsedTime)
{

	UNREFERENCED_PARAMETER(elapsedTime);

	// Transform�̍X�V����
	m_transform->Update();

	// ���_�o�b�t�@�̍X�V
	m_renderableObject->SetPosition(m_transform->GetLocalPosition());
	m_renderableObject->SetScale({ m_transform->GetLocalScale().x ,m_transform->GetLocalScale().y });

	// �`��I�u�W�F�N�g�X�V����
	m_renderableObject->Update(
		m_commonResources->GetDeviceResources()->GetD3DDeviceContext(),
		m_transform->GetWorldMatrix());
}

/// <summary>
/// �I������
/// </summary>
void StageSelectTextUI::Finalize() {}


/// <summary>
/// ���b�Z���W���[��ʒm����
/// </summary>
/// <param name="messageData">���b�Z�[�W�f�[�^</param>
void StageSelectTextUI::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		case Message::MessageID::START_TEXT_ANIMATION:

			// �A�j���[�V�����̐ݒ�Ǝ��s
			m_transform->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One * 0.6f, 0.5f).SetEase(Tween::EasingType::EaseInOutSine).SetDelay(4.0f);

		default:
			break;
	}
}

/// <summary>
/// �L�[�{�[�h�̃��b�Z�[�W��ʒm����
/// </summary>
/// <param name="type">�L�[�^�C�v</param>
/// <param name="key">�L�[</param>
void StageSelectTextUI::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

