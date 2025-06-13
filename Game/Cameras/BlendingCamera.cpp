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

    // ���݂̎��Ԃ��X�V����
    m_elapsed += elapsedTime;
    
    // �A�j���[�V�����̐i�s�x���v�Z�i0.0 �` 1.0 �ɐ��K���j
    float t = m_elapsed  / m_blendingTime;
    // t �� 1.0 �ɃN�����v�i��Ԃ̏���𒴂��Ȃ��悤�ɂ���j
    if (t > 1.0f) t = 1.0f;

    // �C�[�W���O��K�p
    float easeT = Tween::EasingFunction(m_easingType, t);

    // �ړ����� (DoMove)
    m_transform->SetLocalPosition(
        DirectX::SimpleMath::Vector3::Lerp(m_startPosition, m_nextCaemraTransform->GetLocalPosition(), easeT));
    // ��]���� (DoRotation)
    //m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Slerp(m_startRotation, m_endRotation, easeT));
    // �X�P�[������ (DoScale)
    m_transform->SetLocalScale(
        DirectX::SimpleMath::Vector3::Lerp(m_startTargetPosition, m_nextCaemraTransform->GetLocalScale(), easeT));

    // �J�ڂ��I��������
    if (t >= 1.0f)
    {
        // �J�����V�X�e���ɏI���̃��b�Z�[�W��ʒm����

        // �I��
        m_isBlending = false;

        // ���l�̃��Z�b�g
        m_startPosition       = DirectX::SimpleMath::Vector3::Zero;
        m_startTargetPosition = DirectX::SimpleMath::Vector3::Zero;
        m_easingType          = Tween::EasingType::Linear;
        m_elapsed             = 0.0f;
        m_blendingTime        = 0.0f;
    }

}


void BlendingCamera::StartBlending(Transform* currentCamera, Transform* nextCamera, float t, Tween::EasingType easingType)
{
	// �J�ڒ��ɕύX
	m_isBlending = true;

	// �J�ڂ���J������Transform��ݒ�
	m_nextCaemraTransform = nextCamera;

	// �J�ڎ��Ԃ�ݒ�
	m_blendingTime = t;

	// �C�[�W���O�̐ݒ�
	m_easingType = easingType;

    // �J�n���W��ݒ�
    m_startPosition = currentCamera->GetLocalPosition();
    // �J�n�^�[�Q�b�g���W��ݒ�
    m_startTargetPosition = currentCamera->GetLocalScale();

    // �o�ߎ��Ԃ����Z�b�g
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