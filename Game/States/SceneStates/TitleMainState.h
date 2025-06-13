#pragma once
#include "Interface/IState.h"

class InputManager;
class IScene;

class TitleMainState : public IState
{
public:
	// �R���X�g���N�^
	TitleMainState();
	// �f�X�g���N�^
	~TitleMainState() = default;
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

	// �C���v�b�g�}�l�[�W���[
	InputManager* m_inputManager;

};