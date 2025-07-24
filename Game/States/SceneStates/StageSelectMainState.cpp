#include "pch.h"
#include "Game/States/SceneStates/StageSelectMainState.h"
#include "Game/Message/Message.h"
#include "Framework/InputManager.h"
#include "Framework/SceneManager.h"

StageSelectMainState::StageSelectMainState()
{
	// �C���X�^���X���擾����
	m_inputManager = InputManager::GetInstance();
}


void StageSelectMainState::Initialize()
{

}


void StageSelectMainState::PreUpdate()
{

}


void StageSelectMainState::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	if (m_inputManager->OnKeyDown(InputManager::Keys::Right))
	{
		ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::STAGE_SELECT_UI, { Message::MessageID::BUTTON_BACK });
	}
	if (m_inputManager->OnKeyDown(InputManager::Keys::Left))
	{
		ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::STAGE_SELECT_UI, { Message::MessageID::BUTTON_NEXT });
	}

	if (m_inputManager->OnKeyDown(InputManager::Keys::Escape))
	{	
		// �V�[���Ƀ��b�Z�[�W���M
		SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_TITLE_SCENE);
	}

	// �X�y�[�X�Ŏ��̃V�[����
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// �V�[���Ƀ��b�Z�[�W���M
		SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_PLAY_SCENE);
	}
}

void StageSelectMainState::PostUpdate()
{

}


void StageSelectMainState::Finalize()
{

}