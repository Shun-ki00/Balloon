// ============================================
// 
// ファイル名: DebugScene.h
// 概要: DebugScene.cppのヘッダーファイル
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

class DebugScene : public IScene
{
public:
	// コンストラクタ
	DebugScene();
	// デストラクタ
	~DebugScene();

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

	// パラメーター
	Parameters* m_parameters;
	// ステアリングビヘイビア
	WindBehavior* m_steeringBehavior;

	// 共有リソース
	CommonResources* m_commonResources;
	// デバッグカメラで実装
	std::unique_ptr<DebugCamera> m_debugCamera;

	// プレイヤーを追加
	Root* m_root;


	// パーティクル生成器
	std::unique_ptr< ParticleEmitter> m_emitter;
};