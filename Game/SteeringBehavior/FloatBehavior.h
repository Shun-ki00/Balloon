// ============================================
// 
// �t�@�C����: FloatBehavior.h
// �T�v: FloatBehavior.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/ISteeringBehavior.h"


class FloatBehavior : public ISteeringBehavior
{
public:

	// �r�w�C�r�A��L���ɂ���
	void On() override;
	// �r�w�C�r�A�𖳌��ɂ���
	void Off() override;

	// �X�e�A�����O�͂��v�Z����
	DirectX::SimpleMath::Vector3 Calculate() override;

	// �R���X�g���N�^
	FloatBehavior();
	// �f�X�g���N�^
	~FloatBehavior() override = default;

private:

	// �h��Ă��邩�̃t���O
	bool m_isFloat;

	// �h��鍂���̍ő�l
	float m_amplitude;

	// �h���X�s�[�h
	float m_floatSpeed;

	// �h������
	DirectX::SimpleMath::Vector3 m_direction;

	// �o�ߎ���
	float m_elapsedTime;

};