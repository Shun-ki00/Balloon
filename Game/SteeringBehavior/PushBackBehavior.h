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

    // 有効かどうかのフラグ
    bool m_isActive;

    // 対象オブジェクト
    IObject* m_object;     

    // ステージ最小座標
    DirectX::SimpleMath::Vector3 m_stageMinBounds; 
    // ステージ最大座標
    DirectX::SimpleMath::Vector3 m_stageMaxBounds;  
    // 押し戻し力
    float m_pushBackStrength;                     
};