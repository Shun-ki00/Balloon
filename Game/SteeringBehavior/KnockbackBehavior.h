#pragma once
#include "Interface/ISteeringBehavior.h"

class Object;

class KnockbackBehavior : public ISteeringBehavior
{

public:

    // ターゲットオブジェクトを設定する
    void SetTargetObject(Object* target) { m_target = target; }

    // ビヘイビアを有効にする
    void On() override;
    // ビヘイビアを無効にする
    void Off() override;

    // コンストラクタ
    KnockbackBehavior(Object* object);
    // デストラクタ
    ~KnockbackBehavior() override = default;

    // ステアリング力を計算する
    DirectX::SimpleMath::Vector3 Calculate() override;

    // ノックバック範囲内か計算する
    bool IsWithinKnockbackRange();
  
private:

    // 有効かどうかのフラグ
    bool m_isActive;

    // ノックバック対象
    Object* m_object;
    // ターゲット
    Object* m_target;

    // ノックバック回数
    int m_knockbackCount;
    // 発生半径
    float m_knockbackRadius;
    // ノックバック力
    float m_knockbackFoce;
    // ノックバック済みか
    bool m_isKnockedBack;

    int m_count;
};