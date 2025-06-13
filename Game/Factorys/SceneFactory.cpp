#include "pch.h"
#include "Game/Factorys/SceneFactory.h"
#include "Game/Factorys/UIFactory.h"
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/BalloonFactory.h"
#include "Game/Factorys/EnemyFactory.h"
#include "Game/Factorys/CameraFactory.h"
#include "Game/Factorys/EffectFactory.h"
#include "Game/Node/Root.h"


/// <summary>
/// タイトルシーンのオブジェクトを作成
/// </summary>
/// <param name="root">ルートオブジェクト</param>
void SceneFactory::CreateTitleScene(Root* root)
{
	// プレイヤー （固定）0
	root->Attach(PlayerFactory::CreatePlayer(root,
		{ 2.7f , -0.5f ,-1.5f }, { 0.0f ,-45.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f, true));

	// カメラの作成をする
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Backward,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Down, DirectX::XMConvertToRadians(30.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(10.0f)))
	);

	// カメラシステムをアタッチする 1
	root->Attach(CameraFactory::CreateCameraSystem(root, std::move(cameras)));

	// タイトルロゴ 2
	root->Attach(UIFactory::CreateTitleLogoUI(
		root, IObject::ObjectID::TITLE_LOGO_UI,
		DirectX::SimpleMath::Vector3{ 400.0f , -300.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One));

	// スタートテキスト 3
	root->Attach(UIFactory::CreateStartTextUI(
		root, IObject::ObjectID::START_TEXT_UI,
		DirectX::SimpleMath::Vector3{ 400.0f , 400.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::Zero));

	// フェードオブジェクト 4
	root->Attach(UIFactory::CreateFade(
		root, IObject::ObjectID::FADE,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One));
}


/// <summary>
/// ゲームクリアシーンのオブジェクトを作成
/// </summary>
/// <param name="root">ルートオブジェクト</param>
void SceneFactory::CreateGameClearScene(Root* root)
{
	// プレイヤー 0 
	root->Attach(PlayerFactory::CreatePlayer(root,
		{ 2.7f , -0.5f ,-1.5f }, { 0.0f ,-45.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f, true));

	// カメラの作成をする
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Backward,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Down, DirectX::XMConvertToRadians(30.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(10.0f)))
	);

	// カメラシステムをアタッチする 1
	root->Attach(CameraFactory::CreateCameraSystem(root, std::move(cameras)));


	// ボタンUI 2
	root->Attach(UIFactory::CreateResultSceneButtons(
		root, IObject::ObjectID::RESULT_SCENE_KEYS_GUIDE_UI,
		{ 1280.0f / 2.0f - 200.0f , 300.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One * 0.7f));

	// キーガイドUI 3
	root->Attach(UIFactory::CreateResultSceneKeyGuideUI(
		root, IObject::ObjectID::RESULT_SCENE_KEYS_GUIDE_UI,
		{ 1280.0f / 2.0f - 50.0f , 720.0f - 50.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One * 0.7f));

	// クリアテキスト 4
	root->Attach(UIFactory::CreateResultTextUI(
		root, IObject::ObjectID::RESULT_TEXT_UI,
		{ 1280.0f / 2.0f - 200.0f , 150.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One * 0.7f,
		ResultTextUI::TextID::CLEAR));

	// フェードオブジェクト 5
	root->Attach(UIFactory::CreateFade(
		root, IObject::ObjectID::FADE,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One));
}


/// <summary>
/// ゲームオーバーシーンのオブジェクトを作成
/// </summary>
/// <param name="root">ルートオブジェクト</param>
void SceneFactory::CreateGameOverScene(Root* root)
{
	// プレイヤー 0
	root->Attach(PlayerFactory::CreatePlayer(root,
		{ 2.7f , -0.5f ,-1.5f }, { 0.0f ,-45.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f, true));


	// カメラの作成をする
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Backward,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Down, DirectX::XMConvertToRadians(30.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(10.0f)))
	);

	// カメラシステムをアタッチする 1
	root->Attach(CameraFactory::CreateCameraSystem(root, std::move(cameras)));

	// ボタンUI 2
	root->Attach(UIFactory::CreateResultSceneButtons(
		root, IObject::ObjectID::RESULT_SCENE_KEYS_GUIDE_UI,
		{ 1280.0f / 2.0f - 200.0f , 300.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One * 0.7f));

	// キーガイドUI 3
	root->Attach(UIFactory::CreateResultSceneKeyGuideUI(
		root, IObject::ObjectID::RESULT_SCENE_KEYS_GUIDE_UI,
		{ 1280.0f / 2.0f - 50.0f , 720.0f - 50.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One * 0.7f));

	// クリアテキスト 4
	root->Attach(UIFactory::CreateResultTextUI(
		root, IObject::ObjectID::RESULT_TEXT_UI,
		{ 1280.0f / 2.0f - 200.0f , 150.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One * 0.7f,
		ResultTextUI::TextID::FAILED));

	// フェードオブジェクト 5
	root->Attach(UIFactory::CreateFade(
		root, IObject::ObjectID::FADE,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One));
}