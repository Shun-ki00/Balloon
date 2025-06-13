// ============================================
// 
// �t�@�C����: TitleScene.h
// �T�v: TitleScene.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IScene.h"


class CommonResources;
class Root;
class Parameters;
// �X�e�[�g
class FadeInState;
class TitleMainState;
class FadeOutState;

class TitleScene : public IScene
{
public:
	// �R���X�g���N�^
	TitleScene();
	// �f�X�g���N�^
	~TitleScene();

public:
	// ����������
	void Initialize() override;
	// �X�^�[�g����
	void Start()  override;
	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;
	// �I������
	void Finalize() override;

	// �V�[���̃X�e�[�g��ύX����
	void ChangeState(IState* newState) override;
	// �����蔻�胁�b�Z�[�W���󂯎��
	void OnSceneMessegeAccepted(Message::SceneMessageID messageID) override;

private:

	// �I�u�W�F�N�g�̍쐬
	void CreateObjects();
	// UI�I�u�W�F�N�g�̍쐬
	void CreateUiObjects();
	// �J�����̍쐬
	void CreateCameras();
	// �X�e�[�g�̍쐬
	void CreateStates();
	
private:

	// �p�����[�^�[
	Parameters* m_parameters;
	// ���L���\�[�X
	CommonResources* m_commonResources;

	// ���݂̏��
	IState* m_currentState;

	// �t�F�[�h�C���X�e�[�g
	std::unique_ptr<FadeInState> m_fadeInState;
	// �^�C�g���V�[�����C���X�e�[�g
	std::unique_ptr<TitleMainState> m_titleMainState;
	// �t�F�[�h�A�E�g�X�e�[�g
	std::unique_ptr<FadeOutState> m_fadeOutState;

	// ���[�g
	Root* m_root;
};