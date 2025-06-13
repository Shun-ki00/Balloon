#include "pch.h"
#include "Game/Cameras/FixedCamera.h"
#include "Game/Transform/Transform.h"


FixedCamera::FixedCamera(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation)
{
    // 回転をもとにターゲット座標を計算する
    DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Forward;
    // クォータニオンを適応
    target = DirectX::SimpleMath::Vector3::Transform(target, rotation);
    // 座標を加算
    target = target + position;

    m_transform = std::make_unique<Transform>();
    m_transform->Initialize(position, rotation, target);
}


void FixedCamera::Initialize()
{
    // 行列計算をおこう
    this->CalculateViewMatrix();
}


void FixedCamera::Update(const float& elapsedTime)
{
    // 固定カメラのため更新処理は行わない
    UNREFERENCED_PARAMETER(elapsedTime);
}


DirectX::SimpleMath::Matrix FixedCamera::CalculateViewMatrix()
{
    DirectX::SimpleMath::Vector3 eye    = m_transform->GetLocalPosition();
    DirectX::SimpleMath::Vector3 target = m_transform->GetLocalScale();
    DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

    m_viewMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(eye, target, up);

    return m_viewMatrix;
}