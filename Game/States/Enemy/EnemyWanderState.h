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

public:

	// �G�I�u�W�F�N�g
	Object* m_object;


};