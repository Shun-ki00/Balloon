#pragma once
#include "Interface/ICamera.h"
#include "Framework/Tween/Tween.h"

class Transform;

class BlendingCamera : public ICamera
{

public:
	// Transform���擾����
	Transform* GetTransform() const override { return m_transform.get(); }
	// �r���[�s����擾����
	DirectX::SimpleMath::Matrix GetViewMatrix() const override { return m_viewMatrix; }

	// �J�ڂ��J�n����
	void StartBlending(Transform* currentCamera, Transform* nextCamera, float t , Tween::EasingType easingType);
	// �J�ڒ����ǂ����擾����
	bool GetisBlending() const { return m_isBlending; }

public:
	// �R���X�g���N�^
	BlendingCamera();
	// �f�X�g���N�^
	~BlendingCamera() = default;

	// ����������
	void Initialize();
	// �X�V����
	void Update(const float& elapsedTime);
	// �r���[�s��̍쐬
	DirectX::SimpleMath::Matrix CalculateViewMatrix();

private:

	// �J�ڒ����ǂ���
	bool m_isBlending;

	// �J�ڎ���
	float m_blendingTime;

	// �C�[�W���O
	Tween::EasingType m_easingType;

	// Transform
	std::unique_ptr<Transform> m_transform;

	// �J�ڂ���J������Transform
	Transform* m_nextCaemraTransform;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_viewMatrix;


	// ���݂̎���
	float m_elapsed;
	// �J�n�J�������W
	DirectX::SimpleMath::Vector3 m_startPosition;
	// �J�n�J�����^�[�Q�b�g���W
	DirectX::SimpleMath::Vector3 m_startTargetPosition;
};
