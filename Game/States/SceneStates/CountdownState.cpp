#include "pch.h"
#include "Game/States/SceneStates/CountdownState.h"
#include "Game/Message/Message.h"
#include "Framework/InputManager.h"
#include "Framework/SceneManager.h"

CountdownState::CountdownState()
{
}


void CountdownState::Initialize()
{

}


void CountdownState::PreUpdate()
{
	// カウントダウンアニメーション開始
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::COUNTDOWN_UI, { Message::MessageID::PLAY_COUNTDOWN_ANIMATION });
}


void CountdownState::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
}

void CountdownState::PostUpdate()
{
	// 移動可能にする
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER, { Message::MessageID::FIXED ,0,0.0f ,false});
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::ENEMY, { Message::MessageID::FIXED,0,0.0f ,false });
	// タイマー開始　メッセージ送信
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::TIME_NUMBER_UI, { Message::MessageID::START_TIME });
}


void CountdownState::Finalize()
{

}