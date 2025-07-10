#include "pch.h"
#include "Game/Factorys/CameraFactory.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Node/Root.h"

// �J����
#include "Framework/CameraSystem.h"
#include "Game/Cameras/FixedCamera.h"
#include "Game/Cameras/FollowCamera.h"


std::unique_ptr<IObject> CameraFactory::CreateCameraSystem(IObject* parent, std::vector<std::unique_ptr<ICamera>> cameras)
{
	std::unique_ptr<CameraSystem> cameraSystem;
	// CameraSystem�N���X�̃C���X�^���X���쐬����
	cameraSystem.reset(new CameraSystem(Root::GetInstance(),parent));
	// ��������������
	cameraSystem->Initialize();

	// �J������ǉ�����
	for (auto& camera : cameras)
	{
		// �J������n��
		cameraSystem->Attach(std::move(camera));
	}

	// �I�u�W�F�N�g���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::CAMERA_SYSTEM, cameraSystem->GetObjectNumber(), cameraSystem.get());

	// �J�����V�X�e����Ԃ�
	return std::move(cameraSystem);
}


std::unique_ptr<ICamera> CameraFactory::CreateFixedCaemra(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation)
{
	std::unique_ptr<ICamera> fixedCamera;
	// FixedCamera�N���X�̃C���X�^���X�𐶐�����
	fixedCamera.reset(new FixedCamera(position,rotation));
	// ����������
	fixedCamera->Initialize();

	return std::move(fixedCamera);
}


std::unique_ptr<ICamera> CameraFactory::CreateFollowCaemra(Object* target, DirectX::SimpleMath::Vector3 distance)
{
	std::unique_ptr<ICamera> followCamera;
	// FixedCamera�N���X�̃C���X�^���X�𐶐�����
	followCamera.reset(new FollowCamera(target, distance));
	// ����������
	followCamera->Initialize();

	return std::move(followCamera);
}