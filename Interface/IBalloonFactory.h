#pragma once

class IBalloonFactory
{
	// 風船を生成する
	virtual std::unique_ptr<IObject> CreateBalloon(
		IObject* parent,IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// 風船の本体を生成する
	virtual std::unique_ptr<IObject> CreateBalloonBody(
		IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// 風船のひもを生成する
	virtual std::unique_ptr<IObject> CreateBalloonRope(
		IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;
};