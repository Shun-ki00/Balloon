#pragma once
#include "Interface/IObject.h"

class ICollisionVisitor
{
public:
	// �f�X�g���N�^
	virtual ~ICollisionVisitor() = default;

	// �Փˏ����r�W�^�[���J�n����
	virtual void StartPrepareCollision(IObject* component) = 0;
	// �ċA�I�ɏՓˏ����r�W�^�[���Ăяo��
	virtual void PrepareCollision(IObject* object,
		const DirectX::SimpleMath::Vector3& position, const float& radius) = 0;
	// �ċA�I��DetectCollision�֐����Ăяo��
	virtual void DetectCollision(IObject* component, IObject* bullets) = 0;

	// ���E�{�b�N�X��`�悷��
	virtual void DebugDraw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitiveBatch ) = 0;
};