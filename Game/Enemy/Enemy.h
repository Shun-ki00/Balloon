#pragma once
#include "Interface/IComposite.h"
#include "Game/Object/Object.h"
#include "Interface/ICollision.h"
#include "Game/Status/HpController.h"
#include "Game/Status/BalloonScaleController.h"

class Transform;
class PlayerRenderableObject;
class CollisionVisitor;

class ISteeringBehavior;
class KnockbackBehavior;
class PushBackBehavior;
class FloatBehavior;
class FloatForceBehavior;
class SeekBehavior;

class BalloonScaleController;
class HpController;

class ActionSelection;

class Enemy : public Object , public ICollision ,public IComposite
{
public:
	// オブジェクトのアクティブ設定
	void SetIsActive(const bool& isActive) { m_isActive = isActive; }
	// オブジェクトのアクティブ状態を取得
	bool GetIsActive() const { return m_isActive; }

	// HPを取得する
	float GetHp() const { return m_hpController->GetHp(); }
	// 風船の大きさを取得する
	float GetBalloonScale() const { return m_balloonScaleController->GetBalloonScale(); }

	// オブジェクト番号を取得する
	int GetObjectNumber() const  override { return m_objectNumber; }

	std::vector<IObject*> GetBalloonObject() { return m_balloonObject; }

	// オブジェクトIDを取得する
	IObject::ObjectID GetObjectID() const override { return m_objectID; }
	// Transformを取得する
	Transform* GetTransform() const override { return m_transform.get(); }

	// 親オブジェクトを取得する
	IObject* GetParent() const override { return m_parent; }

	// 速度を取得する
	DirectX::SimpleMath::Vector3& GetVelocity() override { return m_velocity; }
	// 速度を設定する
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) override { m_velocity = velocity; }
	// 加速度を取得する
	DirectX::SimpleMath::Vector3& GetAcceralation() override { return m_acceralation; }
	// 加速度を設定する
	void SetAcceralation(const DirectX::SimpleMath::Vector3& accelaration) override { m_acceralation = accelaration; }

	// コンストラクタ
	Enemy(IObject* root, IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale,
		Message::MessageID messageID);
	// デストラクタ
	~Enemy() override;

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

	// 衝突判定を準備する
	void PrepareCollision(ICollisionVisitor* collision) override;

	// 衝突判定する
	void DetectCollision(ICollisionVisitor* collision, IObject* object) override;

private:

	// ビジター
	CollisionVisitor* m_collisionVisitor;

	// アクティブ状態
	bool m_isActive;
	// オブジェクト番号
	int m_objectNumber;
	// オブジェクトID
	IObject::ObjectID m_objectID;
	// 親オブジェクト
	IObject* m_parent;
	// 子オブジェクト
	std::vector<std::unique_ptr<IObject>> m_childs;
	// 風船オブジェクト
	std::vector<IObject*> m_balloonObject;
	
	// メッセージID
	Message::MessageID m_messageID;
	// Transform
	std::unique_ptr<Transform> m_transform;
	// 当たり判定
	DirectX::BoundingSphere m_boundingSphere;

	// アクションセレクター
	std::unique_ptr<ActionSelection> m_actionSelection;

	// ステアリングビヘイビア
	ISteeringBehavior* m_steeringBehavior;
	// ノックバック
	std::unique_ptr<KnockbackBehavior> m_knockbackBehavior;
	// 揺れる
	std::unique_ptr<FloatBehavior> m_floatBehavior;

	std::unique_ptr<FloatForceBehavior> m_floatForceBehavior;

	std::unique_ptr<PushBackBehavior> m_pushBackBehavior;


	std::unique_ptr<SeekBehavior> m_seekBehavior;

	// プレイヤーの速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// 方向
	DirectX::SimpleMath::Vector3 m_heading;
	// 直横
	DirectX::SimpleMath::Vector3 m_side;
	// プレイヤーの加速度
	DirectX::SimpleMath::Vector3 m_acceralation;

	float m_balloonIndex;

	// 風船の大きさをコントロール
	std::unique_ptr<BalloonScaleController> m_balloonScaleController;
	// HPをコントロール
	std::unique_ptr<HpController> m_hpController;

};