#pragma once

class AudioManager;
class FloatForceBehavior;
class HpController;

class BalloonScaleController
{
public:

	// ���D�̑傫�����擾����
	float GetBalloonScale() const { return m_balloonScale; }

public:

	// �R���X�g���N�^
	BalloonScaleController(HpController* hpController, FloatForceBehavior* floatForceBehavior);
	// �f�X�g���N�^
	~BalloonScaleController() = default;

	// ����������
	void Initialize();
	// �X�V����
	void Update(const float& elapsedTime);

	// �I��
	void On();
	// �I�t
	void Off();

private:

	AudioManager* m_audioManager;

	// �X�e�A�����O�r�w�C�r�A
	FloatForceBehavior* m_floatForceBehavior;
	// HP�R���g���[���[
	HpController* m_hpController;

	// ���D�̑傫��
	float m_balloonScale;
	// ���D��c��܂��Ă��邩�ǂ���
	bool m_isBalloonInflating;

	int m_balloonBlowUpIndex;

	int m_balloonReleaseAirIndex; 

};