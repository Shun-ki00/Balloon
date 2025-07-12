// ============================================
// 
// ファイル名: EnemyAttackState.h
// 概要: EnemyAttackState.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class Object;

class EnemyAttackState : public IState
{
public:
	// コンストラクタ
	EnemyAttackState(Object* enemy);
	// デストラクタ
	~EnemyAttackState() = default;
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

	// 敵オブジェクト
	Object* m_enemy;
	// 経過時間
	float m_elapsedTime;
	// 移動時間
	float m_moveingTime;
};