#pragma once
#include "Interface/ICamera.h"

class IObject;

class CameraFactory
{

public:

	static std::unique_ptr<IObject> CreateCameraSystem(IObject* parent,std::vector<std::unique_ptr<ICamera>> cameras);

	// �Œ�J�������쐬����
	static std::unique_ptr<ICamera> CreateFixedCaemra(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation);
	// �ǔ��J�������쐬����
	static std::unique_ptr<ICamera> CreateFollowCaemra(Transform* target, DirectX::SimpleMath::Vector3 distance);
	

};