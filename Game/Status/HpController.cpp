#include "pch.h"
#include "Game/Status/HpController.h"
#include "Game/SteeringBehavior/FloatForceBehavior.h"
#include "Game/Message/ObjectMessenger.h"

/// <summary>
/// コンストラクタ
/// </summary>
HpController::HpController()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void HpController::Initialize()
{
    // 初期HP
    m_hp = 1.0f;
    // 最大HP
    m_maxHp = 1.0f;

    m_targetHp = m_hp;
    m_reduceSpeed = 0.5f;

    m_isReducing = false;
    m_isRecovering = false;
    m_recoverDelayTimer = 0.0f;
    m_recoverDelay = 3.0f;
    m_recoverSpeed = 0.25f;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void HpController::Update(const float& elapsedTime)
{
    // HP減少処理
    if (m_isReducing)
    {
        float delta = m_reduceSpeed * elapsedTime;

        if (m_hp - delta <= m_targetHp)
        {
            m_hp = m_targetHp;
            m_isReducing = false;

            // 減少完了後、遅延タイマーを開始
            m_recoverDelayTimer = 0.0f;
        }
        else
        {
            m_hp -= delta;
        }

        // HPをUIへ通知
        ObjectMessenger::GetInstance()->Dispatch(
            IObject::ObjectID::HP_GAUGE_UI,
            { Message::MessageID::HP_GAUGE, 0, m_hp, false }
        );

        return; // 減少中は回復処理を行わない
    }

    // HP回復開始のディレイタイマー進行
    if (!m_isRecovering && m_hp < m_maxHp)
    {
        m_recoverDelayTimer += elapsedTime;
        if (m_recoverDelayTimer >= m_recoverDelay)
        {
            m_isRecovering = true;
        }
    }

    // 回復処理
    if (m_isRecovering)
    {
        float delta = m_recoverSpeed * elapsedTime;

        if (m_hp + delta >= m_maxHp)
        {
            m_hp = m_maxHp;
            m_isRecovering = false;
        }
        else
        {
            m_hp += delta;
        }

        m_targetHp = m_hp;
    }

    // HPをUIへ通知
    ObjectMessenger::GetInstance()->Dispatch(
        IObject::ObjectID::HP_GAUGE_UI,
        { Message::MessageID::HP_GAUGE, 0, m_hp, false }
    );
}


/// <summary>
/// HPを減らす
/// </summary>
/// <param name="hp">減らす量</param>
/// <returns>減らせれたかどうか</returns>
bool HpController::HpReduction(const float& amount)
{
    float requestedHp = m_targetHp - amount;

    if (requestedHp < 0.0f)
        return false;

    // 回復中ならキャンセル
    if (m_isRecovering)
    {
        m_isRecovering = false;
    }

    // 遅延タイマーも初期化（再度リセット）
    m_recoverDelayTimer = 0.0f;

    // 減少ターゲット更新
    m_targetHp = requestedHp;
    m_isReducing = true;

    return true;

}