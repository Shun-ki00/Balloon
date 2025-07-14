// ============================================
// 
// �t�@�C����: PlayScene.h
// �T�v: PlayScene.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IScene.h"


class CommonResources;
class DebugCamera;
class Root;
class Parameters;
class WindBehavior;
class ParticleEmitter;
class FadeInState;
class CountdownState;
class PlayMainState;
class FadeOutState;

class PlayScene : public IScene
{
public:
	// �R���X�g���N�^
	PlayScene();
	// �f�X�g���N�^
	~PlayScene();

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
	// ���b�Z�[�W���󂯎��
	void OnSceneMessegeAccepted(Message::SceneMessageID messageID) override;

private:

	// �X�e�[�g���쐬
	void CreateState();

private:

	// �p�����[�^�[
	Parameters* m_parameters;
	// ���L���\�[�X
	CommonResources* m_commonResources;
	// ���[�g
	Root* m_root;

	// �f�o�b�O�J�����Ŏ���
	std::unique_ptr<DebugCamera> m_debugCamera;

	// ���݂̏��
	IState* m_currentState;

	// �t�F�[�h�C���X�e�[�g
	std::unique_ptr<FadeInState> m_fadeInState;
	// �J�E���g�_�E���X�e�[�g
	std::unique_ptr<CountdownState> m_countdownState;
	// ���C���X�e�[�g
	std::unique_ptr<PlayMainState> m_playMainState;
	// �t�F�[�h�A�E�g�X�e�[�g
	std::unique_ptr<FadeOutState> m_fadeOutState;
};