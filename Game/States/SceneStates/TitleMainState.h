#pragma once
#include "Interface/IState.h"

class InputManager;
class IScene;

class TitleMainState : public IState
{
public:
	// コンストラクタ
	TitleMainState();
	// デストラクタ
	~TitleMainState() = default;
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

	// インプットマネージャー
	InputManager* m_inputManager;

};