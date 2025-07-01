// ============================================
// 
// ファイル名: Player.h
// 概要: Player.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IComposite.h"
#include "Interface/ICollision.h"
#include "Game/Object/Object.h"

class Transform;
class PlayerRenderableObject;
class PlayerIdleState;
class PlayerRunState;
class PlayerAttackState;
class PlayerSitState;

class ISteeringBehavior;
class SteeringBehavior;

class BalloonScaleController;
class HpController;

class CollisionVisitor;

class Player : public Object ,public ICollision , public IComposite
{
public:
	// オブジェクトのアクティブ設定
	void SetIsActive(const bool& isActive) { m_isActive = isActive; }
	// オブジェクトのアクティブ状態を取得
	bool GetIsActive() const { return m_isActive; }

	// オブジェクト番号を取得する
	int GetObjectNumber() const  override { return m_objectNumber; }

	std::vector<IObject*> GetBalloonObject() { return m_balloonObject; }

	// オブジェクトIDを取得する
	IObject::ObjectID GetObjectID() const override { return m_objectID; }
	// Transformを取得する
	Transform* GetTransform() const override { return m_transform.get(); }

	// 親オブジェクトを取得する
	IObject* GetParent() const override { return m_parent; }
	// 子オブジェクトを取得する
	std::vector<IObject*> GetChilds() const override;

	// 速度を取得する
	DirectX::SimpleMath::Vector3& GetVelocity() override { return m_velocity; }
	// 速度を設定する
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) override { m_velocity = velocity; }
	// 加速度を取得する
	DirectX::SimpleMath::Vector3& GetAcceralation() override { return m_acceralation; }
	// 加速度を設定する
	void SetAcceralation(const DirectX::SimpleMath::Vector3& accelaration) override { m_acceralation = accelaration; }

	// プレイヤーの固定設定
	void SetIsFixed(const bool& isFixed) { m_isFixed = isFixed; }

	// コンストラクタ
	Player(IObject* root, IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale,
		Message::MessageID messageID);
	// デストラクタ
	~Player() override;

	// 初期化する
	void Initialize();
	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageData messageData) override;
	// キーが押下げられたら通知する
	void OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key) override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 後処理を行う
	void Finalize() override;

	// オブジェクトをアタッチする
	void Attach(std::unique_ptr<IObject> object) override;

	// オブジェクトを削除する
	void Detach(std::unique_ptr<IObject> object) override;

	// 衝突判定の準備
	void PrepareCollision(ICollisionVisitor* collision) override;
	// 衝突判定するt
	void DetectCollision(ICollisionVisitor* collision, IObject* bullets) override;

private:

	// オブジェクトを追加する
	void AttachObject();

	// ステートを作成する
	void CreateState();

	// ステアリングビヘイビアを作成する
	void CreateSteeringBehavior();

private:

	// === 共通なもの ===

	// ビジター
	CollisionVisitor* m_collisionVisitor;

	// アクティブ状態
	bool m_isActive;
	// オブジェクト番号
	int m_objectNumber;
	// オブジェクトID
	IObject::ObjectID m_objectID;
	// メッセージID
	Message::MessageID m_messageID;
	// Transform
	std::unique_ptr<Transform> m_transform;
	// 親オブジェクト
	IObject* m_parent;
	// 子オブジェクト
	std::vector<std::unique_ptr<IObject>> m_childs;
	// 当たり判定
	std::unique_ptr<DirectX::BoundingSphere> m_boundingSphere;

	// 風船オブジェクト
	std::vector<IObject*> m_balloonObject;

	// === 物理挙動 ===

	// プレイヤーの速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// 方向
	DirectX::SimpleMath::Vector3 m_heading;
	// 直横
	DirectX::SimpleMath::Vector3 m_side;
	// プレイヤーの加速度
	DirectX::SimpleMath::Vector3 m_acceralation;


	// === ステアリングビヘイビア ===

	std::unique_ptr<SteeringBehavior> m_steeringBehavior;
	
	// === ステート ===

	// アイドルステート
	std::unique_ptr<PlayerIdleState> m_playerIdleState;
	// ランステート
	std::unique_ptr<PlayerRunState> m_playerRunState;
	// アタックステート
	std::unique_ptr<PlayerAttackState> m_playerAttackState;
	// 座るステート
	std::unique_ptr<PlayerSitState> m_playerSitState;


	// 固定設定
	bool m_isFixed;

	// 風船の大きさをコントロール
	std::unique_ptr<BalloonScaleController> m_balloonScaleController;
	// HPをコントロール
	std::unique_ptr<HpController> m_hpController;

};