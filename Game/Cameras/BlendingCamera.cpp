#include "pch.h"
#include "Game/Cameras/BlendingCamera.h"
#include "Game/Transform/Transform.h"


BlendingCamera::BlendingCamera()
{
    m_isBlending = false;
}


void BlendingCamera::Initialize()
{
    m_transform = std::make_unique<Transform>();
    m_transform->Initialize(DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::Zero);
}


void BlendingCamera::Update(const float& elapsedTime)
{
	if (!m_isBlending) return;

    // 現在の時間を更新する
    m_elapsed += elapsedTime;
    
    // アニメーションの進行度を計算（0.0 ～ 1.0 に正規化）
    float t = m_elapsed  / m_blendingTime;
    // t を 1.0 にクランプ（補間の上限を超えないようにする）
    if (t > 1.0f) t = 1.0f;

    // イージングを適用
    float easeT = Tween::EasingFunction(m_easingType, t);

    // 移動処理 (DoMove)
    m_transform->SetLocalPosition(
        DirectX::SimpleMath::Vector3::Lerp(m_startPosition, m_nextCaemraTransform->GetLocalPosition(), easeT));
    // 回転処理 (DoRotation)
    //m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Slerp(m_startRotation, m_endRotation, easeT));
    // スケール処理 (DoScale)
    m_transform->SetLocalScale(
        DirectX::SimpleMath::Vector3::Lerp(m_startTargetPosition, m_nextCaemraTransform->GetLocalScale(), easeT));

    // 遷移が終了したら
    if (t >= 1.0f)
    {
        // カメラシステムに終了のメッセージを通知する

        // 終了
        m_isBlending = false;

        // 数値のリセット
        m_startPosition       = DirectX::SimpleMath::Vector3::Zero;
        m_startTargetPosition = DirectX::SimpleMath::Vector3::Zero;
        m_easingType          = Tween::EasingType::Linear;
        m_elapsed             = 0.0f;
        m_blendingTime        = 0.0f;
    }

}


void BlendingCamera::StartBlending(Transform* currentCamera, Transform* nextCamera, float t, Tween::EasingType easingType)
{
	// 遷移中に変更
	m_isBlending = true;

	// 遷移するカメラのTransformを設定
	m_nextCaemraTransform = nextCamera;

	// 遷移時間を設定
	m_blendingTime = t;

	// イージングの設定
	m_easingType = easingType;

    // 開始座標を設定
    m_startPosition = currentCamera->GetLocalPosition();
    // 開始ターゲット座標を設定
    m_startTargetPosition = currentCamera->GetLocalScale();

    // 経過時間をリセット
    m_elapsed = 0.0f;

}

DirectX::SimpleMath::Matrix BlendingCamera::CalculateViewMatrix()
{
    DirectX::SimpleMath::Vector3 eye    = m_transform->GetLocalPosition();
    DirectX::SimpleMath::Vector3 target = m_transform->GetLocalScale();
    DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

    m_viewMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(eye, target, up);

    return m_viewMatrix;
}