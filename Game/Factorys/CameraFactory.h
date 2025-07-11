#pragma once
#include "Interface/ICamera.h"

class IObject;
class Object;

class CameraFactory
{

public:

	static std::unique_ptr<IObject> CreateCameraSystem(IObject* parent,std::vector<std::unique_ptr<ICamera>> cameras);

	// 固定カメラを作成する
	static std::unique_ptr<ICamera> CreateFixedCaemra(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation);
	// 追尾カメラを作成する
	static std::unique_ptr<ICamera> CreateFollowCaemra(Object* target, DirectX::SimpleMath::Vector3 distance);
	

};