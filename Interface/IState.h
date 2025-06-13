#pragma once


class IState
{
public:
	// �f�X�g���N�^
	virtual ~IState() = default;
	// ����������
	virtual void Initialize() = 0;
	// ���O�X�V����
	virtual void PreUpdate() = 0;
	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;
	// ����X�V����
	virtual void PostUpdate() = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;
};