// ============================================
// 
// ファイル名: EnemyChaseState.h
// 概要: EnemyChaseState.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IState.h"
#include "Interface/IObject.h"
#include "Game/Object/Object.h"

class Object;
class SeekBehavior;
class SteeringBehavior;

class EnemyChaseState : public IState
{
public:
	// コンストラクタ
	EnemyChaseState(Object* enemy , Object* player , SteeringBehavior* steeringBehavior, SeekBehavior* seekBehavior);
	// デストラクタ
	~EnemyChaseState() override = default;
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

	// 敵オブジェクト
	Object* m_enemy;
	// プレイヤーオブジェクト
	Object* m_player;

	// ステアリングビヘイビア
	SteeringBehavior* m_steeringBehavior;
	// 対象を追いかけるビヘイビア
	SeekBehavior* m_seekBehavior;
};