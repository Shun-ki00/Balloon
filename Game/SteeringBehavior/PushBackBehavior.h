// ============================================
// 
// ファイル名: PushBackBehavior.h
// 概要: PushBackBehavior.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/ISteeringBehavior.h"


class PushBackBehavior : public ISteeringBehavior
{
public:

    // ビヘイビアを有効にする
    void On() override;
    // ビヘイビアを無効にする
    void Off() override;

    // ステアリング力を計算する
    DirectX::SimpleMath::Vector3 Calculate() override;

    // コンストラクタ
    PushBackBehavior(IObject* object);
    // デストラクタ
    ~PushBackBehavior() override = default;

private:

    // ステージの範囲
    static const DirectX::SimpleMath::Vector3 STAGE_MIN_BOUNDS;
    static const DirectX::SimpleMath::Vector3 STAGE_MAX_BOUNDS;
    // 押し戻す力
    static const float PUSH_BACK_STRENGTH;



private:

    // 有効かどうかのフラグ
    bool m_isActive;

    // 対象オブジェクト
    IObject* m_object;            
};