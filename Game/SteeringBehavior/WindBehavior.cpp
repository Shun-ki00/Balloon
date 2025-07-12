// ============================================
// 
// ファイル名: WindBehavior.h
// 概要: 外部の風の力を与えるビヘイビア
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/SteeringBehavior/WindBehavior.h"
#include "Game/Parameters/Parameters.h"
#include "Game/Parameters/ParameterKeys.h"


/// <summary>
/// コンストラクタ
/// </summary>
WindBehavior::WindBehavior()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void WindBehavior::Update(float deltaTime) 
{
    // 風の挙動が無効なら何もしない
    if (m_isWind)
    {
        // 残り風継続時間を減らす
        m_windTimer -= deltaTime;

        // 時間切れで風を停止する
        if (m_windTimer <= 0.0f)
        {
            // 風を無効化
            m_isWind = false;
            // 風なしにリセット
            m_currentWind = DirectX::SimpleMath::Vector3::Zero; 
        }

        // 風が吹いてる間は何もしない
        return; 
    }

    // 風が止まっている時間を加算する
    m_timer += deltaTime;
    if (m_timer >= m_idleTime)
    {
        // 風を生成
        GenerateNewWind();
        m_timer = 0.0f;
    }

}


/// <summary>
/// 計算処理
/// </summary>
/// <returns>計算結果</returns>
DirectX::SimpleMath::Vector3 WindBehavior::Calculate() 
{
    return m_currentWind;
}


/// <summary>
/// 風を生成する
/// </summary>
void WindBehavior::GenerateNewWind() 
{
    // 新しい風の方向をランダム生成（XZ平面）
    DirectX::SimpleMath::Vector3 dir(m_dirDist(m_rng), 0.0f, m_dirDist(m_rng));

    // 万一ゼロベクトルならX方向に設定
    if (dir.Length() < 0.001f) dir = DirectX::SimpleMath::Vector3::UnitX;

    // 方向ベクトルを正規化
    dir.Normalize();

    // 風の強さをランダム生成
    float strength = m_strengthDist(m_rng);

    // 現在の風ベクトルを更新
    m_currentWind = dir * strength;

    // 風の継続時間をランダム生成
    m_currentDuration = m_timeDist(m_rng);

    // タイマーをリセット
    m_windTimer = m_currentDuration;

    // アクティブ状態にする
    m_isWind = true;
}

/// <summary>
/// 有効にする
/// </summary>
void WindBehavior::On()
{
    // フラグをオンにする
    m_isActive = true;
}

/// <summary>
/// 無効にする
/// </summary>
void WindBehavior::Off()
{
    // フラグをオフにする
    m_isActive = false;
}
