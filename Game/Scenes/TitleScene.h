// ============================================
// 
// ファイル名: TitleScene.h
// 概要: TitleScene.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IScene.h"


class CommonResources;
class Root;
class Parameters;
// ステート
class FadeInState;
class TitleMainState;
class FadeOutState;

class TitleScene : public IScene
{
public:
	// コンストラクタ
	TitleScene();
	// デストラクタ
	~TitleScene();

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

	// 現在の状態
	IState* m_currentState;

	// フェードインステート
	std::unique_ptr<FadeInState> m_fadeInState;
	// タイトルシーンメインステート
	std::unique_ptr<TitleMainState> m_titleMainState;
	// フェードアウトステート
	std::unique_ptr<FadeOutState> m_fadeOutState;
	// フェードアウトステート
	std::unique_ptr<FadeOutState> m_gameExitFadeOutState;

	// ルート
	Root* m_root;
};