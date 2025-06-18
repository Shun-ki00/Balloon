#pragma once

class Message
{
public:

	

	// ���b�Z�[�WID
	enum class MessageID : int
	{
		NONE = -1,

		// �v���C���[
		PLAYER_IDLING = 0,
		PLAYER_ATTCK,
		PLAYER_DOWN,
		PLAYER_SKILL,
		EFFECT_NUMBER,

		// �G�t�F�N�g
		EXPLOSION,
		ATTACK,
		SMOKE,
		MOVEMENT,
		BALLOON_EXPLOSION,

		// ���菈��
		ON_COLLISION,

		// �t�F�[�h����
		FADE_IN,
		FADE_OUT,

		// �^�C�g�����S�̃A�j���[�V����
		TITLE_LOGO_ANIMATION,
		// �X�^�[�g�e�L�X�g�̃A�j���[�V����
		START_TEXT_ANIMATION,

		// �{�^�����A�N�e�B�u
		BUTTON_ON,
		// �{�^�����A�N�e�B�u
		BUTTON_OFF,


		// ���D�̑傫����ݒ�
		BALLOON_SCALE,

		// �v���C���[�̍�����ݒ肷��
		PLAYER_HEIGHT,

		// �v���C���[�A�C�R���A�j���[�V����
		PLAY_PLAYER_ICON_ANIMATION,

		// HP�Q�[�W�̕ύX
		HP_GAUGE,



	};


	enum class SceneMessageID : int
	{
		FADE_OUT,
		FADE_OUT_CANGE_TITLE_SCENE,
		FADE_OUT_CANGE_MENU_SCENE,
		FADE_OUT_CANGE_SELECT_SCEEN,
		FADE_OUT_CANGE_PLAY_SCENE,
		FADE_OUT_CANGE_GAME_CLEAR_SCENE,
		FADE_OUT_CANGE_GAME_OVER_SCENE,

		FADE_IN,

		COUNTDOWN,
		MAIN,
		SETTING,
	};

	struct MessageData
	{
		Message::MessageID messageId;
		int dataInt = 0;
		float dataFloat = 0.0f;
		bool dataBool = false;
	};

};