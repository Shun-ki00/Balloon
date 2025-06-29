#include "pch.h"
#include "Game/States/SceneStates/FadeStates/FadeOutState.h"
#include "Game/Message/ObjectMessenger.h"


FadeOutState::FadeOutState(int fadeObjectNumber)
{
	// �C���X�^���X���擾����
	m_objectMessenger = ObjectMessenger::GetInstance();

	// �I�u�W�F�N�g�ԍ��擾����
	m_fadeObjectNumber = fadeObjectNumber;
}


void FadeOutState::Initialize()
{
	// ���b�Z�[�W�f�[�^�̍쐬
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