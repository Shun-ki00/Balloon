// ============================================
// 
// ファイル名: PlayerRunState.h
// 概要: PlayerRunState.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class Transform;
class Object;

class PlayerRunState : public IState
{
public:
	void SetIsForward(const bool& isForward) { m_isForward = isForward; }
	void SetIsBackward(const bool& isBackward) { m_isBackward = isBackward; }

public:
	// コンストラクタ
	PlayerRunState(Object* object);
	// デストラクタ
	~PlayerRunState() = default;
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