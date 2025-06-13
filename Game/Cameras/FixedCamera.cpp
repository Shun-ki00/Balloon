#include "pch.h"
#include "Game/Cameras/FixedCamera.h"
#include "Game/Transform/Transform.h"


FixedCamera::FixedCamera(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation)
{
    // ��]�����ƂɃ^�[�Q�b�g���W���v�Z����
    DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Forward;
    // �N�H�[�^�j�I����K��
    target = DirectX::SimpleMath::Vector3::Transform(target, rotation);
    // ���W�����Z
    target = target + position;

    m_transform = std::make_unique<Transform>();
    m_transform->Initialize(position, rotation, target);
}


void FixedCamera::Initialize()
{
    // �s��v�Z��������
    this->CalculateViewMatrix();
}


void FixedCamera::Update(const float& elapsedTime)
{
    // �Œ�J�����̂��ߍX�V�����͍s��Ȃ�
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