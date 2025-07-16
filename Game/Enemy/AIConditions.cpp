#include "pch.h"
#include "Game/Enemy/AIConditions.h"
#include "Game/Player/Player.h"
#include "Game/Object/Object.h"
#include "Framework/DebugRenderer.h"

// AIConditions
std::unique_ptr<AIConditions> AIConditions::s_aiConditions = nullptr;

// AIConditionsクラスのインスタンスを取得する
AIConditions* AIConditions::GetInstance()
{
	if (s_aiConditions == nullptr)
	{
		// AIConditionsクラスのインスタンスを生成する
		s_aiConditions.reset(new AIConditions());
	}

	// AIConditionsクラスのインスタンスを返す
	return s_aiConditions.get();
}

void AIConditions::DestroyInstance()
{
	s_aiConditions.release();
}


AIConditions::AIConditions()
{

}


AIConditions::~AIConditions()
{

}

/// <summary>
/// プレイヤーの上にいるかどうか
/// </summary>
/// <param name="enemy">敵オブジェクト</param>
/// <param name="heightOffset">オフセット</param>
/// <returns>結果</returns>
bool AIConditions::IsAbovePlayer(Object* enemy, float heightOffset)
{
	// プレイヤーが未設定なら失敗
	if (!m_player) return false;

	// プレイヤーのオフセット座標
	float playerOffset =
		m_player->GetTransform()->GetLocalPosition().y + heightOffset;
	// 敵のオフセット座標
	float enemyHeight = enemy->GetTransform()->GetLocalPosition().y;

	DebugRenderer::GetInstance()->Attach({ {m_player->GetTransform()->GetLocalPosition().x , playerOffset , m_player->GetTransform()->GetLocalPosition().z} ,2.2f});

	// プレイヤーの上にいる場合trueを返す
	return enemyHeight >= playerOffset;
}


/// <summary>
/// プレイヤーの下にいるかどうか
/// </summary>
/// <param name="enemy">敵オブジェクト</param>
/// <param name="heightOffset">オフセット</param>
/// <returns>結果</returns>
bool AIConditions::IsBelowPlayer(Object* enemy, float heightOffset)
{
	// プレイヤーが未設定なら失敗
	if (!m_player) return false;

	// プレイヤーのオフセット座標
	float playerOffset =
		m_player->GetTransform()->GetLocalPosition().y + heightOffset;
	// 敵のオフセット座標
	float enemyHeight = enemy->GetTransform()->GetLocalPosition().y;

	// プレイヤーの下にいる場合trueを返す
	return enemyHeight <= playerOffset;
}

/// <summary>
/// プレイヤーの視野内にいるかどうか
/// </summary>
/// <param name="enemy"></param>
/// <returns></returns>
bool AIConditions::IsPlayerVisible(Object* enemy)
{
	if (!m_player) return false;

	// プレイヤーから敵への方向ベクトルを計算
	DirectX::SimpleMath::Vector3 toTarget = enemy->GetTransform()->GetLocalPosition() - m_player->GetTransform()->GetLocalPosition();

	// プレイヤーの前方ベクトル
	DirectX::SimpleMath::Vector3 forward = 
		DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward,
		m_player->GetTransform()->GetLocalRotation());

	// 単位ベクトルに正規化
	toTarget.Normalize();
	forward.Normalize();

	// 視線とターゲット方向ベクトルの角度をDot積で比較
	float dot = forward.Dot(toTarget);
	return dot > 0.866f; // ≒ 視野60度以内
}

/// <summary>
/// プレイヤーの一定範囲内に敵がいるかどうかを判定する
/// </summary>
/// <param name="enemy">敵オブジェクト</param>
/// <param name="offset">プレイヤー位置の補正（例：少し上や後ろ）</param>
/// <param name="range">有効範囲の半径</param>
/// <returns>範囲内なら true、範囲外なら false</returns>
bool AIConditions::IsPlayerInRange(Object* enemy, DirectX::SimpleMath::Vector3 offset, float range)
{
	if (!m_player || !enemy) return false;

	// プレイヤー位置に補正オフセットを加算した座標
	const DirectX::SimpleMath::Vector3 playerPosition = m_player->GetTransform()->GetLocalPosition() + offset;
	// 敵の現在位置
	const DirectX::SimpleMath::Vector3 enemyPosition = enemy->GetTransform()->GetLocalPosition();

	// プレイヤーと敵の距離の2乗（平方距離）を計算
	float distanceSquared = (playerPosition - enemyPosition).LengthSquared();
	// 許容範囲の半径の2乗（平方距離）を計算
	float rangeSquared = range * range;

	DebugRenderer::GetInstance()->Attach({ playerPosition , range });

	// 距離の平方が範囲の平方以下なら、範囲内と判定
	return distanceSquared <= rangeSquared;
}

