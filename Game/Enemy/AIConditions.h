#pragma once

class Object;
class Player;

class AIConditions
{
public:
	// 対象のオブジェクトを設定する
	void SetTargetObject(Player* player) { m_player = player; }

	// AIConditionsクラスのインスタンスを取得する
	static AIConditions* GetInstance();
	// AIConditionsのクラスのインスタンスを破棄する
	static void DestroyInstance();
	// コンストラクタ
	AIConditions();
	// デストラクタ
	~AIConditions();

	// プレイヤーより上にいるかどうか
	bool IsAbovePlayer(Object* enemy, float heightOffset = 3.5f);
	// プレイヤーより下にいるかどうか
	bool IsBelowPlayer(Object* enemy, float heightOffset = 3.5f);
	// プレイヤーの視野内にいるかどうか
	bool IsPlayerVisible(Object* enemy);
	// プレイヤーの一定範囲内にいるかどうか
	bool IsPlayerInRange(Object* enemy,DirectX::SimpleMath::Vector3 offset , float range);

private:

	// AIConditions
	static std::unique_ptr<AIConditions> s_aiConditions;

	// 対象のオブジェクト
	Player* m_player;

};