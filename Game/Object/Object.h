#pragma once
#include "Interface/IObject.h"
#include "Interface/IState.h"

class Object : public IObject
{
public:
	// オブジェクトをカウントアップする
	static int CountUpNumber();
	// 現在のオブジェクトカウントを取得
	static int ResetNumber();

	// 状態を取得する
	IState* GetState() const { return m_currentState; }
	// 状態を設定する
	void SetState(IState* state) { m_currentState = state; }
	// 現在の状態を変更する
	void ChangeState(IState* state)
	{
		// 新規の状態遷移前に事後更新を行う
		m_currentState->PostUpdate();
		// 新規の状態を現在の状態に設定する
		m_currentState = state;
		// 新規の状態遷移後に事前更新を行う
		m_currentState->PreUpdate();
	}

	// 速度を取得する
	virtual DirectX::SimpleMath::Vector3& GetVelocity() = 0;
	// 速度を設定する
	virtual void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) = 0;
	// 加速度を取得する
	virtual DirectX::SimpleMath::Vector3& GetAcceralation() = 0;
	// 加速度を設定する
	virtual void SetAcceralation(const DirectX::SimpleMath::Vector3& acceralation) = 0;

	// 回転するときの最大速度
	float GetMaxTurnRate() const { return m_maxTurnRate; }
	// 最大移動速度
	float GetMaxSpeed() const { return m_maxSpeed; }
	// 最大力
	float GetMaxForce() const { return m_maxForce; }
	// 質量
	float GetMass() const { return m_mass; }

public:

	// コンストラクタ
	Object(const float& m_maxTurnRate, const float& m_maxSpeed, const float& m_maxForce, const float& m_mass);
	// デストラクタ
	 ~Object() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 後処理を行う
	void Finalize() override;

private:
	// オブジェクト番号
	static int s_objectNumber;
	// 現在の状態
	IState* m_currentState;
	// 現在のメッセージ
	Message m_currentMessage;

	// 回転するときの最大速度
	float m_maxTurnRate;
	// 最大移動速度
	float m_maxSpeed;
	// 最大力
	float m_maxForce;
	// プレイヤーの質量
	float m_mass;
};