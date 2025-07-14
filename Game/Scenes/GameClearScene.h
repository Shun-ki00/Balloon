// ============================================
// 
// ファイル名: GameClearScene.h
// 概要: GameClearScene.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IScene.h"

class CommonResources;
class Root;
class Parameters;
class FadeInState;
class GameClearMainState;
class FadeOutState;

class GameClearScene : public IScene
{
public:
	// コンストラクタ
	GameClearScene();
	// デストラクタ
	~GameClearScene();

public:
	// 初期化処理
	void Initialize() override;
	// スタート処理
	void Start()  override;
	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;
	// 終了処理
	void Finalize() override;

	// シーンのステートを変更する
	void ChangeState(IState* newState) override;
	// メッセージを受け取る
	void OnSceneMessegeAccepted(Message::SceneMessageID messageID) override;

private:

	// ステートの作成
	void CreateStates();

	
private:

	// パラメーター
	Parameters* m_parameters;
	// 共有リソース
	CommonResources* m_commonResources;
	// ルート
	Root* m_root;

	// 現在の状態
	IState* m_currentState;

	// フェードインステート
	std::unique_ptr<FadeInState> m_fadeInState;
	// ゲームクリアシーンメインステート
	std::unique_ptr<GameClearMainState> m_gameClearMainState;
	// フェードアウトステート
	std::unique_ptr<FadeOutState> m_fadeOutState;

};