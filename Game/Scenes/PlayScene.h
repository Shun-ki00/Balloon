// ============================================
// 
// ファイル名: PlayScene.h
// 概要: PlayScene.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IScene.h"


class CommonResources;
class DebugCamera;
class Root;
class Parameters;
class WindBehavior;
class ParticleEmitter;
class FadeInState;
class CountdownState;
class PlayMainState;
class FadeOutState;

class PlayScene : public IScene
{
public:
	// コンストラクタ
	PlayScene();
	// デストラクタ
	~PlayScene();

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

	// ステートを作成
	void CreateState();

private:

	// パラメーター
	Parameters* m_parameters;
	// 共有リソース
	CommonResources* m_commonResources;
	// ルート
	Root* m_root;

	// デバッグカメラで実装
	std::unique_ptr<DebugCamera> m_debugCamera;

	// 現在の状態
	IState* m_currentState;

	// フェードインステート
	std::unique_ptr<FadeInState> m_fadeInState;
	// カウントダウンステート
	std::unique_ptr<CountdownState> m_countdownState;
	// メインステート
	std::unique_ptr<PlayMainState> m_playMainState;
	// フェードアウトステート
	std::unique_ptr<FadeOutState> m_fadeOutState;
};