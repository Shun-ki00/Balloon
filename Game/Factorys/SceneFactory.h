#pragma once

class Root;

class SceneFactory
{
public:

	// タイトルシーンの作成
	static void CreateTitleScene(Root* root);

	// メニューシーンの作成

	// ステージセレクトの作成

	// プレイシーンの作成
	static void CreatePlayScene(Root* root);


	// ゲームクリアシーンの作成
	static void CreateGameClearScene(Root* root);

	// ゲームオーバーシーンの作成
	static void CreateGameOverScene(Root* root);


};