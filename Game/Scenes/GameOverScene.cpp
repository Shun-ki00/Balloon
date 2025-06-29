// ============================================
// 
// ファイル名: TitleScene.cpp
// 概要: タイトルのシーン
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/GameOverScene.h"
#include "Game/Node/Root.h"
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/EffectFactory.h"
#include "Game/Parameters/Parameters.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Scenes/PlayScene.h"

#include "Game/Scenes/TitleScene.h"

#include "Game/Factorys/SceneFactory.h"


// ステート
#include "Interface/IState.h"
#include "Game/States/SceneStates/FadeStates/FadeInState.h"
#include "Game/States/SceneStates/FadeStates/FadeOutState.h"
#include "Game/States/SceneStates/TitleMainState.h"

// フェードオブジェクト番号
const int GameOverScene::FADE_OBJECT_NUMBER = 6;


/// <summary>
/// コンストラクタ
/// </summary>
GameOverScene::GameOverScene()
	:
	m_parameters{},
	m_commonResources{},
	m_currentState{},
	m_fadeInState{},
	m_titleMainState{},
	m_fadeOutState{},
	m_root{}
{
	// インスタンスを取得する
	m_commonResources  = CommonResources::GetInstance();
	m_parameters       = Parameters::GetInstance();
	m_root             = Root::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
GameOverScene::~GameOverScene() {}


/// <summary>
/// 初期化処理
/// </summary>
void GameOverScene::Initialize()
{
	// ルートの初期化処理
	m_root->Initialize();

	// オブジェクトの作成
	SceneFactory::CreateGameOverScene(m_root);

	// ステートの作成
	this->CreateStates();
}

/// <summary>
/// スタート処理
/// </summary>
void GameOverScene::Start()
{
	// ステートスタート処理
	m_currentState->PreUpdate();

	// スカイボックスを変更
	m_commonResources->GetSkyBox()->SetDayProgress(1.0f);
}

/// <summary>
/// 更新処理する
/// </summary>
void GameOverScene::Update()
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

void GameOverScene::Render()
{
	// 描画処理を行う
	m_commonResources->GetRenderer()->Render();
}

/// <summary>
/// 終了処理
/// </summary>
void GameOverScene::Finalize() 
{
	// スカイボックスを変更
	m_commonResources->GetSkyBox()->SetDayProgress(0.0f);
}

/// <summary>
/// ステートを切り替える
/// </summary>
/// <param name="newState">次のステート</param>
void GameOverScene::ChangeState(IState* newState)
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
void GameOverScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::SceneMessageID::FADE_OUT:

			break;
		case Message::SceneMessageID::FADE_OUT_CANGE_MENU_SCENE:

			// 次のシーンの準備を行う
			SceneManager::GetInstance()->PrepareScene<TitleScene>();

			// ステートを切り替える
			this->ChangeState(m_fadeOutState.get());

			break;		
		case Message::SceneMessageID::MAIN:

			// ステートを切り替える
			this->ChangeState(m_titleMainState.get());

			break;
		default:
			break;
	}
}


/// <summary>
///	シーンのステートの作成
/// </summary>
void GameOverScene::CreateStates()
{
	// フェードインステート作成 初期化処理
	m_fadeInState = std::make_unique<FadeInState>(FADE_OBJECT_NUMBER);
	m_fadeInState->Initialize();

	// タイトルシーンメインステート作成　初期化処理
	m_titleMainState = std::make_unique<TitleMainState>();
	m_titleMainState->Initialize();

	// フェードアウトステート作成　初期化処理
	m_fadeOutState = std::make_unique<FadeOutState>(Message::MessageData{ Message::MessageID::FADE_OUT_EXIT_GAME,0,1.0f ,false });
	m_fadeOutState->Initialize();

	// 初期ステートを設定
	m_currentState = m_fadeInState.get();
}