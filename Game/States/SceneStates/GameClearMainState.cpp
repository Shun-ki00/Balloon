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

	if (m_inputManager->OnKeyDown(InputManager::Keys::Escape))
	{

		// メッセージボックスの表示
		int result = MessageBox(NULL, L"ゲームを終了しますか？", L"BALLOON", MB_YESNO | MB_ICONQUESTION);

		// 「はい」または「いいえ」の選択に応じてフルスクリーン設定
		if (result == IDYES) {
			// はいが押されたときのみ、シーン遷移メッセージ送信
			SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_EXIT_GAME);
		}
	}


	// スペースで次のシーンへ
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// シーンにメッセージ送信
		SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_MENU_SCENE);
	}
}

void GameClearMainState::PostUpdate()
{

}


void GameClearMainState::Finalize()
{

}