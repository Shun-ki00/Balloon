#pragma once
#include "Interface/IObject.h"
#include "Interface/IBalloonFactory.h"


class BalloonFactory : public IBalloonFactory
{
public:
	// 敵を生成する
	static std::unique_ptr<IObject> CreateBalloon(
		IObject* parent,IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// 敵の体を生成する
	static std::unique_ptr<IObject> CreateBalloonBody(
		IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// 敵の頭を生成する
	static std::unique_ptr<IObject> CreateBalloonRope(
		IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);
private:
	// 回転ベクトルをクォータニオンに変換する
	static DirectX::SimpleMath::Quaternion ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation);
};
