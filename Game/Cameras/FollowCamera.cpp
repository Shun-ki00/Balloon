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
   // ������ݒ�
    m_distance = distance;
    // �^�[�Q�b�g�̃I�u�W�F�N�g��ݒ�
    m_target = target;
}


void FollowCamera::Initialize()
{
    // Transform���쐬
    m_transform = std::make_unique<Transform>();
    m_transform->Initialize(
        DirectX::SimpleMath::Vector3::Zero,
        DirectX::SimpleMath::Quaternion::Identity,
        DirectX::SimpleMath::Vector3::Zero);

}


void FollowCamera::Update(const float& elapsedTime)
{
    using namespace DirectX::SimpleMath;

    // �^�[�Q�b�g�̏����擾
    Transform* targetTransform = m_target->GetTransform();
    Vector3 targetPosition     = targetTransform->GetLocalPosition();
    Quaternion targetRotation  = targetTransform->GetLocalRotation();
    Vector3 targetVelocity     = m_target->GetVelocity();

    // �^�[�Q�b�g�̑��x���擾
    const float currentSpeed = targetVelocity.Length();

    // �Y�[������
    const float desiredZoom = (currentSpeed > SPEED_TO_ZOOM_THRESHOLD) ? 1.0f : 0.0f;

    // �Y�[����Ԓl�̍X�V
    m_zoomBlend = std::clamp(
        std::lerp(m_zoomBlend, desiredZoom, elapsedTime * ZOOM_INTERPOLATION_SPEED), 0.0f, 1.0f
    );

    // �Y�[���������v�Z
    const Vector3 zoomedDistance = m_distance * ZOOM_RATIO;
    const Vector3 currentDistance = Vector3::Lerp(m_distance, zoomedDistance, m_zoomBlend);

    // ��]�������Ǐ]�I�t�Z�b�g
    const Vector3 followOffset = Vector3::Transform(currentDistance, targetRotation);
    // �J�����̈ʒu�̃I�t�Z�b�g�����Z
    const Vector3 cameraOffsetPosition = targetPosition + followOffset;

    // �o�l�ψ�
    const Vector3 displacement = cameraOffsetPosition - m_transform->GetLocalPosition();

    // �o�l��
    Vector3 spring = displacement * SPRING_STIFFNESS;
    // ������
    Vector3 damping = m_velocity * SPRING_DAMPING;

    // �����x���v�Z
    Vector3 acceleration = spring - damping;

    // ���x���X�V
    m_velocity += acceleration * elapsedTime;

    // �J�����̍��W���X�V
    m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);
    // �J���������_���X�V
    m_transform->SetLocalScale(targetPosition);
   
    // �r���[�s��X�V
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