#pragma once
#include "Interface/ICamera.h"
#include "Framework/Tween/Tween.h"

class Transform;

class FixedCamera : public ICamera
{

public:
	// Transform���擾����
	Transform* GetTransform() const override { return m_transform.get(); }
	// �r���[�s����擾����
	DirectX::SimpleMath::Matrix GetViewMatrix() const override { return m_viewMatrix; }

public:
	// �R���X�g���N�^
	FixedCamera(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation);
	// �f�X�g���N�^
	~FixedCamera() = default;

	// ����������
	void Initialize();
	// �X�V����
	void Update(const float& elapsedTime);
	// �r���[�s��̍쐬
	DirectX::SimpleMath::Matrix CalculateViewMatrix();

private:

	// Transform
	std::unique_ptr<Transform> m_transform;
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_viewMatrix;
};
