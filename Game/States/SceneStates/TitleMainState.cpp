#include "pch.h"
#include "Game/States/SceneStates/TitleMainState.h"
#include "Game/Message/Message.h"
#include "Framework/InputManager.h"
#include "Framework/SceneManager.h"

TitleMainState::TitleMainState()
{
	// インスタンスを取得する
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
	// スペースで次のシーンへ
	if (m_inputManager->OnKeyDown(InputManager::Keys::Space))
	{
		// シーンにメッセージ送信
		SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_MENU_SCENE);
	}
}

void TitleMainState::PostUpdate()
{

}


void TitleMainState::Finalize()
{

}