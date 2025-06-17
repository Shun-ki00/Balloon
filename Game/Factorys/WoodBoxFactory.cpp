#include "pch.h"
#include "Game/Factorys/WoodBoxFactory.h"
#include "Game/WoodBox/WoodBox.h"
#include "Game/Node/Root.h"

/// <summary>
/// 木箱オブジェクトを作成する
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="initialRotation">初期回転角</param>
/// <param name="initialScale">初期スケール</param>
/// <returns></returns>
std::unique_ptr<IObject> WoodBoxFactory::CreateWoodBox(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		WoodBoxFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<WoodBox> playerBody;
	// Turretクラスのインスタンスを生成する
	playerBody.reset(new WoodBox(Root::GetInstance(), parent, IObject::ObjectID::WOOD_BOX, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// 初期化する
	playerBody->Initialize();
	// プレイヤークラスのインスタンスを返す
	return std::move(playerBody);
}

/// <summary>
/// 回転ベクトルをクォータニオンに変換する。
/// </summary>
/// <param name="rotation">回転を表すベクトル（度数法）</param>
/// <returns>変換後のクォータニオン</returns>
DirectX::SimpleMath::Quaternion WoodBoxFactory::ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation) {
	return DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(rotation.y),
		DirectX::XMConvertToRadians(rotation.x),
		DirectX::XMConvertToRadians(rotation.z)
	);
}