#pragma once
#include "Interface/IObject.h"
#include "Interface/IPlayerFactory.h"
#include "Game/Parameters/ParameterBuffers.h"

class PlayerFactory : public IPlayerFactory
{
public:
	// プレイヤーを生成する
	static std::unique_ptr<IObject> CreatePlayer(IObject* parent,
		const PlayerParams& playerParams
		);

	// プレイヤーの体を生成する
	static std::unique_ptr<IObject> CreatePlayerBody(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// プレイヤーの頭を生成する
	static std::unique_ptr<IObject> CreatePlayerHead(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// プレイヤーの左腕を生成する
	static std::unique_ptr<IObject> CreatePlayerLeftArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// プレイヤーの左足を生成する
	static std::unique_ptr<IObject> CreatePlayerLeftFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// プレイヤーの右腕を生成する
	static std::unique_ptr<IObject> CreatePlayerRightArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// プレイヤーの右足を生成する
	static std::unique_ptr<IObject> CreatePlayerRightFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

private:
	// 回転ベクトルをクォータニオンに変換する
	static DirectX::SimpleMath::Quaternion ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation);
};