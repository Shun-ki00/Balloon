#pragma once
#include "Interface/IObject.h"
#include "Interface/IEnemyFactory.h"

class EnemyFactory : public IEnemyFactory
{
public:
	// “G‚ğ¶¬‚·‚é
	static std::unique_ptr<IObject> CreateEnemy(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale,const bool& isFixed);

	// “G‚Ì‘Ì‚ğ¶¬‚·‚é
	static std::unique_ptr<IObject> CreateEnemyBody(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// “G‚Ì“ª‚ğ¶¬‚·‚é
	static std::unique_ptr<IObject> CreateEnemyHead(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// “G‚Ì¶˜r‚ğ¶¬‚·‚é
	static std::unique_ptr<IObject> CreateEnemyLeftArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// “G‚Ì¶‘«‚ğ¶¬‚·‚é
	static std::unique_ptr<IObject> CreateEnemyLeftFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// “G‚Ì‰E˜r‚ğ¶¬‚·‚é
	static std::unique_ptr<IObject> CreateEnemyRightArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// “G‚Ì‰E‘«‚ğ¶¬‚·‚é
	static std::unique_ptr<IObject> CreateEnemyRightFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

private:
	// ‰ñ“]ƒxƒNƒgƒ‹‚ğƒNƒH[ƒ^ƒjƒIƒ“‚É•ÏŠ·‚·‚é
	static DirectX::SimpleMath::Quaternion ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation);
};