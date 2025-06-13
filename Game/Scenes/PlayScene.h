// ============================================
// 
// �t�@�C����: DebugScene.h
// �T�v: DebugScene.cpp�̃w�b�_�[�t�@�C��
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
	// �����蔻�胁�b�Z�[�W���󂯎��
	void OnSceneMessegeAccepted(Message::SceneMessageID messageID) override;

private:

	// �p�����[�^�[
	Parameters* m_parameters;
	// ���L���\�[�X
	CommonResources* m_commonResources;

	// �f�o�b�O�J�����Ŏ���
	std::unique_ptr<DebugCamera> m_debugCamera;

	// ���[�g
	Root* m_root;
};