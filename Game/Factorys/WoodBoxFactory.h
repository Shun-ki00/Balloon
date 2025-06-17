#pragma once
#include "Interface/IObject.h"

class WoodBoxFactory
{
public:

	// 木箱オブジェクトを作成する
	static std::unique_ptr<IObject> CreateWoodBox(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

private:
	// 回転ベクトルをクォータニオンに変換する
	static DirectX::SimpleMath::Quaternion ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation);

};