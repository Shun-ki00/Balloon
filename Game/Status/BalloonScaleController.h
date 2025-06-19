#pragma once

class FloatForceBehavior;
class HpController;

class BalloonScaleController
{

public:

	// コンストラクタ
	BalloonScaleController(HpController* hpController, FloatForceBehavior* floatForceBehavior);
	// デストラクタ
	~BalloonScaleController() = default;

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(const float& elapsedTime);

	// オン
	void On();
	// オフ
	void Off();

private:

	// ステアリングビヘイビア
	FloatForceBehavior* m_floatForceBehavior;
	// HPコントローラー
	HpController* m_hpController;

	// 風船の大きさ
	float m_balloonScale;
	// 風船を膨らませているかどうか
	bool m_isBalloonInflating;

};