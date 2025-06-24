#include "pch.h"
#include "Game/SteeringBehavior/SteeringBehavior.h"
#include "Interface/ISteeringBehavior.h"

/// <summary>
/// コンストラクタ
/// </summary>
SteeringBehavior::SteeringBehavior()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void SteeringBehavior::Initialize()
{

}

/// <summary>
/// 計算処理を行う
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>計算結果</returns>
DirectX::SimpleMath::Vector3 SteeringBehavior::Calculate(const float& elapsedTime)
{
	// 合成ステアリングベクトル
	DirectX::SimpleMath::Vector3 steeringForce = DirectX::SimpleMath::Vector3::Zero;

	// ビヘイビアすべてを走査
	for (const auto& [flag, behavior] : m_behaviors)
	{
		// 対象ビヘイビアのビットがONか確認
		if ((m_flags & flag) == flag && behavior)
		{
			// 各ビヘイビアの力を加算
			steeringForce += behavior->Calculate();
		}
	}

	return steeringForce;
}

/// <summary>
/// ステアリングビヘイビアを追加する
/// </summary>
/// <param name="flag">フラグの種類</param>
/// <param name="steeringBehavior">ステアリングビヘイビア</param>
void SteeringBehavior::Attach(BEHAVIOR_TYPE flag, std::unique_ptr<ISteeringBehavior> steeringBehavior)
{
	// ステアリングビヘイビアを追加する
	m_behaviors[flag] = std::move(steeringBehavior);

	// ビットフラグをONにする
	m_flags |= flag;
}

/// <summary>
/// ステアリングビヘイビアを取得する
/// </summary>
/// <param name="flags">フラグ</param>
/// <returns>ステアリングビヘイビア</returns>
ISteeringBehavior* SteeringBehavior::GetSteeringBehavior(BEHAVIOR_TYPE flags)
{
	// 検索
	auto it = m_behaviors.find(flags);

	// ステアリングビヘイビアが見つかれば返す
	if (it != m_behaviors.end())
		return it->second.get();

	// 見つからない場合はnullptrを返す
	return nullptr;
}

/// <summary>
/// ステアリングビヘイビアを有効にする
/// </summary>
/// <param name="flags">フラグ</param>
void SteeringBehavior::On(BEHAVIOR_TYPE flag)
{
	// ビットを立てる
	m_flags |= flag;
}

/// <summary>
/// ステアリングビヘイビアを無効にする
/// </summary>
/// <param name="flags">フラグ</param>
void SteeringBehavior::Off(BEHAVIOR_TYPE flag)
{
	// ビットを落とす
	m_flags ^= flag;
}