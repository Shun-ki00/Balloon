#include "pch.h"
#include "Game/Cameras/FollowCamera.h"
#include "Game/Transform/Transform.h"


FollowCamera::FollowCamera(Transform* target, DirectX::SimpleMath::Vector3 distance)
{
   // ������ݒ�
    m_distance = distance;
    // �^�[�Q�b�g��Transfom��ݒ�
    m_targetTransform = target;
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
    DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Backward;
    DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Zero;

    // �^�[�Q�b�g�̍��W��ݒ肷��
    target = m_targetTransform->GetLocalPosition();
    // �^�[�Q�b�g�̉�]��K������
    position = DirectX::SimpleMath::Vector3::Transform(m_distance, m_targetTransform->GetLocalRotation());
    // �J�����̍��W������
    position += target;

    m_transform->SetLocalPosition(position);
    m_transform->SetLocalScale(target);
    
    // �r���[�s����v�Z
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