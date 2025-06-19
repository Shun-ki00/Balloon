#pragma once


class HpController
{
public:

	// HP���擾����
	float GetHp() const { return m_hp; }

public:

	// �R���X�g���N�^
	HpController();
	// �f�X�g���N�^
	~HpController() = default;

	// ����������
	void Initialize();
	// �X�V����
	void Update(const float& elapsedTime);

public:

	// HP�����炷
	bool HpReduction(const float& amount);

private:

	float m_hp;
	float m_maxHp;
	float m_targetHp;
	float m_reduceSpeed;
	bool  m_isReducing;

	bool m_isRecovering;
	float m_recoverDelayTimer;
	float m_recoverDelay;           // �񕜊J�n�܂ł̒x��
	float m_recoverSpeed;          // ���b�̉񕜑��x

};