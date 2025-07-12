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
	FloatBehavior(const float& floatRange,const float& floatCycleSpeed , const float& floatSpeed,
		const DirectX::SimpleMath::Vector3& direction);
	// �f�X�g���N�^
	~FloatBehavior() override = default;

private:


	// �L�����ǂ����̃t���O
	bool m_isActive;
	// �o�ߎ���
	float m_elapsedTime;

	// �h�ꕝ
	float m_floatRange;
	// �����̑���
	float m_floatCycleSpeed;
	// ���x
	float m_floatSpeed;
	// ����
	DirectX::SimpleMath::Vector3 m_direction;
};