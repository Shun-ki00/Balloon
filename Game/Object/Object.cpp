#include "pch.h"
#include "Game/Object/Object.h"

// �I�u�W�F�N�g�ԍ�
int Object::s_objectNumber = 0;

// �I�u�W�F�N�g���J�E���g�A�b�v����
int Object::CountUpNumber() { return s_objectNumber++; }

// ���݂̃I�u�W�F�N�g�̃J�E���g���擾����
int Object::ResetNumber() { return s_objectNumber = 0; }


// �R���X�g���N�^
Object::Object(const float& maxTurnRate, const float& maxSpeed, const float& maxForce, const float& mass)
	:
	m_currentState{},			// ���݂̏��
	m_currentMessage{},		    // ���݂̃��b�Z�[�W
	m_maxTurnRate(maxTurnRate), // ��]����Ƃ��̍ő呬�x
	m_maxSpeed(maxSpeed),		// �ő�ړ����x
	m_maxForce(maxForce),		// �ő��
	m_mass(mass)				// ����					
{
}

// �f�X�g���N�^
Object::~Object()
{
}

// ����������
void Object::Initialize()
{
}

// �X�V����
void Object::Update(const float& elapsedTime)
{
	m_currentState->Update(elapsedTime);
}


// �㏈�����s��
void Object::Finalize()
{
}