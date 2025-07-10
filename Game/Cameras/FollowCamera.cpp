#include "pch.h"
#include "Game/Cameras/FollowCamera.h"
#include "Game/Transform/Transform.h"
#include "Game/Object/Object.h"

const float FollowCamera::SPEED_TO_ZOOM_THRESHOLD = 4.0f;
const float FollowCamera::ZOOM_INTERPOLATION_SPEED = 10.0f;
const float FollowCamera::ZOOM_RATIO = 0.4f;

const float FollowCamera::SPRING_STIFFNESS = 80.0f;
const float FollowCamera::SPRING_DAMPING = 20.0f;


FollowCamera::FollowCamera(Object* target, DirectX::SimpleMath::Vector3 distance)
    :
    m_transform{},
    m_viewMatrix{},
    m_target{},
    m_distance{},
    m_velocity{},
    m_zoomBlend{}
{
   // 距離を設定
    m_distance = distance;
    // ターゲットのオブジェクトを設定
    m_target = target;
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
    using namespace DirectX::SimpleMath;

    // ターゲットの情報を取得
    Transform* targetTransform = m_target->GetTransform();
    Vector3 targetPosition     = targetTransform->GetLocalPosition();
    Quaternion targetRotation  = targetTransform->GetLocalRotation();
    Vector3 targetVelocity     = m_target->GetVelocity();

    // ターゲットの速度を取得
    const float currentSpeed = targetVelocity.Length();

    // ズーム判定
    const float desiredZoom = (currentSpeed > SPEED_TO_ZOOM_THRESHOLD) ? 1.0f : 0.0f;

    // ズーム補間値の更新
    m_zoomBlend = std::clamp(
        std::lerp(m_zoomBlend, desiredZoom, elapsedTime * ZOOM_INTERPOLATION_SPEED), 0.0f, 1.0f
    );

    // ズーム距離を計算
    const Vector3 zoomedDistance = m_distance * ZOOM_RATIO;
    const Vector3 currentDistance = Vector3::Lerp(m_distance, zoomedDistance, m_zoomBlend);

    // 回転応じた追従オフセット
    const Vector3 followOffset = Vector3::Transform(currentDistance, targetRotation);
    // カメラの位置のオフセットを加算
    const Vector3 cameraOffsetPosition = targetPosition + followOffset;

    // バネ変位
    const Vector3 displacement = cameraOffsetPosition - m_transform->GetLocalPosition();

    // バネ力
    Vector3 spring = displacement * SPRING_STIFFNESS;
    // 減衰力
    Vector3 damping = m_velocity * SPRING_DAMPING;

    // 加速度を計算
    Vector3 acceleration = spring - damping;

    // 速度を更新
    m_velocity += acceleration * elapsedTime;

    // カメラの座標を更新
    m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);
    // カメラ注視点を更新
    m_transform->SetLocalScale(targetPosition);
   
    // ビュー行列更新
    CalculateViewMatrix();
}


DirectX::SimpleMath::Matrix FollowCamera::CalculateViewMatrix()
{
    DirectX::SimpleMath::Vector3 eye    = m_transform->GetLocalPosition();
    DirectX::SimpleMath::Vector3 target = m_transform->GetLocalScale();
    DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

    m_viewMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(eye, target, up);

    return m_viewMatrix;
}