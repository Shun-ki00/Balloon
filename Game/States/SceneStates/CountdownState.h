#pragma once
#include "Interface/IState.h"

class InputManager;
class IScene;

class CountdownState : public IState
{
public:
	// �R���X�g���N�^
	CountdownState();
	// �f�X�g���N�^
	~CountdownState() = default;
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

};