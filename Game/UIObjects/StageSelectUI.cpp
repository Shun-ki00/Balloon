// ============================================
// 
// �t�@�C����: StageSelectUI.cpp
// �T�v: �v���C���[�A�C�R��UI�I�u�W�F�N�g
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/StageSelectUI.h"
#include "Framework/CommonResources.h"
// ���\�[�X
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Game/Factorys/UIFactory.h"
#include "Framework/Tween/TweenManager.h"
#include "Game/GameConfig/GameConfig.h"
#include "Game/Parameters/ParameterBuffers.h"


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
StageSelectUI::StageSelectUI(IObject* parent, IObject::ObjectID objectID,
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
	m_stageIndex{},
	m_isCoolTime{},
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
void StageSelectUI::Initialize()
{
	// �X�e�[�W�Z���N�g�t���[�����O�p��
	for (int i = 0; i < 3; i++)
	{
		this->Attach(UIFactory::CreateStageSelectFrameUI(
			this, IObject::ObjectID::STAGE_SELECT_FRAME_UI,
			DirectX::SimpleMath::Vector3::Right * ((i * 600.0f) - 600.0f),
			DirectX::SimpleMath::Vector3::Zero,
			DirectX::SimpleMath::Vector3::One,i
		));
	}

	m_childs[m_stageIndex]->GetTransform()->SetLocalScale(DirectX::SimpleMath::Vector3::One * 1.2f);

	m_isCoolTime = true;
	m_currentTime = 0.5f;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void StageSelectUI::Update(const float& elapsedTime)
{
	// �N�[���^�C���X�V
	if (m_isCoolTime)
	{
		m_currentTime -= elapsedTime;
		if (m_currentTime <= 0.0f)
		{
			m_isCoolTime = false;
			m_currentTime = 0.5f;
		}
			
	}

	GameConfig::GetInstance()->SetParameters<SceneLinkParams>("SceneLinkParams", SceneLinkParams{ m_stageIndex });

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
void StageSelectUI::Finalize() {}


/// <summary>
/// �I�u�W�F�N�g���A�^�b�`����
/// </summary>
/// <param name="object">�ǉ��I�u�W�F�N�g</param>
void StageSelectUI::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// �I�u�W�F�N�g���폜����
/// </summary>
/// <param name="object">�폜����I�u�W�F�N�g</param>
void StageSelectUI::Detach(std::unique_ptr<IObject> object)
{

}


/// <summary>
/// ���b�Z���W���[��ʒm����
/// </summary>
/// <param name="messageData">���b�Z�[�W�f�[�^</param>
void StageSelectUI::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		case Message::MessageID::BUTTON_NEXT:

			m_isCoolTime = true;

			// ���ׂĂ�Tween���~�߂�
			TweenManager::GetInstance()->Stop();

			// ���݂̃t���[��������������
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOMoveZ(0.0f, 0.4f);
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One, 0.4f).SetEase(Tween::EasingType::EaseInBack);

			m_stageIndex--;
			if (m_stageIndex < 0)
				m_stageIndex = 2;

			// ���̃t���[����傫������
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One * 1.2f, 0.4f).SetEase(Tween::EasingType::EaseInOutQuart);
			// ���̃t���[�����傫���Ȃ������]����A�j���[�V�����X�^�[�g
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOMoveZ(10.0f, 0.4f).SetDelay(0.4f).OnComplete([this] {
				m_childs[m_stageIndex]->GetTransform()->GetTween()->DOMoveZ(-10.0f, 0.4f).SetLoops(100000, Tween::LoopType::Yoyo);
				});

			break;
		case Message::MessageID::BUTTON_BACK:

			m_isCoolTime = true;

			// ���ׂĂ�Tween���~�߂�
			TweenManager::GetInstance()->Stop();

			// ���݂̃t���[��������������
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One, 0.4f).SetEase(Tween::EasingType::EaseInBack);
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOMoveZ(0.0f, 0.4f);

			m_stageIndex++;
			if (m_stageIndex > 2)
				m_stageIndex = 0;

			// ���̃t���[����傫������
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One * 1.2f, 0.4f).SetEase(Tween::EasingType::EaseInOutQuart);
			// ���̃t���[�����傫���Ȃ������]����A�j���[�V�����X�^�[�g
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOMoveZ(10.0f, 0.4f).SetDelay(0.4f).OnComplete([this] {
				m_childs[m_stageIndex]->GetTransform()->GetTween()->DOMoveZ(-10.0f, 0.4f).SetLoops(100000, Tween::LoopType::Yoyo);
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
void StageSelectUI::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);

	if (m_isCoolTime) return;

	switch (key)
	{
		case DirectX::Keyboard::Keys::Left:
			break;
		case DirectX::Keyboard::Keys::Right:
			break;
		default:
			break;
	}
}

