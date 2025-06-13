#pragma once
#include "Interface/IObject.h"
#include "Interface/IEnemyFactory.h"

class EnemyFactory : public IEnemyFactory
{
public:
	// �G�𐶐�����
	static std::unique_ptr<IObject> CreateEnemy(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �G�̑̂𐶐�����
	static std::unique_ptr<IObject> CreateEnemyBody(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �G�̓��𐶐�����
	static std::unique_ptr<IObject> CreateEnemyHead(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �G�̍��r�𐶐�����
	static std::unique_ptr<IObject> CreateEnemyLeftArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �G�̍����𐶐�����
	static std::unique_ptr<IObject> CreateEnemyLeftFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �G�̉E�r�𐶐�����
	static std::unique_ptr<IObject> CreateEnemyRightArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �G�̉E���𐶐�����
	static std::unique_ptr<IObject> CreateEnemyRightFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

private:
	// ��]�x�N�g�����N�H�[�^�j�I���ɕϊ�����
	static DirectX::SimpleMath::Quaternion ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation);
};