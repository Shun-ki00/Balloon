#include "pch.h"
#include "Game/States/SceneStates/StageSelectMainState.h"
#include "Game/Message/Message.h"
#include "Framework/InputManager.h"
#include "Framework/SceneManager.h"

StageSelectMainState::StageSelectMainState()
{
	// インスタンスを取得する
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

	if (m_inputManager->OnKeyDown(InputManager::Keys::Escape))
	{	
		// シーンにメッセージ送信
		SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_TITLE_SCENE);
	}

	// スペースで次のシーンへ
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// シーンにメッセージ送信
		SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_PLAY_SCENE);
	}
}

void StageSelectMainState::PostUpdate()
{

}


void StageSelectMainState::Finalize()
{

}