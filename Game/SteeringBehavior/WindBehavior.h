// ============================================
// 
// ファイル名: WindBehavior.h
// 概要: WindBehavior.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/ISteeringBehavior.h"
#include <random>


class WindBehavior : public ISteeringBehavior
{
public:

    // 風を生成
    void GenerateNewWind();

    // ビヘイビアを有効にする
    void On() override;
    // ビヘイビアを無効にする
    void Off() override;

    // ステアリング力を計算する
    DirectX::SimpleMath::Vector3 Calculate() override;
    // 更新で風を変化させる
    void Update(float deltaTime);

private:
    //	コンストラクタ
    WindBehavior();
    //	デストラクタ
    ~WindBehavior() = default;
public:
    WindBehavior(const WindBehavior&) = delete;             // コピー禁止
    WindBehavior& operator=(const WindBehavior&) = delete;  // コピー代入禁止
    WindBehavior(const WindBehavior&&) = delete;            // ムーブ禁止
    WindBehavior& operator=(const WindBehavior&&) = delete; // ムーブ代入禁止

    //	シングルトンインスタンスの取得
    static WindBehavior* GetInstance()
    {
        static WindBehavior instance;
        return &instance;
    }

private:

    // 有効かどうかのフラグ
    bool m_isActive;

    // ランダム生成器
    mutable std::default_random_engine m_rng;
    // 風の強さを決めるための分布（最小～最大）
    std::uniform_real_distribution<float> m_strengthDist;
    // 風の方向ベクトルを決めるための分布（-1.0～1.0）
    std::uniform_real_distribution<float> m_dirDist;
    // 風の継続時間を決めるための分布（最短～最長）
    std::uniform_real_distribution<float> m_timeDist;   

    // 現在風が吹いているかどうかのフラグ
    bool m_isWind;
    // 経過時間
    float m_timer;
    // 継続時間
    float m_idleTime;
    // 風の時間
    float m_windTimer;
    // 現在の風の継続時間
    float m_currentDuration;                        
    // 現在の風ベクトル
    DirectX::SimpleMath::Vector3 m_currentWind;     
};