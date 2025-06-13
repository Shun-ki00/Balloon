#include "pch.h"
#include "Game/States/SceneStates/FadeStates/FadeInState.h"
#include "Game/Message/ObjectMessenger.h"


FadeInState::FadeInState(int fadeObjectNumber)
{
	// インスタンスを取得する
	m_objectMessenger = ObjectMessenger::GetInstance();

	// オブジェクト番号取得する
	m_fadeObjectNumber = fadeObjectNumber;
}


void FadeInState::Initialize()
{
	// メッセージデータの作成
	m_messageData =
	{
		Message::MessageID::FADE_IN,
		0,
		1.0f,
		false
	};
}


void FadeInState::PreUpdate()
{
	// フェードインを行う
	m_objectMessenger->Dispatch(IObject::ObjectID::FADE, m_fadeObjectNumber, m_messageData);
}


void FadeInState::Update(const float& elapsedTime)
{

}

void FadeInState::PostUpdate()
{

}


void FadeInState::Finalize()
{

}