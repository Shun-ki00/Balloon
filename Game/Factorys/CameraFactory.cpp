#include "pch.h"
#include "Game/Factorys/CameraFactory.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Node/Root.h"

// カメラ
#include "Framework/CameraSystem.h"
#include "Game/Cameras/FixedCamera.h"
#include "Game/Cameras/FollowCamera.h"


std::unique_ptr<IObject> CameraFactory::CreateCameraSystem(IObject* parent, std::vector<std::unique_ptr<ICamera>> cameras)
{
	std::unique_ptr<CameraSystem> cameraSystem;
	// CameraSystemクラスのインスタンスを作成する
	cameraSystem.reset(new CameraSystem(Root::GetInstance(),parent));
	// 初期化処理する
	cameraSystem->Initialize();

	// カメラを追加する
	for (auto& camera : cameras)
	{
		// カメラを渡す
		cameraSystem->Attach(std::move(camera));
	}

	// オブジェクトメッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::CAMERA_SYSTEM, cameraSystem->GetObjectNumber(), cameraSystem.get());

	// カメラシステムを返す
	return std::move(cameraSystem);
}


std::unique_ptr<ICamera> CameraFactory::CreateFixedCaemra(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation)
{
	std::unique_ptr<ICamera> fixedCamera;
	// FixedCameraクラスのインスタンスを生成する
	fixedCamera.reset(new FixedCamera(position,rotation));
	// 初期化処理
	fixedCamera->Initialize();

	return std::move(fixedCamera);
}


std::unique_ptr<ICamera> CameraFactory::CreateFollowCaemra(Transform* target, DirectX::SimpleMath::Vector3 distance)
{
	std::unique_ptr<ICamera> followCamera;
	// FixedCameraクラスのインスタンスを生成する
	followCamera.reset(new FollowCamera(target, distance));
	// 初期化処理
	followCamera->Initialize();

	return std::move(followCamera);
}