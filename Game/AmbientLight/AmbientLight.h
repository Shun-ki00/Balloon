#pragma once
#include "Game/Object/Object.h"
#include "Interface/ILeaf.h"
#include "Game/Buffers/ConstantBuffer.h"


class Transform;
class IRenderableObject;
class CommonResources;


class AmbientLight : public Object , ILeaf
{
public:

	// 定数バッファを取得する
	ID3D11Buffer* GetBuffer() const { return m_constantBuffer->GetBuffer(); }

	// 色を設定
	void SettColor(const DirectX::SimpleMath::Vector3& color) { m_ambientLightData.ambientLightColor = color; }
	// 強さを設定
	void SetIntensity(const float& intensity) { m_ambientLightData.ambientLightIntensity = intensity; }

	// オブジェクトのアクティブ設定
	void SetIsActive(const bool& isActive) { m_isActive = isActive; }
	// オブジェクトのアクティブ状態を取得
	bool GetIsActive() const { return m_isActive; }

	// オブジェクト番号を取得する
	int GetObjectNumber() const  override { return 0; }

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

private:
	//	コンストラクタ
	AmbientLight();
	//	デストラクタ
	~AmbientLight() override = default;
public:
	AmbientLight(const AmbientLight&) = delete;             // コピー禁止
	AmbientLight& operator=(const AmbientLight&) = delete;  // コピー代入禁止
	AmbientLight(const AmbientLight&&) = delete;            // ムーブ禁止
	AmbientLight& operator=(const AmbientLight&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static AmbientLight* GetInstance()
	{
		static AmbientLight instance;
		return &instance;
	}

	// 初期化する
	void Initialize() override;
	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageData messageData) override;
	// キーが押下げられたら通知する
	void OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key) override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 後処理を行う
	void Finalize() override;
	
private:

	// 共有リソース
	CommonResources* m_commonResources;
	// コンテキスト
	ID3D11DeviceContext1* m_context;

	// アクティブ状態
	bool m_isActive;
	// オブジェクトID
	IObject::ObjectID m_objectID;
	// 親オブジェクト
	IObject* m_parent;

	// Transform
	std::unique_ptr<Transform> m_transform;

	AmbientLightParameters m_ambientLightData;
	// 定数バッファ
	std::unique_ptr<ConstantBuffer<AmbientLightParameters>> m_constantBuffer;


	// プレイヤーの速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// 方向
	DirectX::SimpleMath::Vector3 m_heading;
	// 直横
	DirectX::SimpleMath::Vector3 m_side;
	// プレイヤーの加速度
	DirectX::SimpleMath::Vector3 m_acceralation;
};