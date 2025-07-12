// ============================================
// 
// ファイル名: EnemyIdleState.h
// 概要: EnemyIdleState.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class EnemyIdleState : public IState
{
public:
	// コンストラクタ
	EnemyIdleState();
	// デストラクタ
	~EnemyIdleState() override = default;
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
};