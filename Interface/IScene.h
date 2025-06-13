// ============================================
// 
// �t�@�C����: IScene.h
// �T�v: �V�[���̃��C�t�T�C�N���Ǘ��Ə�ԑJ�ځE���b�Z�[�W�������`����i�C���^�[�t�F�[�X�j
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IState.h"
#include "Game/Message/Message.h"

class IScene
{
public:
	// �f�X�g���N�^
	virtual ~IScene() = default;

public:
	// ����������
	virtual void Initialize() = 0;
	// �X�^�[�g����
	virtual void Start() = 0;
	// �X�V����
	virtual void Update() = 0;
	// �`�揈��
	virtual void Render() = 0;
	// �I������
	virtual void Finalize() = 0;

	// ���݂̏�Ԃ�ύX����
	virtual void ChangeState(IState* newState) = 0;
	// ���b�Z�[�W���󂯎��
	virtual void OnSceneMessegeAccepted(Message::SceneMessageID messageID) = 0;
};