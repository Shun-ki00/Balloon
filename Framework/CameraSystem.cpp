#include "pch.h"
#include "Framework/CameraSystem.h"
#include "Framework/CommonResources.h"
#include "Game/Cameras/BlendingCamera.h"
#include "Game/Node/Root.h"


CameraSystem::CameraSystem(Root* root, IObject* parent)
	:
	m_parent(parent),
	m_cameraIndex{},
	m_objectNumber(root->GetObjectNumber())
{
	// �C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();
}


void CameraSystem::Initialize()
{
	m_transform = std::make_unique<Transform>();
	m_transform->Initialize(DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::Zero);

	m_objectID = ObjectID::CAMERA_SYSTEM;

	// �J�ڃJ�������쐬
	m_blendingCamera = std::make_unique<BlendingCamera>();
	m_blendingCamera->Initialize();
	// ���݂̃J����
	m_currentCamera = nullptr;
	// �o�[�`�����J����������
	m_virtualCameras.clear();
	// �J�����ԍ�������
	m_cameraIndex = 0;
}


void CameraSystem::Update(const float& elapsedTime)
{

	// �J�ڃJ����
	m_blendingCamera->Update(elapsedTime);

	// ���݂̃J�����̍X�V���s��
	m_currentCamera->Update(elapsedTime);

	// �r���[�s��̌v�Z
	// �J�ڒ����ǂ���
	if (m_blendingCamera->GetisBlending())
		m_commonResources->SetViewMatrix(m_blendingCamera->CalculateViewMatrix());
	else
		m_commonResources->SetViewMatrix(m_currentCamera->CalculateViewMatrix());

}

void CameraSystem::Finalize()
{

}

void CameraSystem::OnMessegeAccepted(Message::MessageData messageData)
{
	// �J������؂�ւ���
	this->ChangeCamera(messageData.dataInt, messageData.dataFloat);
}


void CameraSystem::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}


void CameraSystem::Attach(std::unique_ptr<ICamera> camera)
{
	// �J������ǉ�����
	m_virtualCameras[m_cameraIndex] = std::move(camera);
	// �ԍ��̍X�V
	m_cameraIndex++;
	// �����ԍ������݂̃J�����ɐݒ�
	m_currentCamera = m_virtualCameras[0].get();
}


void CameraSystem::ChangeCamera(int index, float time)
{
	// �J�ڒ��Ȃ�؂�ւ��Ȃ�
	if (m_blendingCamera->GetisBlending()) return;

	// �J�ڊJ�n
	m_blendingCamera->StartBlending(m_currentCamera->GetTransform(), m_virtualCameras[index]->GetTransform(), time,Tween::EasingType::Linear);

	// ���݂̃J������ύX
	m_currentCamera = m_virtualCameras[index].get();
}



