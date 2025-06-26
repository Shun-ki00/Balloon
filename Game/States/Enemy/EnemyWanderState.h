#pragma once
#pragma once
#include "Interface/IState.h"

class Transform;
class Object;


class EnemyWanderState : public IState
{

public:
	// �R���X�g���N�^
	EnemyWanderState(Object* object);
	// �f�X�g���N�^
	~EnemyWanderState() = default;
	// ����������
	void Initialize() override;
	// ���O�X�V����
	void PreUpdate() override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// ����X�V����
	void PostUpdate() override;
	// �㏈�����s��
	void Finalize() override;

private:

	// ��]�p
	static const float MIN_ROTATION_ANGLE;
	static const float MAX_ROTATION_ANGLE;
	// ��]���x
	static const float ROTATION_DURATION;
	// �ړ�����
	static const float MIN_MOVE_DISTANCE;
	static const float MAX_MOVE_DISTANCE;
	// �ړ����x
	static const float MIN_MOVE_SPEED;
	static const float MAX_MOVE_SPEED;

public:

	// �G�I�u�W�F�N�g
	Object* m_object;

	// �҂����Ԃ̏��
	bool m_isWait;

	// ���D��c��܂��邩
	bool m_isFlate;

	// �o�ߎ���
	float m_timer;
	// �ҋ@����
	float m_waitTime;
	
	// ���������p�x
	float m_targetAngle;
	// ��]���x
	float m_rotationSpeed;
	

	// �ړ����x
	float m_moveSpeed;
	// �ړ�����
	float m_moveDistance;
	// �i�񂾋���
	float m_moved;
};