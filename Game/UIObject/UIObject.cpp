#include "pch.h"
#include "Game/UIObject/UIObject.h"

// �I�u�W�F�N�g�ԍ�
int UIObject::s_objectNumber = 0;

// �I�u�W�F�N�g���J�E���g�A�b�v����
int UIObject::CountUpNumber() { return s_objectNumber++; }

// ���݂̃I�u�W�F�N�g�̃J�E���g���擾����
int UIObject::ResetNumber() { return s_objectNumber = 0; }

// ���݂̃I�u�W�F�N�g�ԍ����擾����
int UIObject::GetNumber() { return s_objectNumber; }


// �R���X�g���N�^
UIObject::UIObject()
{
}

// �f�X�g���N�^
UIObject::~UIObject()
{
}

// ����������
void UIObject::Initialize()
{
}

// �X�V����
void UIObject::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
}


// �㏈�����s��
void UIObject::Finalize()
{
}