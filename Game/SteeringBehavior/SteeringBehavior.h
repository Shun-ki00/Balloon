#pragma once
#include "Interface/ISteeringBehavior.h"
#include "Interface/IObject.h"

class SteeringBehavior
{
public:


	// ステアリングビヘイビアを取得する
	ISteeringBehavior* GetSteeringBehavior(BEHAVIOR_TYPE flags);

	// コンストラクタ
	SteeringBehavior();
	// デストラクタ
	~SteeringBehavior() = default;

	// 初期化処理
	void Initialize();

	// 計算処理を行う
	DirectX::SimpleMath::Vector3 Calculate(const float& elapsedTime);

	// ステアリングビヘイビアをオンにする
	void On(BEHAVIOR_TYPE flags);
	// ステアリングビヘイビアをオフにする
	void Off(BEHAVIOR_TYPE flags);

	// 追加する
	void Attach(BEHAVIOR_TYPE flags , std::unique_ptr<ISteeringBehavior> steeringBehavior);

private:

	// ステアリングビヘイビア
	std::unordered_map<BEHAVIOR_TYPE, std::unique_ptr<ISteeringBehavior>> m_behaviors;

	// フラグ
	uint32_t m_flags;

	// ターゲットオブジェクト
	IObject* m_targetObject;
};