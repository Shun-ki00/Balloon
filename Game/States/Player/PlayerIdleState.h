#pragma once
#include "Interface/IState.h"

class PlayerIdleState : public IState
{
public:
	// �R���X�g���N�^
	PlayerIdleState();
	// �f�X�g���N�^
	~PlayerIdleState() = default;
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




};