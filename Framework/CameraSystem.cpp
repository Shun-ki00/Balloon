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
	// インスタンスを取得する
	m_commonResources = CommonResources::GetInstance();
}


void CameraSystem::Initialize()
{
	m_transform = std::make_unique<Transform>();
	m_transform->Initialize(DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::Zero);

	m_objectID = ObjectID::CAMERA_SYSTEM;

	// 遷移カメラを作成
	m_blendingCamera = std::make_unique<BlendingCamera>();
	m_blendingCamera->Initialize();
	// 現在のカメラ
	m_currentCamera = nullptr;
	// バーチャルカメラ初期化
	m_virtualCameras.clear();
	// カメラ番号初期化
	m_cameraIndex = 0;
}


void CameraSystem::Update(const float& elapsedTime)
{

	// 遷移カメラ
	m_blendingCamera->Update(elapsedTime);

	// 現在のカメラの更新を行う
	m_currentCamera->Update(elapsedTime);

	// ビュー行列の計算
	// 遷移中かどうか
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
	// カメラを切り替える
	this->ChangeCamera(messageData.dataInt, messageData.dataFloat);
}


void CameraSystem::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}


void CameraSystem::Attach(std::unique_ptr<ICamera> camera)
{
	// カメラを追加する
	m_virtualCameras[m_cameraIndex] = std::move(camera);
	// 番号の更新
	m_cameraIndex++;
	// 初期番号を現在のカメラに設定
	m_currentCamera = m_virtualCameras[0].get();
}


void CameraSystem::ChangeCamera(int index, float time)
{
	// 遷移中なら切り替えない
	if (m_blendingCamera->GetisBlending()) return;

	// 遷移開始
	m_blendingCamera->StartBlending(m_currentCamera->GetTransform(), m_virtualCameras[index]->GetTransform(), time,Tween::EasingType::Linear);

	// 現在のカメラを変更
	m_currentCamera = m_virtualCameras[index].get();
}



