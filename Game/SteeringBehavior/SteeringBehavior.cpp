#include "pch.h"
#include "Game/SteeringBehavior/SteeringBehavior.h"
#include "Game/SteeringBehavior/WindBehavior.h"
#include "Interface/ISteeringBehavior.h"

/// <summary>
/// コンストラクタ
/// </summary>
SteeringBehavior::SteeringBehavior()
	:
	m_windBehavior{},
	m_behaviors{},
	m_flags{},
	m_targetObject{}
{
	// インスタンスを取得する
	m_windBehavior = WindBehavior::GetInstance();
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
	UNREFERENCED_PARAMETER(elapsedTime);

	// 合成ステアリングベクトル
	DirectX::SimpleMath::Vector3 steeringForce = DirectX::SimpleMath::Vector3::Zero;

	// 共通のビヘイビアがオンの時は加算する
	if ((m_flags & BEHAVIOR_TYPE::WIND) != 0 && m_windBehavior)
	{
		steeringForce += m_windBehavior->Calculate();
	}

	// ビヘイビアすべてを走査
	for (const auto& [flag, behavior] : m_behaviors)
	{
		// 対象ビヘイビアのビットがONか確認
		if ((m_flags & flag) && behavior)
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
	// 同じ種類のビヘイビアは登録しない
	for (const auto& pair : m_behaviors)
	{
		if (pair.first == flag) return;
	}
	// ビヘイビアの登録
	m_behaviors.emplace_back(flag, std::move(steeringBehavior));

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
	// 検索して見つかれば返す
	for (const auto& behabior : m_behaviors)
	{
		if (behabior.first == flags)
			return behabior.second.get();
	}

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