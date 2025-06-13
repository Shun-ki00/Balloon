#pragma once
#include "Interface/IObject.h"
#include "Interface/IState.h"

class UIObject : public IObject
{
public:
	// �I�u�W�F�N�g���J�E���g�A�b�v����
	static int CountUpNumber();
	// ���݂̃I�u�W�F�N�g�J�E���g���擾
	static int ResetNumber();
	// ���݂̃I�u�W�F�N�g�ԍ����擾����
	static int GetNumber();

public:

	// �R���X�g���N�^
	UIObject();
	// �f�X�g���N�^
	~UIObject() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// �㏈�����s��
	void Finalize() override;

private:
	// �I�u�W�F�N�g�ԍ�
	static int s_objectNumber;
	// ���݂̃��b�Z�[�W
	Message m_currentMessage;
};