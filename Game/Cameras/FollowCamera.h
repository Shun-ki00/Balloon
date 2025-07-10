#pragma once
#include "Interface/ICamera.h"
#include "Framework/Tween/Tween.h"

class Transform;
class Object;

class FollowCamera : public ICamera
{

private:

	// �Y�[�����邽�߂ɕK�v�ȃ^�[�Q�b�g�̑��x
	static const float SPEED_TO_ZOOM_THRESHOLD;
	// �Y�[�������̕�ԑ��x
	static const float ZOOM_INTERPOLATION_SPEED;
	// �Y�[���{��
	static const float ZOOM_RATIO;

	// �o�l�̍���
	static const float SPRING_STIFFNESS;
	// �����W��
	static const float SPRING_DAMPING;

public:
	// Transform���擾����
	Transform* GetTransform() const override { return m_transform.get(); }
	// �r���[�s����擾����
	DirectX::SimpleMath::Matrix GetViewMatrix() const override { return m_viewMatrix; }

public:
	// �R���X�g���N�^
	FollowCamera(Object* target,DirectX::SimpleMath::Vector3 distance);
	// �f�X�g���N�^
	~FollowCamera() = default;

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

	// �ǔ�����I�u�W�F�N�g
	Object* m_target;
	// �I�t�Z�b�g�l
	DirectX::SimpleMath::Vector3 m_distance;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// �Y�[����Ԃ̕�ԌW��
	float m_zoomBlend;
};
