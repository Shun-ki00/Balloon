#include "pch.h"
#include "Game/States/SceneStates/PlayMainState.h"
#include "Game/Message/Message.h"
#include "Framework/InputManager.h"
#include "Framework/SceneManager.h"

PlayMainState::PlayMainState()
{
	// �C���X�^���X���擾����
	m_inputManager = InputManager::GetInstance();
}


void PlayMainState::Initialize()
{

}


void PlayMainState::PreUpdate()
{

}


void PlayMainState::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

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

void PlayMainState::PostUpdate()
{
	// �ړ��\�ɂ���
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER, { Message::MessageID::FIXED ,0,0.0f ,true });
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::ENEMY, { Message::MessageID::FIXED,0,0.0f ,true });
}


void PlayMainState::Finalize()
{

}