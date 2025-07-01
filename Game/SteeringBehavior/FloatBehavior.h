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
	FloatBehavior();
	// デストラクタ
	~FloatBehavior() override = default;

private:

	// 揺れているかのフラグ
	bool m_isFloat;

	// 揺れる高さの最大値
	float m_amplitude;

	// 揺れるスピード
	float m_floatSpeed;

	// 揺れる向き
	DirectX::SimpleMath::Vector3 m_direction;

	// 経過時間
	float m_elapsedTime;

	float m_frequency;

};