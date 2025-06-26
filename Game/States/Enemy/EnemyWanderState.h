#pragma once
#pragma once
#include "Interface/IState.h"

class Transform;
class Object;


class EnemyWanderState : public IState
{

public:
	// コンストラクタ
	EnemyWanderState(Object* object);
	// デストラクタ
	~EnemyWanderState() = default;
	// 初期化する
	void Initialize() override;
	// 事前更新する
	void PreUpdate() override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 事後更新する
	void PostUpdate() override;
	// 後処理を行う
	void Finalize() override;

private:

	// 回転角
	static const float MIN_ROTATION_ANGLE;
	static const float MAX_ROTATION_ANGLE;
	// 回転速度
	static const float ROTATION_DURATION;
	// 移動距離
	static const float MIN_MOVE_DISTANCE;
	static const float MAX_MOVE_DISTANCE;
	// 移動速度
	static const float MIN_MOVE_SPEED;
	static const float MAX_MOVE_SPEED;

public:

	// 敵オブジェクト
	Object* m_object;

	// 待ち時間の状態
	bool m_isWait;

	// 風船を膨らませるか
	bool m_isFlate;

	// 経過時間
	float m_timer;
	// 待機時間
	float m_waitTime;
	
	// 向きたい角度
	float m_targetAngle;
	// 回転速度
	float m_rotationSpeed;
	

	// 移動速度
	float m_moveSpeed;
	// 移動距離
	float m_moveDistance;
	// 進んだ距離
	float m_moved;
};