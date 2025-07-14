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

	// �V�[���ύX���b�Z�[�W���M
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::RESULT_BUTTON_SYSTEM,4000, { Message::MessageID::CHANGE_SCENE });
	}
}

void GameOverMainState::PostUpdate()
{

}


void GameOverMainState::Finalize()
{

}