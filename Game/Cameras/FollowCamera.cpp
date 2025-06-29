#include "pch.h"
#include "Game/Cameras/FollowCamera.h"
#include "Game/Transform/Transform.h"


FollowCamera::FollowCamera(Transform* target, DirectX::SimpleMath::Vector3 distance)
{
   // 距離を設定
    m_distance = distance;
    // ターゲットのTransfomを設定
    m_targetTransform = target;
}


void FollowCamera::Initialize()
{
    // Transformを作成
    m_transform = std::make_unique<Transform>();
    m_transform->Initialize(
        DirectX::SimpleMath::Vector3::Zero,
        DirectX::SimpleMath::Quaternion::Identity,
        DirectX::SimpleMath::Vector3::Zero);
}


void FollowCamera::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Backward;
    DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Zero;

    // ターゲットの座標を設定する
    target = m_targetTransform->GetLocalPosition();
    // ターゲットの回転を適応する
    position = DirectX::SimpleMath::Vector3::Transform(m_distance, m_targetTransform->GetLocalRotation());
    // カメラの座標を決定
    position += target;

    m_transform->SetLocalPosition(position);
    m_transform->SetLocalScale(target);
    
    // ビュー行列を計算
    this->CalculateViewMatrix();
}


DirectX::SimpleMath::Matrix FollowCamera::CalculateViewMatrix()
{
    DirectX::SimpleMath::Vector3 eye    = m_transform->GetLocalPosition();
    DirectX::SimpleMath::Vector3 target = m_transform->GetLocalScale();
    DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

    m_viewMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(eye, target, up);

    return m_viewMatrix;
}