#pragma once


class HpController
{
public:

	// HPを取得する
	float GetHp() const { return m_hp; }

public:

	// コンストラクタ
	HpController();
	// デストラクタ
	~HpController() = default;

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(const float& elapsedTime);

public:

	// HPを減らす
	bool HpReduction(const float& amount);

private:

	float m_hp;
	float m_maxHp;
	float m_targetHp;
	float m_reduceSpeed;
	bool  m_isReducing;

	bool m_isRecovering;
	float m_recoverDelayTimer;
	float m_recoverDelay;           // 回復開始までの遅延
	float m_recoverSpeed;          // 毎秒の回復速度

};