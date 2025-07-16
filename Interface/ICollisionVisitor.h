#pragma once
#include "Interface/IObject.h"

class ICollisionVisitor
{
public:
	// �f�X�g���N�^
	virtual ~ICollisionVisitor() = default;


	// �A�^�b�`�̋���
	virtual void Begin() = 0;
	// �A�^�b�`�̏I��
	virtual void End() = 0;

	// �Փˏ����r�W�^�[���J�n����
	virtual void StartPrepareCollision(IObject* component) = 0;
	// �ċA�I�ɏՓˏ����r�W�^�[���Ăяo��
	virtual void PrepareCollision(IObject* object, DirectX::BoundingSphere* boundingSphere) = 0;
	// �ċA�I��DetectCollision�֐����Ăяo��
	virtual void DetectCollision(IObject* component, IObject* bullets) = 0;

	// ���E�{�b�N�X��`�悷��
	virtual void DebugDraw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitiveBatch ) = 0;
};