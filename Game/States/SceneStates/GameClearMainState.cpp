#include "pch.h"
#include "Game/States/SceneStates/GameClearMainState.h"
#include "Game/Message/Message.h"
#include "Framework/InputManager.h"
#include "Framework/SceneManager.h"

GameClearMainState::GameClearMainState()
{
	// インスタンスを取得する
	m_inputManager = InputManager::GetInstance();
}


void GameClearMainState::Initialize()
{

}


void GameClearMainState::PreUpdate()
{

}


void GameClearMainState::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// シーン変更メッセージ送信
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::RESULT_BUTTON_SYSTEM,3000, { Message::MessageID::CHANGE_SCENE });
	}

}

void GameClearMainState::PostUpdate()
{

}


void GameClearMainState::Finalize()
{

}