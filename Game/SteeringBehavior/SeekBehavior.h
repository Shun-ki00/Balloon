#pragma once
#include "Interface/ISteeringBehavior.h"

class Object;


class SeekBehavior : public ISteeringBehavior
{
public:
    

    // ベクトルの向きを取得する
    DirectX::SimpleMath::Vector3 GetDirection() const { return m_direction; }

    // ビヘイビアを有効にする
    void On() override;
    // ビヘイビアを無効にする
    void Off() override;

    // ステアリング力を計算する
    DirectX::SimpleMath::Vector3 Calculate() override;

    // コンストラクタ
    SeekBehavior(Object* object , Object* target);
    // デストラクタ
    ~SeekBehavior() override = default;

private:

    // 有効かどうかのフラグ
    bool m_isActive;

    // オブジェクト
    Object* m_object;
    // 追尾するオブジェクト
    Object* m_target;

    // ベクトルの向き
    DirectX::SimpleMath::Vector3 m_direction;
    
    // 位置のオフセット
    float m_distance;
    // 予測時間の倍率
    float m_predictionMultiplier;
    // 移動速度
    float m_seekSpeed;
};