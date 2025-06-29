#include "pch.h"
#include "Game/States/SceneStates/TitleMainState.h"
#include "Game/Message/Message.h"
#include "Framework/InputManager.h"
#include "Framework/SceneManager.h"

TitleMainState::TitleMainState()
{
	// �C���X�^���X���擾����
	m_inputManager = InputManager::GetInstance();
}


void TitleMainState::Initialize()
{

}


void TitleMainState::PreUpdate()
{

}


void TitleMainState::Update(const float& elapsedTime)
{
	// �X�y�[�X�Ŏ��̃V�[����
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// �V�[���Ƀ��b�Z�[�W���M
		SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_MENU_SCENE);
	}
}

void TitleMainState::PostUpdate()
{

}


void TitleMainState::Finalize()
{

}