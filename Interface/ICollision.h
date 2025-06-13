#pragma once
#include "Interface/ICollisionVisitor.h"
#include "Interface/IObject.h"

class ICollision
{
public:

	// Õ“Ë”»’è‚ğ€”õ‚·‚é
	virtual void PrepareCollision(ICollisionVisitor* collision) = 0;
	// Õ“Ë”»’è‚·‚é
	virtual void DetectCollision(ICollisionVisitor* collision, IObject* object) = 0;

};