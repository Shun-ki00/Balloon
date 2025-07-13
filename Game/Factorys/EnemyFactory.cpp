#include "pch.h"
#include "Interface/IObject.h"
#include "Game/Factorys/EnemyFactory.h"
#include "Game/Message/Message.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Node/Root.h"

// 敵パーツ
#include "Game/Enemy/Enemy.h"
#include "Game/Player/Body.h"
#include "Game/Player/Head.h"
#include "Game/Player/LeftArm.h"
#include "Game/Player/LeftFoot.h"
#include "Game/Player/RightArm.h"
#include "Game/Player/RightFoot.h"


// 敵の作成
std::unique_ptr<IObject> EnemyFactory::CreateEnemy(IObject* parent, const EnemyParams& enemyParams)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		EnemyFactory::ConvertToYawPitchRoll(enemyParams.rotation);

	// 砲塔を宣言する
	std::unique_ptr<Enemy> enemy;
	// Turretクラスのインスタンスを生成する
	enemy.reset(new Enemy(Root::GetInstance(), parent , IObject::ObjectID::ENEMY ,
		enemyParams.position, rotation , enemyParams.scale, enemyParams.balloonIndex,
		enemyParams.floatBehaviorParams,enemyParams.knockbackBehaviorParams,enemyParams.seekBehaviorParams));
	// 初期化する
	enemy->Initialize();
	// 固定設定
	enemy->SetIsFixed(enemyParams.fixed);

	// オブジェクトメッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::ENEMY, enemy->GetObjectNumber(), enemy.get());

	// プレイヤークラスのインスタンスを返す
	return std::move(enemy);
}

// 敵の体を作成
std::unique_ptr<IObject> EnemyFactory::CreateEnemyBody(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		EnemyFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> enemyBody;
	// Turretクラスのインスタンスを生成する
	enemyBody.reset(new Body(Root::GetInstance(), parent, IObject::ObjectID::ENEMY_BODY, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// 初期化する
	enemyBody->Initialize();
	// プレイヤークラスのインスタンスを返す
	return std::move(enemyBody);
}


// 敵の頭を作成
std::unique_ptr<IObject> EnemyFactory::CreateEnemyHead(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		EnemyFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> enemyHead;
	// Turretクラスのインスタンスを生成する
	enemyHead.reset(new Head(Root::GetInstance(), parent, IObject::ObjectID::ENEMY_HEAD, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// 初期化する
	enemyHead->Initialize();
	// プレイヤークラスのインスタンスを返す
	return std::move(enemyHead);
}


// 敵の左腕を作成
std::unique_ptr<IObject> EnemyFactory::CreateEnemyLeftArm(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		EnemyFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> enemyLeftArm;
	// Turretクラスのインスタンスを生成する
	enemyLeftArm.reset(new LeftArm(Root::GetInstance(), parent, IObject::ObjectID::ENEMY_LEFT_ARM, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// 初期化する
	enemyLeftArm->Initialize();
	// プレイヤークラスのインスタンスを返す
	return std::move(enemyLeftArm);
}

// 敵の左足を作成
std::unique_ptr<IObject> EnemyFactory::CreateEnemyLeftFoot(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		EnemyFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> enemyLeftFoot;
	// Turretクラスのインスタンスを生成する
	enemyLeftFoot.reset(new LeftFoot(Root::GetInstance(), parent, IObject::ObjectID::ENEMY_LEFT_FOOT, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// 初期化する
	enemyLeftFoot->Initialize();
	// プレイヤークラスのインスタンスを返す
	return std::move(enemyLeftFoot);
}


// 敵の右腕を作成
std::unique_ptr<IObject> EnemyFactory::CreateEnemyRightArm(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		EnemyFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> enemyRightArm;
	// Turretクラスのインスタンスを生成する
	enemyRightArm.reset(new RightArm(Root::GetInstance(), parent, IObject::ObjectID::ENEMY_RIGHT_ARM, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// 初期化する
	enemyRightArm->Initialize();
	// プレイヤークラスのインスタンスを返す
	return std::move(enemyRightArm);
}

// 敵の右足を作成
std::unique_ptr<IObject> EnemyFactory::CreateEnemyRightFoot(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		EnemyFactory::ConvertToYawPitchRoll(initialRotation);

	// 砲塔を宣言する
	std::unique_ptr<IObject> enemyRightFoot;
	// Turretクラスのインスタンスを生成する
	enemyRightFoot.reset(new RightFoot(Root::GetInstance(), parent, IObject::ObjectID::ENEMY_RIGHT_FOOT, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// 初期化する
	enemyRightFoot->Initialize();
	// プレイヤークラスのインスタンスを返す
	return std::move(enemyRightFoot);
}



/// <summary>
/// 回転ベクトルをクォータニオンに変換する。
/// </summary>
/// <param name="rotation">回転を表すベクトル（度数法）</param>
/// <returns>変換後のクォータニオン</returns>
DirectX::SimpleMath::Quaternion EnemyFactory::ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation) {
	return DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(rotation.y),
		DirectX::XMConvertToRadians(rotation.x),
		DirectX::XMConvertToRadians(rotation.z)
	);
}