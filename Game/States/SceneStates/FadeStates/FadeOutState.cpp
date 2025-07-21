#include "pch.h"
#include "Game/States/SceneStates/FadeStates/FadeOutState.h"
#include "Game/Message/ObjectMessenger.h"


FadeOutState::FadeOutState(Message::MessageData data)
{
	// �C���X�^���X���擾����
	m_objectMessenger = ObjectMessenger::GetInstance();

	// ���b�Z�[�W�f�[�^�ݒ�
	m_messageData = data;
	
}


void FadeOutState::Initialize()
{

}


void FadeOutState::PreUpdate()
{
	// BGM���~����
	AudioManager::GetInstance()->StopBgm(1.0f);
	// �Đ�����SE���~����
	AudioManager::GetInstance()->StopSE();

	// �t�F�[�h�A�E�g���s��
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