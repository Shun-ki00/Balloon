// ============================================
// 
// �t�@�C����: Body.cpp
// �T�v: �v���C���[�A�G�̑̃I�u�W�F�N�g
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/Fade/Fade.h"
#include "Framework/CommonResources.h"
#include "Framework/SceneManager.h"
#include "Game/Message/Message.h"
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
Fade::Fade(IObject* root, IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale)
	:
	// ���N���X
	UIObject(),
	m_isActive(true),
	m_objectNumber(root->GetObjectNumber() + UIObject::GetNumber()),
	m_objectID(objectID),
	m_parent(parent),
	m_transform{}
{
	// ���L���\�[�X�̃C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();
	// �V�[���}�l�[�W���[�̃C���X�^���X���擾����
	m_sceneManager = SceneManager::GetInstance();

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
void Fade::Initialize()
{
	// ���_�o�b�t�@
	UIVertexBuffer vertexBuffer =
	{
		{1280.0f / 2.0f , 720.0f / 2.0f ,0.0f ,0.0f},
		{1.0f , 1.0f , 0.0f},
		{1280.0f , 720.0f},
		{0.0f ,0.0f , 1.0f ,1.0f },
		{1.0f ,1.0f ,1.0f ,1.0f },
		{1.0f, 1.1f ,0.0f ,0.0f}
	};

	// �`��I�u�W�F�N�g�쐬
	m_renderableObject = std::make_unique<UIRenderableObject>();
	// ������
	m_renderableObject->Initialize(vertexBuffer, TextureKeyID::FadeMain, TextureKeyID::Rule,PS_ID::UI_PS);

	// �`��Ǘ��҂ɓn��
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Fade::Update(const float& elapsedTime)
{
	// ���[���摜�i�s�x�ݒ�
	m_renderableObject->SetRuleProgress(m_transform->GetLocalScale().z);

	// Transform�̍X�V����
	m_transform->Update();

	// �`��I�u�W�F�N�g�X�V����
	m_renderableObject->Update(
		m_commonResources->GetDeviceResources()->GetD3DDeviceContext(),
		m_transform->GetWorldMatrix());
}

/// <summary>
/// �I������
/// </summary>
void Fade::Finalize() {}


/// <summary>
/// ���b�Z���W���[��ʒm����
/// </summary>
/// <param name="messageData">���b�Z�[�W�f�[�^</param>
void Fade::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		case Message::MessageID::FADE_IN :

			// �l�̏���������
			m_transform->SetLocalScale({ 1.0f ,1.0f ,1.1f });

			// �X�P�[����Z���������[���摜�̐i�s�x��ݒ�
			m_transform->GetTween()->DOScaleZ(0.0f, 1.0f).OnComplete([this] {

				// �V�[���؂�ւ�
				m_sceneManager->Dispatch(Message::SceneMessageID::MAIN);

				});
			break;
		case Message::MessageID::FADE_OUT:

			// �X�P�[����Z���������[���摜�̐i�s�x��ݒ�
			m_transform->GetTween()->DOScaleZ(1.1f, 1.0f).OnComplete([this] {

				// �V�[���؂�ւ�
				SceneManager::GetInstance()->ChageScene();

			});

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
void Fade::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

