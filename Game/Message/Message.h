#pragma once

class Message
{
public:

	// メッセージID
	enum class MessageID : int
	{
		NONE = -1,

		// プレイヤー
		PLAYER_IDLING = 0,
		PLAYER_ATTCK,
		PLAYER_DOWN,
		PLAYER_SKILL,
		EFFECT_NUMBER,
		PLAYER_ANIMATION,

		PLAYER_TITLE_ANIMATION,
		PLAYER_SIT_ANIMATION,
		PLAYER_CLEAR_ANIMATION,

		// 敵
		ENEMY_IDLING,
		ENEMY_WANDER,
		ENEMY_CHASE,
		ENEMY_ATTACK,
		ENEMY_ON_BALLOON_SCALE,
		ENEMY_OFF_BALLOON_SCALE,

		FIXED,
		INVERT_Y_VECTOR,
		BALLOON_LOST,


		// エフェクト
		EXPLOSION,
		ATTACK,
		SMOKE,
		MOVEMENT,
		BALLOON_EXPLOSION,

		// 判定処理
		ON_COLLISION,

		// フェード処理
		FADE_IN,
		FADE_OUT,
		FADE_OUT_EXIT_GAME,

		// タイトルロゴのアニメーション
		TITLE_LOGO_ANIMATION,
		// スタートテキストのアニメーション
		START_TEXT_ANIMATION,

		// ボタンをアクティブ
		BUTTON_ON,
		// ボタンを非アクティブ
		BUTTON_OFF,


		// 風船の大きさを設定
		BALLOON_SCALE,

		// プレイヤーの高さを設定する
		PLAYER_HEIGHT,

		// プレイヤーアイコンアニメーション
		PLAY_PLAYER_ICON_ANIMATION,

		// HPゲージの変更
		HP_GAUGE,

		START_TIME,
		PLAY_COUNTDOWN_ANIMATION,
		CHANGE_SCENE,

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
		FADE_OUT_EXIT_GAME,

		FADE_IN,

		COUNTDOWN,
		MAIN,
		SETTING,
		PLAY_MAIN_STATE,
	};

	// メッセージデータ
	struct MessageData
	{
		Message::MessageID messageId;
		int dataInt = 0;
		float dataFloat = 0.0f;
		bool dataBool = false;
	};

};