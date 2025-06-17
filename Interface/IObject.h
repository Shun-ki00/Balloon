#pragma once
#include "Interface/IObserver.h"
#include "Game/Transform/Transform.h"

class IObject :public IObserver
{
public:
	enum class ObjectID
	{
		NODE_BASE,

		PLAYER,
		PLAYER_BODY,
		PLAYER_HEAD,
		PLAYER_LEFT_ARM,
		PLAYER_LEFT_FOOT,
		PLAYER_RIGHT_ARM,
		PLAYER_RIGHT_FOOT,

		ENEMY,
		ENEMY_BODY,
		ENEMY_HEAD,
		ENEMY_LEFT_ARM,
		ENEMY_LEFT_FOOT,
		ENEMY_RIGHT_ARM,
		ENEMY_RIGHT_FOOT,

		BALLOON,
		BALLOON_BLUE,
		BALLOON_GREEN,
		BALLOON_PINK,
		BALLOON_RED,
		BALLOON_YELLOW,
		BALLOON_PURPLE,

		WOOD_BOX,

		FADE,

		CAMERA_SYSTEM,

		// UI =============================

		TITLE_LOGO_UI,
		PLAYER_ICON_UI,
		METER_UI,
		HEIGHT_METER_UI,
		PLAY_SCENE_KEYS_GUIDE_UI,
		RESULT_SCENE_KEYS_GUIDE_UI,
		RESULT_BUTTON_TEXT,
		RESULT_TEXT_UI,
		SCORE_FRAME_UI,
		STAGE_SELECT_KEYS_GUIDE_UI,
		START_TEXT_UI,
		TIME_FRAME_UI,
		HP_UI,
		HP_FRAME_UI,
		HP_GAUGE_UI,
		BALLOON_HP_UI,
		BALLOON_HP_FRAME_UI,
		BALLOON_HP_GAUGE_UI,
		COUNTDOWN_UI,
		TIME_NUMBER_UI,


		SUN,

		EFFECT_CONTROLLER,
	};

public:
	// �I�u�W�F�N�g�̃A�N�e�B�u�ݒ�
	virtual void SetIsActive(const bool& isActive) = 0;
	// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾
	virtual bool GetIsActive() const = 0;

	// �I�u�W�F�N�g�ԍ����擾����
	virtual int GetObjectNumber() const = 0;

	// �I�u�W�F�N�gID���擾����
	virtual IObject::ObjectID GetObjectID() const = 0;
	// Transform���擾����
	virtual Transform* GetTransform() const = 0;

	// �e�I�u�W�F�N�g���擾����
	virtual IObject* GetParent() const = 0;

public:
	// �R���X�g���N�^
	virtual ~IObject() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;
};

