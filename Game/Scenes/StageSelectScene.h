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
class SceneManager;
// �X�e�[�g
class FadeInState;
class StageSelectMainState;
class FadeOutState;

class StageSelectScene : public IScene
{
public:
	// �R���X�g���N�^
	StageSelectScene();
	// �f�X�g���N�^
	~StageSelectScene();

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

	// �X�e�[�g�̍쐬
	void CreateStates();

private:

	// �t�F�[�h�I�u�W�F�N�g�ԍ�
	static const int FADE_OBJECT_NUMBER;
	
private:

	// �p�����[�^�[
	Parameters* m_parameters;
	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �V�[���}�l�[�W���[
	SceneManager* m_sceneManager;


	// ���݂̏��
	IState* m_currentState;

	// �t�F�[�h�C���X�e�[�g
	std::unique_ptr<FadeInState> m_fadeInState;
	// �X�e�[�W�Z���N�g�V�[�����C���X�e�[�g
	std::unique_ptr<StageSelectMainState> m_stageSelectMainState;
	// �t�F�[�h�A�E�g�X�e�[�g
	std::unique_ptr<FadeOutState> m_fadeOutState;

	// ���[�g
	Root* m_root;
};