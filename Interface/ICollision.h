#pragma once
#include "Interface/ICollisionVisitor.h"
#include "Interface/IObject.h"

class ICollision
{
public:

	// �Փ˔������������
	virtual void PrepareCollision(ICollisionVisitor* collision) = 0;
	// �Փ˔��肷��
	virtual void DetectCollision(ICollisionVisitor* collision, IObject* object) = 0;

};