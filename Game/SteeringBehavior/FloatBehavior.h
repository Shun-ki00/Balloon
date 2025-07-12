// ============================================
// 
// ファイル名: FloatBehavior.h
// 概要: FloatBehavior.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/ISteeringBehavior.h"


class FloatBehavior : public ISteeringBehavior
{
public:

	// ビヘイビアを有効にする
	void On() override;
	// ビヘイビアを無効にする
	void Off() override;

	// ステアリング力を計算する
	DirectX::SimpleMath::Vector3 Calculate() override;

	// コンストラクタ
	FloatBehavior(const float& floatRange,const float& floatCycleSpeed , const float& floatSpeed,
		const DirectX::SimpleMath::Vector3& direction);
	// デストラクタ
	~FloatBehavior() override = default;

private:


	// 有効かどうかのフラグ
	bool m_isActive;
	// 経過時間
	float m_elapsedTime;

	// 揺れ幅
	float m_floatRange;
	// 周期の速さ
	float m_floatCycleSpeed;
	// 速度
	float m_floatSpeed;
	// 方向
	DirectX::SimpleMath::Vector3 m_direction;
};