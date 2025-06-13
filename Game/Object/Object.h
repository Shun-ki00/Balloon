#pragma once
#include "Interface/IObject.h"
#include "Interface/IState.h"

class Object : public IObject
{
public:
	// �I�u�W�F�N�g���J�E���g�A�b�v����
	static int CountUpNumber();
	// ���݂̃I�u�W�F�N�g�J�E���g���擾
	static int ResetNumber();

	// ��Ԃ��擾����
	IState* GetState() const { return m_currentState; }
	// ��Ԃ�ݒ肷��
	void SetState(IState* state) { m_currentState = state; }
	// ���݂̏�Ԃ�ύX����
	void ChangeState(IState* state)
	{
		// �V�K�̏�ԑJ�ڑO�Ɏ���X�V���s��
		m_currentState->PostUpdate();
		// �V�K�̏�Ԃ����݂̏�Ԃɐݒ肷��
		m_currentState = state;
		// �V�K�̏�ԑJ�ڌ�Ɏ��O�X�V���s��
		m_currentState->PreUpdate();
	}

	// ���x���擾����
	virtual DirectX::SimpleMath::Vector3& GetVelocity() = 0;
	// ���x��ݒ肷��
	virtual void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) = 0;
	// �����x���擾����
	virtual DirectX::SimpleMath::Vector3& GetAcceralation() = 0;
	// �����x��ݒ肷��
	virtual void SetAcceralation(const DirectX::SimpleMath::Vector3& acceralation) = 0;

	// ��]����Ƃ��̍ő呬�x
	float GetMaxTurnRate() const { return m_maxTurnRate; }
	// �ő�ړ����x
	float GetMaxSpeed() const { return m_maxSpeed; }
	// �ő��
	float GetMaxForce() const { return m_maxForce; }
	// ����
	float GetMass() const { return m_mass; }

public:

	// �R���X�g���N�^
	Object(const float& m_maxTurnRate, const float& m_maxSpeed, const float& m_maxForce, const float& m_mass);
	// �f�X�g���N�^
	 ~Object() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// �㏈�����s��
	void Finalize() override;

private:
	// �I�u�W�F�N�g�ԍ�
	static int s_objectNumber;
	// ���݂̏��
	IState* m_currentState;
	// ���݂̃��b�Z�[�W
	Message m_currentMessage;

	// ��]����Ƃ��̍ő呬�x
	float m_maxTurnRate;
	// �ő�ړ����x
	float m_maxSpeed;
	// �ő��
	float m_maxForce;
	// �v���C���[�̎���
	float m_mass;
};