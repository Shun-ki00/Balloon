#include "pch.h"
#include "Game/States/SceneStates/FadeStates/FadeOutState.h"
#include "Game/Message/ObjectMessenger.h"


FadeOutState::FadeOutState(int fadeObjectNumber)
{
	// インスタンスを取得する
	m_objectMessenger = ObjectMessenger::GetInstance();

	// オブジェクト番号取得する
	m_fadeObjectNumber = fadeObjectNumber;
}


void FadeOutState::Initialize()
{
	// メッセージデータの作成
	m_messageData =
	{
		Message::MessageID::FADE_OUT,
		0,
		1.0f,
		false
	};
}


void FadeOutState::PreUpdate()
{
	// フェードアウトを行う
	m_objectMessenger->Dispatch(IObject::ObjectID::FADE, m_messageData);
}


void FadeOutState::Update(const float& elapsedTime)
{

}

void FadeOutState::PostUpdate()
{

}


void FadeOutState::Finalize()
{

}