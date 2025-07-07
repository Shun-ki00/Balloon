#include "pch.h"
#include "Game/States/SceneStates/PlayMainState.h"
#include "Game/Message/Message.h"
#include "Framework/InputManager.h"
#include "Framework/SceneManager.h"
#include "Game/Message/ObjectMessenger.h"

PlayMainState::PlayMainState()
{
	// �C���X�^���X���擾����
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

	auto enemys = m_objectMessenger->FindObject(IObject::ObjectID::ENEMY);

	for (const auto& enemy : enemys)
	{
		if (enemy->GetIsActive()) return;
	}

	SceneManager::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_CANGE_GAME_CLEAR_SCENE);

}

void PlayMainState::PostUpdate()
{
	// �ړ��\�ɂ���
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER, { Message::MessageID::FIXED ,0,0.0f ,true });
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::ENEMY, { Message::MessageID::FIXED,0,0.0f ,true });
}


void PlayMainState::Finalize()
{

}