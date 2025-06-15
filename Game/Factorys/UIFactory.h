#pragma once
#include "Interface/IObject.h"
#include "Game/UIObjects/ResultButtonTextUI.h"
#include "Game/UIObjects/ResultTextUI.h"

class IObject;

class UIFactory
{
public:

	// ==== static UI�I�u�W�F�N�g ====

	

	// �t�F�[�h�I�u�W�F�N�g
	static std::unique_ptr<IObject> CreateFade(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);
	

	// ==== �^�C�g���V�[�� ====

	// �^�C�g�����S
	static std::unique_ptr<IObject> CreateTitleLogoUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �X�^�[�g�e�L�X�g
	static std::unique_ptr<IObject> CreateStartTextUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);


	// ==== �v���C�V�[�� ====

	// �v���C�V�[���������
	static std::unique_ptr<IObject> CreatePlaySceneKeyGuideUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �J�E���g�_�E��
	static std::unique_ptr<IObject> CreateCountdownUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �^�C�}�[�t���[��
	static std::unique_ptr<IObject> CreateTimerFrameUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �^�C��
	static std::unique_ptr<IObject> CreateTimeUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// ���[�^�@�i�����j
	static std::unique_ptr<IObject> CreateMeterUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �v���C���[�A�C�R��
	static std::unique_ptr<IObject> CreatePlayerIconUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �������[�^
	static std::unique_ptr<IObject> CreateHeightMeterUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);


	// ==== HP �Q�[�W ====

	// HP
	static std::unique_ptr<IObject> CreateHPUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// HP �t���[��
	static std::unique_ptr<IObject> CreateHPFrameUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// HP �Q�[�W
	static std::unique_ptr<IObject> CreateHPGaugeUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);
	

	// ==== ���D�@�傫���Q�[�W ====

	// ���DHP
	static std::unique_ptr<IObject> CreateBalloonHPUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// ���D �t���[��
	static std::unique_ptr<IObject> CreateBalloonFrameUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// ���D �Q�[�W
	static std::unique_ptr<IObject> CreateBalloonGaugeUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);
	

	// ==== ���U���g�V�[�� ====

	// ���U���g�e�L�X�g
	static std::unique_ptr<IObject> CreateResultTextUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale,
		const ResultTextUI::TextID& textId);

	// ���U���g�V�[���̃{�^��
	static std::unique_ptr<IObject> CreateResultButtonText(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale,
		const ResultButtonTextUI::TextID& textId);

	// ���U���g�V�[���̃{�^���V�X�e��
	static std::unique_ptr<IObject> CreateResultSceneButtons(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// ���U���g�V�[���L�[�K�C�h
	static std::unique_ptr<IObject> CreateResultSceneKeyGuideUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

private:
	// ��]�x�N�g�����N�H�[�^�j�I���ɕϊ�����
	static DirectX::SimpleMath::Quaternion ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation);
};