// ============================================
// 
// �t�@�C����: CountdownUI.cpp
// �T�v: �J�E���g�_�E��UI�I�u�W�F�N�g
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/CountdownUI.h"
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
CountdownUI::CountdownUI(IObject* parent, IObject::ObjectID objectID,
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
void CountdownUI::Initialize()
{
	
	// �e�N�X�`���T�C�Y���擾����
	float width, height;
	Resources::GetInstance()->GetTextureResources()->GetTextureSize(TextureKeyID::ReadyGo, width, height);

	// ����1��
	float uvScaleX = 1.0f / 1.0f;
	// �c��2��
	float uvScaleY = 1.0f / 2.0f;

	// ����1���Ȃ̂ŃI�t�Z�b�g�͏��0
	float uvOffsetX = 0.0f;
	float uvOffsetY = uvScaleY * 0;

	UIVertexBuffer vertexBuffer =
	{
		{m_transform->GetLocalPosition().x , m_transform->GetLocalPosition().y ,0.0f ,0.0f},
		{m_transform->GetLocalScale().x ,m_transform->GetLocalScale().y , 0.0f},
		{width  , height / 2.0f },
		{ uvOffsetX ,uvOffsetY , uvScaleX ,uvScaleY },
		{1.0f ,1.0f ,1.0f ,1.0f },
		{0.0f ,0.0f ,1.0f ,0.0f}
	};

	// �`��I�u�W�F�N�g�쐬
	m_renderableObject = std::make_unique<UIRenderableObject>();
	// ������
	m_renderableObject->Initialize(vertexBuffer, TextureKeyID::ReadyGo , TextureKeyID::Rule , PS_ID::UI_PS);

	// �`��Ǘ��҂ɓn��
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void CountdownUI::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
		
	// Transform�̍X�V����
	m_transform->Update();

	m_transform->SetLocalScale({ m_transform->GetLocalScale().x ,m_transform->GetLocalScale().y , 0.0f });

	// ���W���X�V
	m_renderableObject->SetPosition(m_transform->GetLocalPosition());
	// �傫�����X�V
	m_renderableObject->SetScale({ m_transform->GetLocalScale().x ,m_transform->GetLocalScale().y });
	// ��]���X�V
	m_renderableObject->SetRotate(m_transform->GetLocalScale().z);
	// �F���X�V
	m_renderableObject->SetColor({ 1.0f ,1.0f ,1.0f , m_transform->GetLocalPosition().z });

	// �`��I�u�W�F�N�g�X�V����
	m_renderableObject->Update(
		m_commonResources->GetDeviceResources()->GetD3DDeviceContext(),
		m_transform->GetWorldMatrix());
}

/// <summary>
/// �I������
/// </summary>

void CountdownUI::Finalize() {}


/// <summary>
/// ���b�Z���W���[��ʒm����
/// </summary>
/// <param name="messageData">���b�Z�[�W�f�[�^</param>
void CountdownUI::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		case Message::MessageID::PLAY_COUNTDOWN_ANIMATION:
			this->PlayCoundown();
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
void CountdownUI::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

/// <summary>
/// �J�E���g�_�E�����J�n����
/// </summary>
void CountdownUI::PlayCoundown()
{

	// �uReady�v���E���璆���@�A�j���[�V����
	m_transform->GetTween()->DOMoveX(1280.0f / 2.0f, 1.0f).SetEase(Tween::EasingType::EaseOutBack).OnComplete([this] {

		// �uReady�v�𒆉����獶�@�A�j���[�V����
		m_transform->GetTween()->DOMoveX(-300.0f, 1.0f).SetDelay(0.5f).SetEase(Tween::EasingType::EaseInBack).OnComplete([this] {
			// �I�t�Z�b�g��ύX
			float uvScaleY = (1.0f / 2.0f) * 1.0f;
			m_renderableObject->SetUvOffset({ 0.0f , uvScaleY });

			// �傫�����[���ɂ���
			m_transform->SetLocalScale({ 0.0f ,0.0f ,0.0f });

			// ���W����ʒ��S�ɂ���
			m_transform->SetLocalPosition({ 1280.0f / 2.0f ,720.0f / 2.0f , 1.0f });

			// �uGo�v�𒆉�����傫������@�A�j���[�V����
			m_transform->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One, 1.0f).SetDelay(0.5f).SetEase(Tween::EasingType::EaseOutBounce).OnComplete([this] {
				// �uGo�v��]���Ȃ��珬��������@�A�j���[�V����
				m_transform->GetTween()->DOMoveZ(0.0f, 0.5f).SetDelay(0.5f).OnComplete([this] { 
					SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::PLAY_MAIN_STATE);
					m_isActive = false; });
				});

			});
		});
}

