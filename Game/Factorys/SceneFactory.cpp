#include "pch.h"
#include "Game/Factorys/SceneFactory.h"
#include "Game/GameConfig/GameConfig.h"
#include "Game/Factorys/UIFactory.h"
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/BalloonFactory.h"
#include "Game/Factorys/EnemyFactory.h"
#include "Game/Factorys/CameraFactory.h"
#include "Game/Factorys/EffectFactory.h"
#include "Game/Factorys/WoodBoxFactory.h"
#include "Game/Node/Root.h"
#include "Game/Parameters/ParameterBuffers.h"

#include <iostream>
#include <fstream>


/// <summary>
/// タイトルシーンのオブジェクトを作成
/// </summary>
/// <param name="root">ルートオブジェクト</param>
void SceneFactory::CreateTitleScene(Root* root)
{
	nlohmann::json data = GameConfig::GetInstance()->GetParameters("Title");

	Player player;
	data.get_to(player);

	std::vector<UI> uis;
	data.at("UI").get_to(uis);

	// プレイヤー （固定）0
	root->Attach(PlayerFactory::CreatePlayer(root,
		player.position, player.rotation, player.scale, true));

	// カメラの作成をする
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Backward,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Down, DirectX::XMConvertToRadians(30.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(10.0f)))
	);
	// カメラシステムをアタッチする 1
	root->Attach(CameraFactory::CreateCameraSystem(root, std::move(cameras)));

	if (uis.size() >= 3)
	{
		// タイトルロゴ
		root->Attach(UIFactory::CreateTitleLogoUI(
			root, IObject::ObjectID::TITLE_LOGO_UI,
			uis[0].position,
			uis[0].rotation,
			uis[0].scale));

		// スタートテキスト
		root->Attach(UIFactory::CreateStartTextUI(
			root, IObject::ObjectID::START_TEXT_UI,
			uis[1].position,
			uis[1].rotation,
			uis[1].scale));

		// フェード
		root->Attach(UIFactory::CreateFade(
			root, IObject::ObjectID::FADE,
			uis[2].position,
			uis[2].rotation,
			uis[2].scale));
	}

	//// バイナリへ変換（例: CBOR）
	//std::vector<uint8_t> binary = json::to_msgpack(data);
	//// 出力ファイル
	//std::ofstream output("Resources/Json/TitleScene.msgpack", std::ios::binary);
	//output.write(reinterpret_cast<const char*>(binary.data()), binary.size());

}

/// <summary>
/// ステージセレクトシーンオブジェクトの作成
/// </summary>
/// <param name="root">ルートオブジェクト</param>
void SceneFactory::CreateStageSelectScene(Root* root)
{

	// ステージナンバー

	// ステージセレクト背景

	// ステージセレクト操作説明


}



/// <summary>
/// プレイシーンオブジェクト作成
/// </summary>
/// <param name="root">ルートオブジェクト</param>
void SceneFactory::CreatePlayScene(Root* root)
{

	// プレイヤー （固定）0
	root->Attach(PlayerFactory::CreatePlayer(root,
		DirectX::SimpleMath::Vector3::Zero, { 0.0f ,0.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f, false));

	// 敵　複数
	root->Attach(EnemyFactory::CreateEnemy(root,
		{ 2.7f , -0.5f ,-1.5f }, { 0.0f ,0.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f));
	root->Attach(EnemyFactory::CreateEnemy(root,
		{ 2.7f , -0.5f ,-2.5f }, { 0.0f ,0.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f));
	root->Attach(EnemyFactory::CreateEnemy(root,
		{ 2.7f , -4.5f ,-1.5f }, { 0.0f ,0.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f));
	root->Attach(EnemyFactory::CreateEnemy(root,
		{ 2.7f , 3.5f ,-1.5f }, { 0.0f ,0.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f));

	// カウントダウンUI
	root->Attach(UIFactory::CreateCountdownUI(root, IObject::ObjectID::COUNTDOWN_UI,
		{ 1280.0f + 300.0f  , 720.0f / 2.0f,1.0f }, DirectX::SimpleMath::Vector3::Zero, {1.0f ,1.0f ,0.0f}));
	// タイマーUI
	root->Attach(UIFactory::CreateTimerFrameUI(root, IObject::ObjectID::TIME_FRAME_UI,
		{ 1180.0f , 100.0f ,0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.5f));
	// タイムナンバーUI
	root->Attach(UIFactory::CreateTimeUI(root, IObject::ObjectID::TIME_NUMBER_UI,
		{ 1180.0f , 100.0f ,0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.35f));
	// プレイヤーの高さUI
	root->Attach(UIFactory::CreateHeightMeterUI(root, IObject::ObjectID::HEIGHT_METER_UI,
		{ 1280.0f - 70.0f , 720.0f / 2.0f ,0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.5f));
	// キー操作説明UI
	root->Attach(UIFactory::CreatePlaySceneKeyGuideUI(root, IObject::ObjectID::HEIGHT_METER_UI,
		{ 400.0f , 720.0f - 35.0f ,0.0f }, DirectX::SimpleMath::Vector3::Zero, {2.0f , 2.0f,0.0f}));

	// 風船の大きさゲージフレームUI
	root->Attach(UIFactory::CreateBalloonFrameUI(root, IObject::ObjectID::BALLOON_HP_FRAME_UI,
		DirectX::SimpleMath::Vector3(100.0f, 100.0f, 0.0f), DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.3f));
	// 風船の大きさゲージUI
	root->Attach(UIFactory::CreateBalloonHPUI(root, IObject::ObjectID::BALLOON_HP_UI,
		{ 100.0f , 141.0f  ,0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.6f));

	// 体力ゲージUI
	root->Attach(UIFactory::CreateHPUI(root, IObject::ObjectID::HP_UI,
		{ 260.0f , 120.0f ,0.0f }, DirectX::SimpleMath::Vector3::Zero, {0.4f , 0.35f, 0.0f}));

	// フェード
	//root->Attach(UIFactory::CreateFade(root, IObject::ObjectID::FADE,
	//	DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Vector3::One));

}



/// <summary>
/// ゲームクリアシーンのオブジェクトを作成
/// </summary>
/// <param name="root">ルートオブジェクト</param>
void SceneFactory::CreateGameClearScene(Root* root)
{
	nlohmann::json data = GameConfig::GetInstance()->GetParameters("Clear");

	Player player;
	data.get_to(player);

	std::vector<UI> uis;
	data.at("UI").get_to(uis);


	// プレイヤー 0 
	root->Attach(PlayerFactory::CreatePlayer(root,
		player.position, player.rotation, player.scale, true));

	// カメラの作成をする
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Backward,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Down, DirectX::XMConvertToRadians(30.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(10.0f)))
	);

	// カメラシステムをアタッチする 1
	root->Attach(CameraFactory::CreateCameraSystem(root, std::move(cameras)));


	// ボタンUI（2）
	root->Attach(UIFactory::CreateResultSceneButtons(
		root,
		IObject::ObjectID::RESULT_SCENE_KEYS_GUIDE_UI,
		uis[0].position,
		uis[0].rotation,
		uis[0].scale
	));

	// キーガイドUI（3）
	root->Attach(UIFactory::CreateResultSceneKeyGuideUI(
		root,
		IObject::ObjectID::RESULT_SCENE_KEYS_GUIDE_UI,
		uis[1].position,
		uis[1].rotation,
		uis[1].scale
	));

	// クリアテキスト（4）
	root->Attach(UIFactory::CreateResultTextUI(
		root,
		IObject::ObjectID::RESULT_TEXT_UI,
		uis[2].position,
		uis[2].rotation,
		uis[2].scale,
		ResultTextUI::TextID::CLEAR
	));

	// フェードUI（5）
	root->Attach(UIFactory::CreateFade(
		root,
		IObject::ObjectID::FADE,
		uis[3].position,
		uis[3].rotation,
		uis[3].scale
	));
}


/// <summary>
/// ゲームオーバーシーンのオブジェクトを作成
/// </summary>
/// <param name="root">ルートオブジェクト</param>
void SceneFactory::CreateGameOverScene(Root* root)
{
	// プレイヤー 0
	root->Attach(PlayerFactory::CreatePlayer(root,
		{ 4.7f , -20.0f ,-3.5f }, { 0.0f ,0.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f, true));

	// 木箱 1
	root->Attach(WoodBoxFactory::CreateWoodBox(root,
		{ 4.7f , -20.9f ,-3.5f }, { 0.0f ,0.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.002f));


	// カメラの作成をする
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Backward + DirectX::SimpleMath::Vector3::Down * 18.0f,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Down, DirectX::XMConvertToRadians(30.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(5.0f)))
	);

	// カメラシステムをアタッチする 2
	root->Attach(CameraFactory::CreateCameraSystem(root, std::move(cameras)));

	// ボタンUI 3
	root->Attach(UIFactory::CreateResultSceneButtons(
		root, IObject::ObjectID::RESULT_SCENE_KEYS_GUIDE_UI,
		{ 1280.0f / 2.0f - 200.0f , 300.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One * 0.7f));

	// キーガイドUI 4
	root->Attach(UIFactory::CreateResultSceneKeyGuideUI(
		root, IObject::ObjectID::RESULT_SCENE_KEYS_GUIDE_UI,
		{ 1280.0f / 2.0f - 50.0f , 720.0f - 50.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One * 0.7f));

	// クリアテキスト 5
	root->Attach(UIFactory::CreateResultTextUI(
		root, IObject::ObjectID::RESULT_TEXT_UI,
		{ 1280.0f / 2.0f - 200.0f , 150.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One * 0.7f,
		ResultTextUI::TextID::FAILED));

	// フェードオブジェクト 6
	root->Attach(UIFactory::CreateFade(
		root, IObject::ObjectID::FADE,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One));
}