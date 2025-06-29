// ============================================
// 
// �t�@�C����: SceneManager.h
// �T�v: SceneManager.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include <future>
#include "Interface/IScene.h"
#include "Game/Node/Root.h"
#include "Framework/CommonResources.h"
#include "Framework/Renderer.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Message/KeyboardMessenger.h"
#include "Game/Visitor/CollisionVisitor.h"


class IScene;

class SceneManager
{
public:

	// �X�e�[�W�ԍ����擾
	int GetStageNumber() const { return m_stageNumber; }
	// �X�e�[�W�ԍ���ݒ�
	void GetStageNumber(const int& number) { m_stageNumber = number; }

public:
	// �����t���[���̎��ɃV�[����ύX����
	void ChageScene() { m_isChange = true; }
	// �`�F�b�N�`�F���W�V�[��
	bool CheckChageScene();
	// �Q�[���I���t���O��ݒ�
	void SetIsGameExit() { m_isExitGame = true; }

	// �Q�[���I���t���O���擾����
	bool GetIsGameExit() const { return m_isExitGame; }

public:
	
	// �V�[����񓯊��ŏ���
	template <typename T>
	void PrepareScene()
	{
		CollisionVisitor::GetInstance()->Clear();

		// �񓯊��^�X�N�ŃV�[��������
		m_future = std::async(std::launch::async, [this]() 
		{
			// �V�[���̍쐬
			m_nextScene = std::make_unique<T>();
			// ���[�g�̃m�[�h�A�^�b�`����
			Root::GetInstance()->Begin();
			// �`��I�u�W�F�N�g�̃A�^�b�`������
			CommonResources::GetInstance()->GetRenderer()->Begin();
			// �I�u�W�F�N�g���b�Z���W���[�̃A�^�b�`������
			ObjectMessenger::GetInstance()->Begin();
			// �L�[�{�[�h���b�Z���W���[�̃A�^�b�`������
			KeyboardMessenger::GetInstance()->Begin();

			// �V�[���̏������������s��
			m_nextScene->Initialize();
		});
	}

private:
	//	�R���X�g���N�^
	SceneManager();
	//	�f�X�g���N�^
	~SceneManager() = default;
public:
	SceneManager(const SceneManager&) = delete;             // �R�s�[�֎~
	SceneManager& operator=(const SceneManager&) = delete;  // �R�s�[����֎~
	SceneManager(const SceneManager&&) = delete;            // ���[�u�֎~
	SceneManager& operator=(const SceneManager&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}

public:
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�揈��
	void Render();
	// �I������
	void Finalize();

	void Dispatch(Message::SceneMessageID messageID);

private:

	// ���L���\�[�X
	CommonResources* m_commonResources;
	
	// �V�[��
	std::unique_ptr<IScene> m_currentScene;
	// ���̃V�[��
	std::unique_ptr<IScene> m_nextScene;

	// �V�[���؂�ւ��t���O
	bool m_isChange;

	// �񓯊��^�X�N�Ǘ��p
	std::future<void> m_future;

	// �Q�[���I���t���O
	bool m_isExitGame;

	// �X�e�[�W�ԍ�
	int m_stageNumber;
};