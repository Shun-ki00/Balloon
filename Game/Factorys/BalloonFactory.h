#pragma once
#include "Interface/IObject.h"
#include "Interface/IBalloonFactory.h"


class BalloonFactory : public IBalloonFactory
{
public:
	// �G�𐶐�����
	static std::unique_ptr<IObject> CreateBalloon(
		IObject* parent,IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �G�̑̂𐶐�����
	static std::unique_ptr<IObject> CreateBalloonBody(
		IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �G�̓��𐶐�����
	static std::unique_ptr<IObject> CreateBalloonRope(
		IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);
private:
	// ��]�x�N�g�����N�H�[�^�j�I���ɕϊ�����
	static DirectX::SimpleMath::Quaternion ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation);
};
