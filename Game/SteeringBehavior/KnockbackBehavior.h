// ============================================
// 
// ファイル名: KnockbackBehavior.h
// 概要: KnockbackBehavior.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/ISteeringBehavior.h"

class Object;
class IObject;

class KnockbackBehavior : public ISteeringBehavior
{

public:

    // ターゲットオブジェクトを設定する
    void SetTargetObject(IObject* target) { m_targets.push_back(target); }
    void SetTargetObject(std::vector<IObject*> targets) 
    {
        for (const auto& target : targets)
            m_targets.push_back(target);
    }
    // ターゲットをリセットする
    void ResetTargetObject() { m_targets.clear(); }

    // ビヘイビアを有効にする
    void On() override;
    // ビヘイビアを無効にする
    void Off() override;

    // コンストラクタ
    KnockbackBehavior(Object* object,
        const float& knockbackRadius,const int& knockbackCount,const float& knockbackFoce);
    // デストラクタ
    ~KnockbackBehavior() override = default;

    // ステアリング力を計算する
    DirectX::SimpleMath::Vector3 Calculate() override;

private:

    // ノックバック範囲内か計算する
    bool IsWithinKnockbackRange();
  
private:

    // 有効かどうかのフラグ
    bool m_isActive;

    // ノックバック対象
    Object* m_object;
    // ターゲット
    std::vector<IObject*> m_targets;

    // 発生半径
    float m_knockbackRadius;
    // ノックバック回数
    int m_knockbackCount;
    // ノックバック力
    float m_knockbackFoce;
    // ノックバック済みか
    bool m_isKnockedBack;

    int m_count;
};