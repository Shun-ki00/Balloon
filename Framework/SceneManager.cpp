// ============================================
// 
// ファイル名: SceneManager.cpp
// 概要: 各シーンを管理するクラス（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Framework/SceneManager.h"
#include "Framework/CommonResources.h"
#include "Game/Game.h"
#include "Game/Node/Root.h"
#include "Game/Message/KeyboardMessenger.h"
#include "Game/Message/ObjectMessenger.h"
#include "Framework/Tween/TweenManager.h"

// 各シーン
#include "Game/Scenes/DebugScene.h"
#include "Game/Scenes/TitleScene.h"
#include "Game/Scenes/GameClearScene.h"
#include "Game/Scenes/PlayScene.h"
#include "Game/Scenes/GameOverScene.h"
#include "Game/Scenes/StageSelectScene.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager()
	:
	m_currentScene{},
	m_nextScene{},
	m_isChange{},
	m_future{}
{
	// 共有リソースのインスタンスを取得する
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// 初期化処理
/// </summary>
void SceneManager::Initialize()
{
	// アタッチ開始
	Root::GetInstance()->Begin();
	m_commonResources->GetRenderer()->Begin();
	ObjectMessenger::GetInstance()->Begin();
	KeyboardMessenger::GetInstance()->Begin();

	// 初期シーンの作成
	m_currentScene = std::make_unique<TitleScene>();
	// 初期シーンの初期化
	m_currentScene->Initialize();

	// アタッチ終了
	Root::GetInstance()->End();
	m_commonResources->GetRenderer()->End();
	ObjectMessenger::GetInstance()->End();
	KeyboardMessenger::GetInstance()->End();

	// 初期シーンのスタート処理
	m_currentScene->Start();

	m_isChange = false;
	m_isExitGame = false;
}

/// <summary>
/// 更新処理
/// </summary>
void SceneManager::Update()
{
	if (m_currentScene != nullptr)
		m_currentScene->Update();
}
/// <summary>
/// 描画処理
/// </summary>
void SceneManager::Render()
{
	if (m_currentScene != nullptr)
		m_currentScene->Render();
}
/// <summary>
/// 終了処理
/// </summary>
void SceneManager::Finalize()
{
	if (m_currentScene != nullptr)
		m_currentScene->Finalize();
}

void SceneManager::Dispatch(Message::SceneMessageID messageID)
{
	m_currentScene->OnSceneMessegeAccepted(messageID);
}

/// <summary>
/// シーン切り替え
/// </summary>
bool SceneManager::CheckChageScene()
{
	// ゲーム終了の場合
	if (m_isExitGame)
	{
		return false;
	}

	// シーン切り替えフラグがオンの場合
	if (m_isChange)
	{
		// 前のシーンの終了処理を行う
		m_currentScene->Finalize();

		// アタッチ終了
		Root::GetInstance()->End();
		CommonResources::GetInstance()->GetRenderer()->End();
		ObjectMessenger::GetInstance()->End();
		KeyboardMessenger::GetInstance()->End();

		TweenManager::GetInstance()->Stop();
		
		// 前のシーンを削除する
		m_currentScene.reset();

		// 次のシーンを入れる
		m_currentScene = std::move(m_nextScene);

		// 次のシーンスタート処理
		m_currentScene->Start();

		// フラグを解除する
		m_isChange = false;
	}

	return true;
}