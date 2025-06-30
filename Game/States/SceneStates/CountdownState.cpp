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
	// �J�E���g�_�E���A�j���[�V�����J�n
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::COUNTDOWN_UI, { Message::MessageID::PLAY_COUNTDOWN_ANIMATION });
}


void CountdownState::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
}

void CountdownState::PostUpdate()
{
	// �ړ��\�ɂ���
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER, { Message::MessageID::FIXED ,0,0.0f ,false});
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::ENEMY, { Message::MessageID::FIXED,0,0.0f ,false });
	// �^�C�}�[�J�n�@���b�Z�[�W���M
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::TIME_NUMBER_UI, { Message::MessageID::START_TIME });
}


void CountdownState::Finalize()
{

}