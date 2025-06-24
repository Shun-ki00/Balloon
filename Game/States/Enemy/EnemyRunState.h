#pragma once
#include "Interface/IState.h"

class Transform;
class Object;

class EnemyRunState : public IState
{
public:
	void SetIsForward(const bool& isForward) { m_isForward = isForward; }
	void SetIsBackward(const bool& isBackward) { m_isBackward = isBackward; }

public:
	// コンストラクタ
	EnemyRunState(Object* object);
	// デストラクタ
	~EnemyRunState() = default;
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

	// プレイヤーオブジェクト
	Object* m_object;
	
	bool m_isForward;
	bool m_isBackward;
};