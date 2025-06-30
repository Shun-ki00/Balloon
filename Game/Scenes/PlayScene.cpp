// ============================================
// 
// ファイル名: DebugScene.cpp
// 概要: デバッグ用のシーン
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/PlayScene.h"
#include "Interface/IObject.h"
#include "Interface/IScene.h"
#include "Game/Cameras/DebugCamera.h"
#include "Game/Node/Root.h"
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/EnemyFactory.h"
#include "Game/Message/KeyboardMessenger.h"
#include "Game/Parameters/Parameters.h"
#include "Game/SteeringBehavior/WindBehavior.h"
#include "Game/AmbientLight/AmbientLight.h"
#include "Game/Particle/ParticleEmitter.h"
#include "Game/Factorys/EffectFactory.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/States/SceneStates/FadeStates/FadeInState.h"
#include "Game/States/SceneStates/FadeStates/FadeOutState.h"
#include "Game/States/SceneStates/PlayMainState.h"
#include "Game/States/SceneStates/CountdownState.h"
#include "Game/Scenes/GameClearScene.h"
#include "Game/Scenes/GameOverScene.h"

#include "Game/Factorys/SceneFactory.h"


PlayScene::PlayScene()
{
	m_commonResources  = CommonResources::GetInstance();
	m_parameters       = Parameters::GetInstance();
	m_root             = Root::GetInstance();
}


PlayScene::~PlayScene()
{

}

void PlayScene::Initialize()
{
	// デバッグカメラ
	m_debugCamera = std::make_unique<DebugCamera>();
	m_debugCamera->Initialize(1280, 720);

	m_root->Initialize();

	// オブジェクトを作成する
	SceneFactory::CreatePlayScene(m_root);

	// シーンのステート作成
	this->CreateState();
}

void PlayScene::Start()
{
	m_currentState->PreUpdate();

	// アニメーション開始
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER_ICON_UI, { Message::MessageID::PLAY_PLAYER_ICON_ANIMATION });
}

void PlayScene::Update()
{
	const float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// 通知を行う
	KeyboardMessenger::GetInstance()->Dispatch();

	// カメラを更新
	m_debugCamera->Update();
	m_commonResources->SetViewMatrix(m_debugCamera->GetViewMatrix());
	m_commonResources->SetCameraTransform(m_debugCamera->GetTransform());

	m_root->Update(elapsedTime);
}

void PlayScene::Render()
{
	m_commonResources->GetRenderer()->Render();
}


void PlayScene::Finalize()
{

}

void PlayScene::ChangeState(IState* newState)
{
	// 終了処理
	m_currentState->PostUpdate();

	// ステートを切り替える
	m_currentState = newState;

	// スタート処理
	m_currentState->PreUpdate();
}

void PlayScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::SceneMessageID::FADE_OUT:

			break;
		case Message::SceneMessageID::FADE_OUT_CANGE_GAME_CLEAR_SCENE:
			
			// ステートを切り替える
			this->ChangeState(m_fadeOutState.get());
			// 次のシーンの準備を行う
			SceneManager::GetInstance()->PrepareScene<GameClearScene>();
			

			break;

		case Message::SceneMessageID::FADE_OUT_CANGE_GAME_OVER_SCENE:

			// ステートを切り替える
			this->ChangeState(m_fadeOutState.get());
			// 次のシーンの準備を行う
			SceneManager::GetInstance()->PrepareScene<GameOverScene>();
			
			break;

		case Message::SceneMessageID::MAIN:

			// ステートを切り替える
			this->ChangeState(m_countdownState.get());

			break;

		case Message::SceneMessageID::PLAY_MAIN_STATE:

			this->ChangeState(m_playMainState.get());
			break;
		default:
			break;
	}
}


/// <summary>
/// シーンのステート作成
/// </summary>
void PlayScene::CreateState()
{
	// フェードインステート作成 初期化処理
	m_fadeInState = std::make_unique<FadeInState>(0);
	m_fadeInState->Initialize();

	// カウントダウンステート
	m_countdownState = std::make_unique<CountdownState>();
	m_countdownState->Initialize();

	// プレイシーンメインステート作成　初期化処理
	m_playMainState = std::make_unique<PlayMainState>();
	m_playMainState->Initialize();

	// フェードアウトステート作成　初期化処理
	m_fadeOutState = std::make_unique<FadeOutState>(Message::MessageData{ Message::MessageID::FADE_OUT,0,1.0f ,false });
	m_fadeOutState->Initialize();

	// 初期ステートを設定
	m_currentState = m_fadeInState.get();
}

