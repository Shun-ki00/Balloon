#pragma once
#include "Interface/IObject.h"
#include "Interface/IBalloonFactory.h"


class BalloonFactory : public IBalloonFactory
{
public:
	// 風船を生成
	static std::unique_ptr<IObject> CreateBalloon(
		IObject* parent,IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale,
		const float& colorIndex);

	// 風船の本体を生成
	static std::unique_ptr<IObject> CreateBalloonBody(
		IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale,
		const float& colorIndex);

	// 風船の線を生成
	static std::unique_ptr<IObject> CreateBalloonRope(
		IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);
private:
	// 回転ベクトルをクォータニオンに変換する
	static DirectX::SimpleMath::Quaternion ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation);
};
