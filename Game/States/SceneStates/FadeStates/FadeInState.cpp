#include "pch.h"
#include "Game/States/SceneStates/FadeStates/FadeInState.h"
#include "Game/Message/ObjectMessenger.h"


FadeInState::FadeInState(int fadeObjectNumber)
{
	// �C���X�^���X���擾����
	m_objectMessenger = ObjectMessenger::GetInstance();

	// �I�u�W�F�N�g�ԍ��擾����
	m_fadeObjectNumber = fadeObjectNumber;
}


void FadeInState::Initialize()
{
	// ���b�Z�[�W�f�[�^�̍쐬
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
	// �t�F�[�h�C�����s��
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