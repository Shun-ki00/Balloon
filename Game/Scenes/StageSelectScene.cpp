// ============================================
// 
// ファイル名: StageSelectScene.cpp
// 概要: ステージセレクトシーン
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/StageSelectScene.h"
#include "Game/Node/Root.h"
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/EffectFactory.h"
#include "Game/Parameters/Parameters.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Scenes/PlayScene.h"
#include "Game/Factorys/SceneFactory.h"
#include "Game/Scenes/TitleScene.h"
#include "Game/Scenes/GameOverScene.h"
#include "Interface/IState.h"
#include "Game/States/SceneStates/FadeStates/FadeInState.h"
#include "Game/States/SceneStates/FadeStates/FadeOutState.h"
#include "Game/States/SceneStates/StageSelectMainState.h"


/// <summary>
/// コンストラクタ
/// </summary>
StageSelectScene::StageSelectScene()
	:
	m_parameters{},
	m_commonResources{},
	m_currentState{},
	m_fadeInState{},
	m_stageSelectMainState{},
	m_fadeOutState{},
	m_root{}
{
	// インスタンスを取得する
	m_commonResources  = CommonResources::GetInstance();
	m_sceneManager     = SceneManager::GetInstance();
	m_parameters       = Parameters::GetInstance();
	m_root             = Root::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
StageSelectScene::~StageSelectScene() {}


/// <summary>
/// 初期化処理
/// </summary>
void StageSelectScene::Initialize()
{
	// ルートの初期化処理
	m_root->Initialize();

	// オブジェクトの作成
	SceneFactory::CreateStageSelectScene(m_root);

	// ステートの作成
	this->CreateStates();
}

/// <summary>
/// スタート処理
/// </summary>
void StageSelectScene::Start()
{
	// BGMを再生する
	AudioManager::GetInstance()->PlayBgm(XACT_WAVEBANK_SOUNDS::XACT_WAVEBANK_SOUNDS_SELECTSCENE, 1.0f);

	// ステートスタート処理
	m_currentState->PreUpdate();

	// アニメーション開始
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER, { Message::MessageID::PLAYER_ANIMATION });

}

/// <summary>
/// 更新処理する
/// </summary>
void StageSelectScene::Update()
{
	// 経過時間を取得する
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// キーボードメッセンジャー
	KeyboardMessenger::GetInstance()->Dispatch();

	// シーンステートの更新処理
	m_currentState->Update(elapsedTime);

	// ルートの更新処理
	m_root->Update(elapsedTime);
}

/// <summary>
/// 描画処理
/// </summary>
void StageSelectScene::Render()
{
	// 描画処理を行う
	m_commonResources->GetRenderer()->Render();
}

/// <summary>
/// 終了処理
/// </summary>
void StageSelectScene::Finalize() {}

/// <summary>
/// ステートを切り替える
/// </summary>
/// <param name="newState">次のステート</param>
void StageSelectScene::ChangeState(IState* newState)
{
	// 終了処理
	m_currentState->PostUpdate();

	// ステートを切り替える
	m_currentState = newState;

	// スタート処理
	m_currentState->PreUpdate();
}

/// <summary>
/// メッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージデータ</param>
void StageSelectScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::SceneMessageID::FADE_OUT_CANGE_TITLE_SCENE:
			// 次のシーンの準備を行う
			SceneManager::GetInstance()->PrepareScene<TitleScene>();
			// ステートを切り替える
			this->ChangeState(m_fadeOutState.get());
			break;
		case Message::SceneMessageID::FADE_OUT_CANGE_PLAY_SCENE:
			// 次のシーンの準備を行う
			SceneManager::GetInstance()->PrepareScene<PlayScene>();
			// ステートを切り替える
			this->ChangeState(m_fadeOutState.get());
			break;		
		case Message::SceneMessageID::MAIN:
			// ステートを切り替える
			this->ChangeState(m_stageSelectMainState.get());
			break;
		default:
			break;
	}
}


/// <summary>
///	シーンのステートの作成
/// </summary>
void StageSelectScene::CreateStates()
{
	// フェードインステート作成 初期化処理
	m_fadeInState = std::make_unique<FadeInState>(0);
	m_fadeInState->Initialize();

	// ステージセレクトシーンメインステート作成　初期化処理
	m_stageSelectMainState = std::make_unique<StageSelectMainState>();
	m_stageSelectMainState->Initialize();

	// フェードアウトステート作成　初期化処理
	m_fadeOutState = std::make_unique<FadeOutState>(Message::MessageData{ Message::MessageID::FADE_OUT,0,1.0f ,false });
	m_fadeOutState->Initialize();

	// 初期ステートを設定
	m_currentState = m_fadeInState.get();
}