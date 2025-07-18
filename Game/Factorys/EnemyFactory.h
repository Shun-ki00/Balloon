#pragma once
#include "Interface/IObject.h"
#include "Interface/IEnemyFactory.h"
#include "Game/Parameters/ParameterBuffers.h"

class EnemyFactory : public IEnemyFactory
{
public:
	// 敵を生成する
	static std::unique_ptr<IObject> CreateEnemy(IObject* parent , const EnemyParams& enemyParams);

	// 敵の体を生成する
	static std::unique_ptr<IObject> CreateEnemyBody(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// 敵の頭を生成する
	static std::unique_ptr<IObject> CreateEnemyHead(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// 敵の左腕を生成する
	static std::unique_ptr<IObject> CreateEnemyLeftArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// 敵の左足を生成する
	static std::unique_ptr<IObject> CreateEnemyLeftFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// 敵の右腕を生成する
	static std::unique_ptr<IObject> CreateEnemyRightArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// 敵の右足を生成する
	static std::unique_ptr<IObject> CreateEnemyRightFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

private:
	// 回転ベクトルをクォータニオンに変換する
	static DirectX::SimpleMath::Quaternion ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation);
};