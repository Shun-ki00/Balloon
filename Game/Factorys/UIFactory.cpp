#include "pch.h"
#include "Interface/IObject.h"
#include "Game/Message/Message.h"
#include "Game/Factorys/UIFactory.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Message/KeyboardMessenger.h"
// �I�u�W�F�N�g
#include "Game/Node/Root.h"
#include "Game/Fade/Fade.h"
#include "Game/UIObjects/TitleLogoUI.h"
#include "Game/UIObjects/StartTextUI.h"
#include "Game/UIObjects/ResultButtonTextUI.h"
#include "Game/UIObjects/ResultTextUI.h"
#include "Game/UIObjects/ResultSceneKeyGuideUI.h"
#include "Game/UIObjects/ResultSceneButtons.h"
#include "Game/UIObjects/HPUI.h"
#include "Game/UIObjects/HPFrameUI.h"
#include "Game/UIObjects/HPGaugeUI.h"
#include "Game/UIObjects/BalloonHPUI.h"
#include "Game/UIObjects/BalloonFrameUI.h"
#include "Game/UIObjects/BalloonGaugeUI.h"
#include "Game/UIObjects/PLayerIconUI.h"


/// <summary>
/// �t�F�[�h�I�u�W�F�N�g���쐬
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>�t�F�[�h�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateFade(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<Fade> fade = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	fade.reset(new Fade(Root::GetInstance(), parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	fade->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::FADE , fade->GetObjectNumber(), fade.get());
	// �C���X�^���X��Ԃ�
	return std::move(fade);
}


/// <summary>
/// �^�C�g�����SUI�I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>�t�F�[�h�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateTitleLogoUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<TitleLogoUI> titleLogo = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	titleLogo.reset(new TitleLogoUI(Root::GetInstance(), parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	titleLogo->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::TITLE_LOGO_UI, titleLogo->GetObjectNumber(), titleLogo.get());
	// �C���X�^���X��Ԃ�
	return std::move(titleLogo);
}


/// <summary>
/// �v���C���[�A�C�R���̍쐬
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>�t�F�[�h�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreatePlayerIconUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<PLayerIconUI> titleLogo = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	titleLogo.reset(new PLayerIconUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	titleLogo->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::TITLE_LOGO_UI, titleLogo->GetObjectNumber(), titleLogo.get());
	// �C���X�^���X��Ԃ�
	return std::move(titleLogo);
}

/// <summary>
/// �^�C�g�����SUI�I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>�t�F�[�h�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateHeightMeterUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<TitleLogoUI> titleLogo = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	titleLogo.reset(new TitleLogoUI(Root::GetInstance(), parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	titleLogo->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::TITLE_LOGO_UI, titleLogo->GetObjectNumber(), titleLogo.get());
	// �C���X�^���X��Ԃ�
	return std::move(titleLogo);
}


/// <summary>
/// �X�^�[�g�e�L�X�gUI�I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>�t�F�[�h�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateStartTextUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<StartTextUI> startText = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	startText.reset(new StartTextUI(Root::GetInstance(), parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	startText->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::START_TEXT_UI , startText->GetObjectNumber(), startText.get());
	// �C���X�^���X��Ԃ�
	return std::move(startText);
}

/// <summary>
/// ���U���g�V�[���̃e�L�X�g
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="rotation">������]</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <param name="textId">�e�L�X�gID</param>
/// <returns>���U���g�V�[���e�L�X�g�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateResultTextUI(
	IObject* parent, const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale,
	const ResultTextUI::TextID& textId)
{
	std::unique_ptr<ResultTextUI> resultText = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	resultText.reset(new ResultTextUI(Root::GetInstance(), parent, objectID, initialPosition, rotation, initialScale, textId));
	// ����������
	resultText->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, resultText->GetObjectNumber(), resultText.get());
	// �C���X�^���X��Ԃ�
	return std::move(resultText);
}


/// <summary>
/// ���U���g�V�[���̃{�^���e�L�X�g
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="rotation">������]</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <param name="textId">�e�L�X�gID</param>
/// <returns>���U���g�V�[���{�^���e�L�X�g�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateResultButtonText(
	IObject* parent, const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale,
	const ResultButtonTextUI::TextID& textId)
{
	std::unique_ptr<ResultButtonTextUI> resultButtonText = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	resultButtonText.reset(new ResultButtonTextUI(Root::GetInstance(), parent, objectID, initialPosition, rotation, initialScale,textId));
	// ����������
	resultButtonText->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, resultButtonText->GetObjectNumber(), resultButtonText.get());
	// �C���X�^���X��Ԃ�
	return std::move(resultButtonText);
}

/// <summary>
/// ���U���g�V�[���̃{�^���e�L�X�g
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="rotation">������]</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <param name="textId">�e�L�X�gID</param>
/// <returns>���U���g�V�[���{�^���e�L�X�g�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateResultSceneButtons(
	IObject* parent, const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<ResultSceneButtons> resultButtons = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	resultButtons.reset(new ResultSceneButtons(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	resultButtons->Initialize();

	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, resultButtons->GetObjectNumber(), resultButtons.get());

	// �L�[�{�[�h���b�Z���W���[�ɓo�^
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_DOWN, DirectX::Keyboard::Keys::Up, resultButtons.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_DOWN, DirectX::Keyboard::Keys::Down, resultButtons.get());

	// �C���X�^���X��Ԃ�
	return std::move(resultButtons);
}

/// <summary>
/// �X�^�[�g�e�L�X�gUI�I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>�t�F�[�h�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateResultSceneKeyGuideUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<ResultSceneKeyGuideUI> resultSceneKeyGuide = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	resultSceneKeyGuide.reset(new ResultSceneKeyGuideUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	resultSceneKeyGuide->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// �C���X�^���X��Ԃ�
	return std::move(resultSceneKeyGuide);
}


/// <summary>
/// HP�̍쐬
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>�t�F�[�h�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateHPUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<HPUI> resultSceneKeyGuide = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	resultSceneKeyGuide.reset(new HPUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	resultSceneKeyGuide->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// �C���X�^���X��Ԃ�
	return std::move(resultSceneKeyGuide);
}


/// <summary>
/// HP�@�t���[���쐬
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>�t�F�[�h�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateHPFrameUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<HPFrameUI> resultSceneKeyGuide = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	resultSceneKeyGuide.reset(new HPFrameUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	resultSceneKeyGuide->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// �C���X�^���X��Ԃ�
	return std::move(resultSceneKeyGuide);
}



/// <summary>
/// HP�@�Q�[�W�쐬
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>�t�F�[�h�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateHPGaugeUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<HPGaugeUI> resultSceneKeyGuide = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	resultSceneKeyGuide.reset(new HPGaugeUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	resultSceneKeyGuide->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// �C���X�^���X��Ԃ�
	return std::move(resultSceneKeyGuide);
}


/// <summary>
/// ���DHP�쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns> ���DHP</returns>
std::unique_ptr<IObject> UIFactory::CreateBalloonHPUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<BalloonHPUI> resultSceneKeyGuide = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	resultSceneKeyGuide.reset(new BalloonHPUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	resultSceneKeyGuide->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// �C���X�^���X��Ԃ�
	return std::move(resultSceneKeyGuide);
}


/// <summary>
///�@���DHP�t���[���쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>���DHP�t���[��</returns>
std::unique_ptr<IObject> UIFactory::CreateBalloonFrameUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<BalloonFrameUI> resultSceneKeyGuide = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	resultSceneKeyGuide.reset(new BalloonFrameUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	resultSceneKeyGuide->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// �C���X�^���X��Ԃ�
	return std::move(resultSceneKeyGuide);
}



/// <summary>
/// ���DHP�@�Q�[�W�쐬
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>���DHP�@�Q�[�W</returns>
std::unique_ptr<IObject> UIFactory::CreateBalloonGaugeUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<BalloonGaugeUI> resultSceneKeyGuide = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	resultSceneKeyGuide.reset(new BalloonGaugeUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	resultSceneKeyGuide->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// �C���X�^���X��Ԃ�
	return std::move(resultSceneKeyGuide);
}



/// <summary>
/// ��]�x�N�g�����N�H�[�^�j�I���ɕϊ�����B
/// </summary>
/// <param name="rotation">��]��\���x�N�g���i�x���@�j</param>
/// <returns>�ϊ���̃N�H�[�^�j�I��</returns>
DirectX::SimpleMath::Quaternion UIFactory::ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation) {
	return DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(rotation.y),
		DirectX::XMConvertToRadians(rotation.x),
		DirectX::XMConvertToRadians(rotation.z)
	);
}