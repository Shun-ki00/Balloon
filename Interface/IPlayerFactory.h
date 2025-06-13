#pragma once
#include "Interface/IObject.h"

class IPlayerFactory
{
	// プレイヤーを生成する
	virtual std::unique_ptr<IObject> CreatePlayer(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// プレイヤーの体を生成する
	virtual std::unique_ptr<IObject> CreatePlayerBody(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// プレイヤーの頭を生成する
	virtual std::unique_ptr<IObject> CreatePlayerHead(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// プレイヤーの左腕を生成する
	virtual std::unique_ptr<IObject> CreatePlayerLeftArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// プレイヤーの左足を生成する
	virtual std::unique_ptr<IObject> CreatePlayerLeftFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// プレイヤーの右腕を生成する
	virtual std::unique_ptr<IObject> CreatePlayerRightArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// プレイヤーの右足を生成する
	virtual std::unique_ptr<IObject> CreatePlayerRightFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;
};