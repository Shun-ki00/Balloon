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
#include "Game/Scenes/GameClearScene.h"
#include "Game/Node/Root.h"
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/EffectFactory.h"
#include "Game/Parameters/Parameters.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Scenes/PlayScene.h"


#include "Game/Factorys/SceneFactory.h"

#include "Game/Scenes/TitleScene.h"
#include "Game/Scenes/GameOverScene.h"

// ステート
#include "Interface/IState.h"
#include "Game/States/SceneStates/FadeStates/FadeInState.h"
#include "Game/States/SceneStates/FadeStates/FadeOutState.h"
#include "Game/States/SceneStates/TitleMainState.h"

// フェードオブジェクト番号
const int GameClearScene::FADE_OBJECT_NUMBER = 5;

/// <summary>
/// コンストラクタ
/// </summary>
GameClearScene::GameClearScene()
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
GameClearScene::~GameClearScene() {}


/// <summary>
/// 初期化処理
/// </summary>
void GameClearScene::Initialize()
{
	// ルートの初期化処理
	m_root->Initialize();

	// オブジェクトの作成
	SceneFactory::CreateGameClearScene(m_root);

	// ステートの作成
	this->CreateStates();
}

/// <summary>
/// スタート処理
/// </summary>
void GameClearScene::Start()
{
	// ステートスタート処理
	m_currentState->PreUpdate();
}

/// <summary>
/// 更新処理する
/// </summary>
void GameClearScene::Update()
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

void GameClearScene::Render()
{
	// 描画処理を行う
	m_commonResources->GetRenderer()->Render();
}

/// <summary>
/// 終了処理
/// </summary>
void GameClearScene::Finalize() {}

/// <summary>
/// ステートを切り替える
/// </summary>
/// <param name="newState">次のステート</param>
void GameClearScene::ChangeState(IState* newState)
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
void GameClearScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::SceneMessageID::FADE_OUT:

			break;
		case Message::SceneMessageID::FADE_OUT_CANGE_MENU_SCENE:

			// 次のシーンの準備を行う
			SceneManager::GetInstance()->PrepareScene<GameOverScene>();

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
void GameClearScene::CreateStates()
{
	// フェードインステート作成 初期化処理
	m_fadeInState = std::make_unique<FadeInState>(FADE_OBJECT_NUMBER);
	m_fadeInState->Initialize();

	// タイトルシーンメインステート作成　初期化処理
	m_titleMainState = std::make_unique<TitleMainState>();
	m_titleMainState->Initialize();

	// フェードアウトステート作成　初期化処理
	m_fadeOutState = std::make_unique<FadeOutState>(FADE_OBJECT_NUMBER);
	m_fadeOutState->Initialize();

	// 初期ステートを設定
	m_currentState = m_fadeInState.get();
}