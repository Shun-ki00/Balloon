#pragma once
#include "Interface/IObject.h"

class IEnemyFactory
{
	// プレイヤーを生成する
	virtual std::unique_ptr<IObject> CreateEnemy(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// プレイヤーの体を生成する
	virtual std::unique_ptr<IObject> CreateEnemyBody(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// プレイヤーの頭を生成する
	virtual std::unique_ptr<IObject> CreateEnemyHead(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// プレイヤーの左腕を生成する
	virtual std::unique_ptr<IObject> CreateEnemyLeftArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// プレイヤーの左足を生成する
	virtual std::unique_ptr<IObject> CreateEnemyLeftFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// プレイヤーの右腕を生成する
	virtual std::unique_ptr<IObject> CreateEnemyRightArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// プレイヤーの右足を生成する
	virtual std::unique_ptr<IObject> CreateEnemyRightFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;
};