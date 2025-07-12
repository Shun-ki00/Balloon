#pragma once
#include "Interface/ISteeringBehavior.h"
#include "Interface/IObject.h"

class WindBehavior;

class SteeringBehavior
{
public:

	// �X�e�A�����O�r�w�C�r�A���擾����
	ISteeringBehavior* GetSteeringBehavior(BEHAVIOR_TYPE flags);

	// �R���X�g���N�^
	SteeringBehavior();
	// �f�X�g���N�^
	~SteeringBehavior() = default;

	// ����������
	void Initialize();

	// �v�Z�������s��
	DirectX::SimpleMath::Vector3 Calculate(const float& elapsedTime);

	// �X�e�A�����O�r�w�C�r�A���I���ɂ���
	void On(BEHAVIOR_TYPE flag);
	// �X�e�A�����O�r�w�C�r�A���I�t�ɂ���
	void Off(BEHAVIOR_TYPE flag);

	// �ǉ�����
	void Attach(BEHAVIOR_TYPE flags , std::unique_ptr<ISteeringBehavior> steeringBehavior);

private:

	// ���ʂ̃r�w�C�r�A �i���r�w�C�r�A�j
	WindBehavior* m_windBehavior;

	// �X�e�A�����O�r�w�C�r�A
	std::vector<std::pair<BEHAVIOR_TYPE, std::unique_ptr<ISteeringBehavior>>> m_behaviors;

	// �t���O
	uint32_t m_flags;

	// �^�[�Q�b�g�I�u�W�F�N�g
	IObject* m_targetObject;
};