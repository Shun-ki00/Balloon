// ============================================
// 
// ファイル名: PlayerAttackState.h
// 概要: PlayerAttackState.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class Object;

class PlayerAttackState : public IState
{
public:
	// コンストラクタ
	PlayerAttackState(Object* player);
	// デストラクタ
	~PlayerAttackState() = default;
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