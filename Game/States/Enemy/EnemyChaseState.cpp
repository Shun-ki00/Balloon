// ============================================
// 
// ファイル名: EnemyChaseState.h
// 概要: 敵　追いかける状態
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/States/Enemy/EnemyChaseState.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Object/Object.h"
#include "Game/SteeringBehavior/SeekBehavior.h"
#include "Game/SteeringBehavior/SteeringBehavior.h"
#include "Game/Enemy/Enemy.h"
#include "Interface/IObject.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="enemy">敵オブジェクト</param>
/// <param name="player">プレイヤーオブジェクト</param>
/// <param name="steeringBehavior">ステアリングビヘイビア</param>
/// <param name="seekBehavior">対象を追いかけるビヘイビア</param>
EnemyChaseState::EnemyChaseState(Object* enemy, Object* player, SteeringBehavior* steeringBehavior, SeekBehavior* seekBehavior)
{
	m_enemy        = enemy;
	m_player       = player;
    m_seekBehavior = seekBehavior;
    m_steeringBehavior = steeringBehavior;
}

/// <summary>
/// 初期化処理
/// </summary>
void EnemyChaseState::Initialize()
{

}

/// <summary>
/// 事前処理
/// </summary>
void EnemyChaseState::PreUpdate()
{
    // ビヘイビアをオンにする
    m_steeringBehavior->On(BEHAVIOR_TYPE::SEEK);

    // プレイヤーの位置を取得
    DirectX::SimpleMath::Vector3 playerPos = m_player->GetTransform()->GetLocalPosition();
    // 敵の位置を取得
    DirectX::SimpleMath::Vector3 enemyPos  = m_enemy->GetTransform()->GetLocalPosition();

    // 差分ベクトル（向きたい方向）
    DirectX::SimpleMath::Vector3 direction = playerPos - enemyPos;

    // ベクトルがゼロでないかチェック
    if (direction.LengthSquared() > 0.0001f)
    {
        // 回転角（Yaw）に変換
        float yaw = std::atan2(direction.x, direction.z);
        float deg = DirectX::XMConvertToDegrees(yaw);

        // Y軸回転Tween（例: 0.3秒かけて回転）
        m_enemy->GetTransform()->GetTween()->DORotationY(-deg, 0.3f);
    }
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void EnemyChaseState::Update(const float& elapsedTime)
{
    UNREFERENCED_PARAMETER(elapsedTime);

    // SeekBehaviorによって算出されたベクトルの向きを取得する
    DirectX::SimpleMath::Vector3 velocity = m_seekBehavior->GetDirection();

    // ベクトルが有効なら向きを更新
    if (velocity.LengthSquared() > 0.0001f)
    {
        float yaw = std::atan2(velocity.x, velocity.z);
    
        m_enemy->GetTransform()->SetLocalRotation(
            DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, yaw)
        );
    }
}

/// <summary>
/// 事後処理
/// </summary>
void EnemyChaseState::PostUpdate()
{
    m_steeringBehavior->Off(BEHAVIOR_TYPE::SEEK);
}

/// <summary>
/// 終了処理
/// </summary>
void EnemyChaseState::Finalize()
{

}