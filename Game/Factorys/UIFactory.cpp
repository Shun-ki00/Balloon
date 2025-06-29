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
#include "Game/UIObjects/HeightMeterUI.h"
#include "Game/UIObjects/MeterUI.h"
#include "Game/UIObjects/PlaySceneKeysGuideUI.h"
#include "Game/UIObjects/TimeFrameUI.h"
#include "Game/UIObjects/CountdownUI.h"
#include "Game/UIObjects/TimeUI.h"
#include "Game/UIObjects/StageSelectFrameUI.h"
#include "Game/UIObjects/StageSelectUI.h"
#include "Game/UIObjects/StageSelectTextUI.h"
#include "Game/UIObjects/StageSelectKeyGuideUI.h"


/// <summary>
/// �t�F�[�h�I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�����ʒu</param>
/// <param name="initialRotation">������]</param>
/// <param name="initialScale">�����X�P�[��</param>
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
	ObjectMessenger::GetInstance()->Register(objectID, fade->GetObjectNumber(), fade.get());
	// �C���X�^���X��Ԃ�
	return std::move(fade);
}


/// <summary>
/// �^�C�g�����SUI�̍쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="initialRotation">������]�p</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <returns>�^�C�g�����SUI</returns>
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
	ObjectMessenger::GetInstance()->Register(objectID, titleLogo->GetObjectNumber(), titleLogo.get());
	// �C���X�^���X��Ԃ�
	return std::move(titleLogo);
}


/// <summary>
/// �X�^�[�g�e�L�X�gUI�I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>�X�^�[�g�e�L�X�gUI</returns>
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
	ObjectMessenger::GetInstance()->Register(objectID, startText->GetObjectNumber(), startText.get());
	// �C���X�^���X��Ԃ�
	return std::move(startText);
}


// ===== �X�e�[�W�Z���N�g�V�[�� =====

/// <summary>
/// �X�e�[�W�Z���N�g�t���[��UI�I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="initialRotation">������]�p</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <param name="stageIndex">�X�e�[�W�ԍ�</param>
/// <returns>�X�e�[�W�Z���N�g�t���[��UI�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateStageSelectFrameUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale,int stageIndex)
{
	std::unique_ptr<StageSelectFrameUI> stageSelectFrame = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	stageSelectFrame.reset(new StageSelectFrameUI(parent, objectID, initialPosition, rotation, initialScale, stageIndex));
	// ����������
	stageSelectFrame->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, stageSelectFrame->GetObjectNumber(), stageSelectFrame.get());
	// �C���X�^���X��Ԃ�
	return std::move(stageSelectFrame);
}

/// <summary>
/// �X�e�[�W�Z���N�gUI�e�L�X�g�I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>�X�e�[�W�Z���N�g�e�L�X�gUI</returns>
std::unique_ptr<IObject> UIFactory::CreateStageSelectTextUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<StageSelectTextUI> stageSelectText = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	stageSelectText.reset(new StageSelectTextUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	stageSelectText->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, stageSelectText->GetObjectNumber(), stageSelectText.get());
	// �C���X�^���X��Ԃ�
	return std::move(stageSelectText);
}


/// <summary>
/// �X�e�[�W�Z���N�gUI�I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>�X�e�[�W�Z���N�gUI</returns>
std::unique_ptr<IObject> UIFactory::CreateStageSelectUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<StageSelectUI> stageSelect = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	stageSelect.reset(new StageSelectUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	stageSelect->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, stageSelect->GetObjectNumber(), stageSelect.get());

	// �L�[�{�[�h���b�Z���W���[�ɓo�^
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_DOWN, DirectX::Keyboard::Keys::Left, stageSelect.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_DOWN, DirectX::Keyboard::Keys::Right, stageSelect.get());

	// �C���X�^���X��Ԃ�
	return std::move(stageSelect);
}

/// <summary>
/// �X�e�[�W�Z���N�g�������UI�I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>�X�e�[�W�Z���N�g�������UI</returns>
std::unique_ptr<IObject> UIFactory::CreateStageSelectKeyGuideUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<StageSelectKeyGuideUI> stageSelectKeyGuide = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	stageSelectKeyGuide.reset(new StageSelectKeyGuideUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	stageSelectKeyGuide->Initialize();

	// �C���X�^���X��Ԃ�
	return std::move(stageSelectKeyGuide);
}


// ===== �v���C�V�[�� =====


/// <summary>
/// �v���C�V�[���������UI�I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>�t�F�[�h�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreatePlaySceneKeyGuideUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<PlaySceneKeysGuideUI> playSceneKeysGuide = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	playSceneKeysGuide.reset(new PlaySceneKeysGuideUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	playSceneKeysGuide->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, playSceneKeysGuide->GetObjectNumber(), playSceneKeysGuide.get());
	// �C���X�^���X��Ԃ�
	return std::move(playSceneKeysGuide);
}


/// <summary>
/// �J�E���g�_�E��UI�I�u�W�F�N�g�쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="initialRotation">������]�p</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <returns>�J�E���g�_�E��UI�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateCountdownUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<CountdownUI> countdown = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	countdown.reset(new CountdownUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	countdown->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, countdown->GetObjectNumber(), countdown.get());
	// �C���X�^���X��Ԃ�
	return std::move(countdown);
}


/// <summary>
/// �^�C�}�[�t���[��UI�I�u�W�F�N�g�쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="initialRotation">������]�p</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <returns>�^�C�}�[�t���[��UI�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateTimerFrameUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<TimeFrameUI> timeFrame = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	timeFrame.reset(new TimeFrameUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	timeFrame->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, timeFrame->GetObjectNumber(), timeFrame.get());
	// �C���X�^���X��Ԃ�
	return std::move(timeFrame);
}


/// <summary>
/// �^�C��UI�I�u�W�F�N�g�쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="initialRotation">������]�p</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <returns>�^�C��UI�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateTimeUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<TimeUI> time = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	time.reset(new TimeUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	time->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, time->GetObjectNumber(), time.get());
	// �C���X�^���X��Ԃ�
	return std::move(time);
}


/// <summary>
/// ���[�^�[UI�I�u�W�F�N�g�쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="initialRotation">������]�p</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <returns>���[�^�[UI�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateMeterUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<MeterUI> meter = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	meter.reset(new MeterUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	meter->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, meter->GetObjectNumber(), meter.get());
	// �C���X�^���X��Ԃ�
	return std::move(meter);
}


/// <summary>
/// �v���C���[�A�C�R��UI�I�u�W�F�N�g�쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="initialRotation">������]�p</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <returns>�v���C���[�A�C�R��UI�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreatePlayerIconUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<PLayerIconUI> playerIcon = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	playerIcon.reset(new PLayerIconUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	playerIcon->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, playerIcon->GetObjectNumber(), playerIcon.get());
	// �C���X�^���X��Ԃ�
	return std::move(playerIcon);
}


/// <summary>
/// �������[�^�[UI�I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="initialRotation">������]�p</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <returns>�������[�^�[UI�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateHeightMeterUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<HeightMeterUI> heightMeter = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	heightMeter.reset(new HeightMeterUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	heightMeter->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, heightMeter->GetObjectNumber(), heightMeter.get());
	// �C���X�^���X��Ԃ�
	return std::move(heightMeter);
}



// ==== HP �Q�[�W ====

/// <summary>
/// HPUI�̍쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="initialRotation">������]�p</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <returns>HPUI�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateHPUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<HPUI> hp = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	hp.reset(new HPUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	hp->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, hp->GetObjectNumber(), hp.get());
	// �C���X�^���X��Ԃ�
	return std::move(hp);
}


/// <summary>
/// HP �t���[��UI�I�u�W�F�N�g�쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="initialRotation">������]�p</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <returns>HP �t���[���I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateHPFrameUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<HPFrameUI> hpFrame = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	hpFrame.reset(new HPFrameUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	hpFrame->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, hpFrame->GetObjectNumber(), hpFrame.get());
	// �C���X�^���X��Ԃ�
	return std::move(hpFrame);
}


/// <summary>
/// HP �Q�[�WUI�I�u�W�F�N�g�쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="initialRotation">������]�p</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <returns>HP �Q�[�WUI�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateHPGaugeUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<HPGaugeUI> hpGauge = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	hpGauge.reset(new HPGaugeUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	hpGauge->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, hpGauge->GetObjectNumber(), hpGauge.get());
	// �C���X�^���X��Ԃ�
	return std::move(hpGauge);
}



// ==== ���D�@�傫���Q�[�W ====

/// <summary>
/// ���DHPUI�I�u�W�F�N�g�쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>���DHPUI�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateBalloonHPUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<BalloonHPUI> balloonHp = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	balloonHp.reset(new BalloonHPUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	balloonHp->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, balloonHp->GetObjectNumber(), balloonHp.get());
	// �C���X�^���X��Ԃ�
	return std::move(balloonHp);
}


/// <summary>
///�@���DHP�t���[��UI�I�u�W�F�N�g�쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>���DHP�t���[��UI�I�u�W�F�N�g</returns>
std::unique_ptr<IObject> UIFactory::CreateBalloonFrameUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<BalloonFrameUI> balloonFrame = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	balloonFrame.reset(new BalloonFrameUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	balloonFrame->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, balloonFrame->GetObjectNumber(), balloonFrame.get());
	// �C���X�^���X��Ԃ�
	return std::move(balloonFrame);
}


/// <summary>
/// ���DHP �Q�[�WUI�I�u�W�F�N�g�쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <returns>���DHP �Q�[�WUI�I�u�W�F�N�g�쐬</returns>
std::unique_ptr<IObject> UIFactory::CreateBalloonGaugeUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<BalloonGaugeUI> balloonGauge = nullptr;

	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// �C���X�^���X����
	balloonGauge.reset(new BalloonGaugeUI(parent, objectID, initialPosition, rotation, initialScale));
	// ����������
	balloonGauge->Initialize();
	// ���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(objectID, balloonGauge->GetObjectNumber(), balloonGauge.get());
	// �C���X�^���X��Ԃ�
	return std::move(balloonGauge);
}


// ==== ���U���g�V�[�� ====

/// <summary>
/// ���U���g�V�[���̃e�L�X�gUI�I�u�W�F�N�g�쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="initialRotation">������]�p</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <param name="textId">�e�L�X�gID</param>
/// <returns>���U���g�V�[���̃e�L�X�gUI�I�u�W�F�N�g</returns>
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
	resultButtonText.reset(new ResultButtonTextUI(Root::GetInstance(), parent, objectID, initialPosition, rotation, initialScale, textId));
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
/// ���U���g�V�[���������UI�I�u�W�F�N�g�쐬
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="initialPosition">�������W</param>
/// <param name="initialRotation">������]�p</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <returns>���U���g�V�[���������UI�I�u�W�F�N�g</returns>
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