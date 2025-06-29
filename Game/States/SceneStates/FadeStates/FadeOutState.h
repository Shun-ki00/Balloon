#pragma once
#include "Interface/IState.h"
#include "Framework/SceneManager.h"

class ObjectMessenger;

class FadeOutState : public IState
{
public:
	// �R���X�g���N�^
	FadeOutState(Message::MessageData data);
	// �f�X�g���N�^
	~FadeOutState() = default;
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

	// �I�u�W�F�N�g���b�Z���W���[
	ObjectMessenger* m_objectMessenger;

	// �t�F�[�h�I�u�W�F�N�g�ԍ�
	int m_fadeObjectNumber;

	// ���b�Z�[�W�f�[�^
	Message::MessageData m_messageData;

};