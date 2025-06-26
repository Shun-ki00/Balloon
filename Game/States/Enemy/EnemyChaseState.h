#pragma once
#include "Interface/IState.h"
#include "Interface/IObject.h"
#include "Game/Object/Object.h"

class Object;
class SeekBehavior;
class SteeringBehavior;

class EnemyChaseState : public IState
{
public:
	// �R���X�g���N�^
	EnemyChaseState(Object* enemy , Object* player , SteeringBehavior* steeringBehavior, SeekBehavior* seekBehavior);
	// �f�X�g���N�^
	~EnemyChaseState() = default;
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
	Object* m_enemy;

	// �v���C���[�I�u�W�F�N�g
	Object* m_player;

	SteeringBehavior* m_steeringBehavior;

	// �X�e�A�����O�r�w�C�r�A
	SeekBehavior* m_seekBehavior;



};