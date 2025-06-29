#pragma once
#include "Interface/IState.h"

class Object;

class EnemyAttackState : public IState
{
public:
	// コンストラクタ
	EnemyAttackState(Object* player);
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

public:

private:

	Object* m_player;

	float m_elapsedTime;

	float m_moveingTime;
};