// ============================================
// 
// ファイル名: StageSelectScene.h
// 概要: StageSelectScene.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IScene.h"


class CommonResources;
class Root;
class Parameters;
class SceneManager;
class FadeInState;
class StageSelectMainState;
class FadeOutState;

class StageSelectScene : public IScene
{
public:
	// コンストラクタ
	StageSelectScene();
	// デストラクタ
	~StageSelectScene();

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
	// 当たり判定メッセージを受け取る
	void OnSceneMessegeAccepted(Message::SceneMessageID messageID) override;

private:

	// ステートの作成
	void CreateStates();
	
private:

	// パラメーター
	Parameters* m_parameters;
	// 共有リソース
	CommonResources* m_commonResources;
	// シーンマネージャー
	SceneManager* m_sceneManager;
	// ルート
	Root* m_root;

	// 現在の状態
	IState* m_currentState;

	// フェードインステート
	std::unique_ptr<FadeInState> m_fadeInState;
	// ステージセレクトシーンメインステート
	std::unique_ptr<StageSelectMainState> m_stageSelectMainState;
	// フェードアウトステート
	std::unique_ptr<FadeOutState> m_fadeOutState;

};