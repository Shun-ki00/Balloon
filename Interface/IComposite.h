// ============================================
// 
// �t�@�C����: IComposite.h
// �T�v: �����I�u�W�F�N�g�̍\���E�������`����i�C���^�[�t�F�[�X�j
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IObject.h"

class IComposite
{
public:
	// �I�u�W�F�N�g��ǉ�����
	virtual void Attach(std::unique_ptr<IObject> object) = 0;
	// �I�u�W�F�N�g���폜����
	virtual void Detach(std::unique_ptr<IObject> object)  = 0;
};

