#include "pch.h"
#include "Game/States/SceneStates/FadeStates/FadeOutState.h"
#include "Game/Message/ObjectMessenger.h"


FadeOutState::FadeOutState(Message::MessageData data)
{
	// インスタンスを取得する
	m_objectMessenger = ObjectMessenger::GetInstance();

	// メッセージデータ設定
	m_messageData = data;
	
}


void FadeOutState::Initialize()
{

}


void FadeOutState::PreUpdate()
{
	// BGMを停止する
	AudioManager::GetInstance()->StopBgm(1.0f);
	// 再生中のSEを停止する
	AudioManager::GetInstance()->StopSE();

	// フェードアウトを行う
	m_objectMessenger->Dispatch(IObject::ObjectID::FADE, m_messageData);
}


void FadeOutState::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
}

void FadeOutState::PostUpdate()
{

}


void FadeOutState::Finalize()
{

}