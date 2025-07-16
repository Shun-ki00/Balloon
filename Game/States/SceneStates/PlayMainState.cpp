#include "pch.h"
#include "Game/States/SceneStates/PlayMainState.h"
#include "Game/Message/Message.h"
#include "Framework/InputManager.h"
#include "Framework/SceneManager.h"
#include "Game/Message/ObjectMessenger.h"

PlayMainState::PlayMainState()
{
	// インスタンスを取得する
	m_inputManager = InputManager::GetInstance();
	m_objectMessenger = ObjectMessenger::GetInstance();
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

	if (!m_objectMessenger->FindObject(IObject::ObjectID::PLAYER)[0]->GetIsActive())
	{
		SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_GAME_OVER_SCENE);

		return;
	}

	auto enemys = m_objectMessenger->FindObject(IObject::ObjectID::ENEMY);

	for (const auto& enemy : enemys)
	{
		if (enemy->GetIsActive()) return;
	}

	SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_GAME_CLEAR_SCENE);
}

void PlayMainState::PostUpdate()
{
	// 移動可能にする
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER, { Message::MessageID::FIXED ,0,0.0f ,true });
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::ENEMY, { Message::MessageID::FIXED,0,0.0f ,true });
}


void PlayMainState::Finalize()
{

}