#pragma once

class IBalloonFactory
{
	// ���D�𐶐�����
	virtual std::unique_ptr<IObject> CreateBalloon(
		IObject* parent,IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// ���D�̖{�̂𐶐�����
	virtual std::unique_ptr<IObject> CreateBalloonBody(
		IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// ���D�̂Ђ��𐶐�����
	virtual std::unique_ptr<IObject> CreateBalloonRope(
		IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;
};