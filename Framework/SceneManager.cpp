// ============================================
// 
// �t�@�C����: SceneManager.cpp
// �T�v: �e�V�[�����Ǘ�����N���X�i�V���O���g���j
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Framework/SceneManager.h"
#include "Framework/CommonResources.h"
#include "Game/Game.h"
#include "Game/Node/Root.h"
#include "Game/Message/KeyboardMessenger.h"
#include "Game/Message/ObjectMessenger.h"
#include "Framework/Tween/TweenManager.h"

// �e�V�[��
#include "Game/Scenes/DebugScene.h"
#include "Game/Scenes/TitleScene.h"
#include "Game/Scenes/GameClearScene.h"
#include "Game/Scenes/PlayScene.h"
#include "Game/Scenes/GameOverScene.h"
#include "Game/Scenes/StageSelectScene.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager()
	:
	m_currentScene{},
	m_nextScene{},
	m_isChange{},
	m_future{}
{
	// ���L���\�[�X�̃C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// ����������
/// </summary>
void SceneManager::Initialize()
{
	// �A�^�b�`�J�n
	Root::GetInstance()->Begin();
	m_commonResources->GetRenderer()->Begin();
	ObjectMessenger::GetInstance()->Begin();
	KeyboardMessenger::GetInstance()->Begin();

	// �����V�[���̍쐬
	m_currentScene = std::make_unique<TitleScene>();
	// �����V�[���̏�����
	m_currentScene->Initialize();

	// �A�^�b�`�I��
	Root::GetInstance()->End();
	m_commonResources->GetRenderer()->End();
	ObjectMessenger::GetInstance()->End();
	KeyboardMessenger::GetInstance()->End();

	// �����V�[���̃X�^�[�g����
	m_currentScene->Start();

	m_isChange = false;
	m_isExitGame = false;
}

/// <summary>
/// �X�V����
/// </summary>
void SceneManager::Update()
{
	if (m_currentScene != nullptr)
		m_currentScene->Update();
}
/// <summary>
/// �`�揈��
/// </summary>
void SceneManager::Render()
{
	if (m_currentScene != nullptr)
		m_currentScene->Render();
}
/// <summary>
/// �I������
/// </summary>
void SceneManager::Finalize()
{
	if (m_currentScene != nullptr)
		m_currentScene->Finalize();
}

void SceneManager::Dispatch(Message::SceneMessageID messageID)
{
	m_currentScene->OnSceneMessegeAccepted(messageID);
}

/// <summary>
/// �V�[���؂�ւ�
/// </summary>
bool SceneManager::CheckChageScene()
{
	// �Q�[���I���̏ꍇ
	if (m_isExitGame)
	{
		return false;
	}

	// �V�[���؂�ւ��t���O���I���̏ꍇ
	if (m_isChange)
	{
		// �O�̃V�[���̏I���������s��
		m_currentScene->Finalize();

		// �A�^�b�`�I��
		Root::GetInstance()->End();
		CommonResources::GetInstance()->GetRenderer()->End();
		ObjectMessenger::GetInstance()->End();
		KeyboardMessenger::GetInstance()->End();

		TweenManager::GetInstance()->Stop();
		
		// �O�̃V�[�����폜����
		m_currentScene.reset();

		// ���̃V�[��������
		m_currentScene = std::move(m_nextScene);

		// ���̃V�[���X�^�[�g����
		m_currentScene->Start();

		// �t���O����������
		m_isChange = false;
	}

	return true;
}