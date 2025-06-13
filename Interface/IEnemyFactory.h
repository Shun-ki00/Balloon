#pragma once
#include "Interface/IObject.h"

class IEnemyFactory
{
	// �v���C���[�𐶐�����
	virtual std::unique_ptr<IObject> CreateEnemy(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// �v���C���[�̑̂𐶐�����
	virtual std::unique_ptr<IObject> CreateEnemyBody(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// �v���C���[�̓��𐶐�����
	virtual std::unique_ptr<IObject> CreateEnemyHead(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// �v���C���[�̍��r�𐶐�����
	virtual std::unique_ptr<IObject> CreateEnemyLeftArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// �v���C���[�̍����𐶐�����
	virtual std::unique_ptr<IObject> CreateEnemyLeftFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// �v���C���[�̉E�r�𐶐�����
	virtual std::unique_ptr<IObject> CreateEnemyRightArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// �v���C���[�̉E���𐶐�����
	virtual std::unique_ptr<IObject> CreateEnemyRightFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;
};