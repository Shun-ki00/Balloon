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

class DebugScene : public IScene
{
public:
	// �R���X�g���N�^
	DebugScene();
	// �f�X�g���N�^
	~DebugScene();

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
	// �X�e�A�����O�r�w�C�r�A
	WindBehavior* m_steeringBehavior;

	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �f�o�b�O�J�����Ŏ���
	std::unique_ptr<DebugCamera> m_debugCamera;

	// �v���C���[��ǉ�
	Root* m_root;


	// �p�[�e�B�N��������
	std::unique_ptr< ParticleEmitter> m_emitter;
};