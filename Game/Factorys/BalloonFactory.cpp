#include "pch.h"
#include "Game/Factorys/BalloonFactory.h"
#include "Game/Node/root.h"
#include "Game/Message/ObjectMessenger.h"

// パーツ
#include "Game/Balloon/Balloon.h"
#include "Game/Balloon/BalloonBody.h"
#include "Game/Balloon/BalloonRope.h"


// 敵の作成
std::unique_ptr<IObject> BalloonFactory::CreateBalloon(
	IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale,
	const float& colorIndex)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		BalloonFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> player;
	// Turretクラスのインスタンスを生成する
	player.reset(new Balloon(Root::GetInstance(),parent, objectID, initialPosition, rotation, initialScale, colorIndex));
	// 初期化する
	player->Initialize();

	// プレイヤークラスのインスタンスを返す
	return std::move(player);
}

// 敵の体を作成
std::unique_ptr<IObject> BalloonFactory::CreateBalloonBody(
	IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale,
	const float& colorIndex)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		BalloonFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> balloonBody;
	// Turretクラスのインスタンスを生成する
	balloonBody.reset(new BalloonBody(Root::GetInstance(), parent, objectID, initialPosition, rotation, initialScale, colorIndex));
	// 初期化する
	balloonBody->Initialize();
	// オブジェクトメッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, balloonBody->GetObjectNumber(), balloonBody.get());
	// プレイヤークラスのインスタンスを返す
	return std::move(balloonBody);
}


// 敵の頭を作成
std::unique_ptr<IObject> BalloonFactory::CreateBalloonRope(
	IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		BalloonFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> enemyHead;
	// Turretクラスのインスタンスを生成する
	enemyHead.reset(new BalloonRope(Root::GetInstance(), parent, objectID, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// 初期化する
	enemyHead->Initialize();
	// プレイヤークラスのインスタンスを返す
	return std::move(enemyHead);
}


/// <summary>
/// 回転ベクトルをクォータニオンに変換する。
/// </summary>
/// <param name="rotation">回転を表すベクトル（度数法）</param>
/// <returns>変換後のクォータニオン</returns>
DirectX::SimpleMath::Quaternion BalloonFactory::ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation) {
	return DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(rotation.y),
		DirectX::XMConvertToRadians(rotation.x),
		DirectX::XMConvertToRadians(rotation.z)
	);
}