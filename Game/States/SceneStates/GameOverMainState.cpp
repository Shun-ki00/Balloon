#include "pch.h"
#include "Game/States/SceneStates/GameOverMainState.h"
#include "Game/Message/Message.h"
#include "Framework/InputManager.h"
#include "Framework/SceneManager.h"

GameOverMainState::GameOverMainState()
{
	// �C���X�^���X���擾����
	m_inputManager = InputManager::GetInstance();
}


void GameOverMainState::Initialize()
{

}


void GameOverMainState::PreUpdate()
{

}


void GameOverMainState::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	if (m_inputManager->OnKeyDown(InputManager::Keys::Escape))
	{

		// ���b�Z�[�W�{�b�N�X�̕\��
		int result = MessageBox(NULL, L"�Q�[�����I�����܂����H", L"BALLOON", MB_YESNO | MB_ICONQUESTION);

		// �u�͂��v�܂��́u�������v�̑I���ɉ����ăt���X�N���[���ݒ�
		if (result == IDYES) {
			// �͂��������ꂽ�Ƃ��̂݁A�V�[���J�ڃ��b�Z�[�W���M
			SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_EXIT_GAME);
		}
	}


	// �X�y�[�X�Ŏ��̃V�[����
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// �V�[���Ƀ��b�Z�[�W���M
		SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_MENU_SCENE);
	}
}

void GameOverMainState::PostUpdate()
{

}


void GameOverMainState::Finalize()
{

}