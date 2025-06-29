// ============================================
// 
// ファイル名: SceneManager.h
// 概要: SceneManager.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include <future>
#include "Interface/IScene.h"
#include "Game/Node/Root.h"
#include "Framework/CommonResources.h"
#include "Framework/Renderer.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Message/KeyboardMessenger.h"
#include "Game/Visitor/CollisionVisitor.h"


class IScene;

class SceneManager
{
public:

	// ステージ番号を取得
	int GetStageNumber() const { return m_stageNumber; }
	// ステージ番号を設定
	void GetStageNumber(const int& number) { m_stageNumber = number; }

public:
	// 初期フレームの時にシーンを変更する
	void ChageScene() { m_isChange = true; }
	// チェックチェンジシーン
	bool CheckChageScene();
	// ゲーム終了フラグを設定
	void SetIsGameExit() { m_isExitGame = true; }

	// ゲーム終了フラグを取得する
	bool GetIsGameExit() const { return m_isExitGame; }

public:
	
	// シーンを非同期で準備
	template <typename T>
	void PrepareScene()
	{
		CollisionVisitor::GetInstance()->Clear();

		// 非同期タスクでシーンを準備
		m_future = std::async(std::launch::async, [this]() 
		{
			// シーンの作成
			m_nextScene = std::make_unique<T>();
			// ルートのノードアタッチ許可
			Root::GetInstance()->Begin();
			// 描画オブジェクトのアタッチを許可
			CommonResources::GetInstance()->GetRenderer()->Begin();
			// オブジェクトメッセンジャーのアタッチを許可
			ObjectMessenger::GetInstance()->Begin();
			// キーボードメッセンジャーのアタッチを許可
			KeyboardMessenger::GetInstance()->Begin();

			// シーンの初期化処理を行う
			m_nextScene->Initialize();
		});
	}

private:
	//	コンストラクタ
	SceneManager();
	//	デストラクタ
	~SceneManager() = default;
public:
	SceneManager(const SceneManager&) = delete;             // コピー禁止
	SceneManager& operator=(const SceneManager&) = delete;  // コピー代入禁止
	SceneManager(const SceneManager&&) = delete;            // ムーブ禁止
	SceneManager& operator=(const SceneManager&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}

public:
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update();
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();

	void Dispatch(Message::SceneMessageID messageID);

private:

	// 共有リソース
	CommonResources* m_commonResources;
	
	// シーン
	std::unique_ptr<IScene> m_currentScene;
	// 次のシーン
	std::unique_ptr<IScene> m_nextScene;

	// シーン切り替えフラグ
	bool m_isChange;

	// 非同期タスク管理用
	std::future<void> m_future;

	// ゲーム終了フラグ
	bool m_isExitGame;

	// ステージ番号
	int m_stageNumber;
};