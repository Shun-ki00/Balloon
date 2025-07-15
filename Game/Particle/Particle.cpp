#include "pch.h"
#include "Game/Particle/Particle.h"

/// <summary>
/// コンストラクタ
/// </summary>
Particle::Particle()
{
    m_isActive = false;
}

/// <summary>
/// 初期化処理
/// </summary>
void Particle::Initialize()
{
    m_inputData = {};

    m_position     = DirectX::SimpleMath::Vector3::Zero;
    m_velocity     = DirectX::SimpleMath::Vector3::Zero;
    m_acceleration = DirectX::SimpleMath::Vector3::Zero;

    m_totalLifetime = 0.0f;
    m_currentLifetime = m_totalLifetime;

    m_startSize = 1.0f;
    m_endSize   = 1.0f;
    m_startColor = DirectX::SimpleMath::Vector4::One;
    m_endColor   = DirectX::SimpleMath::Vector4::One;

    m_isActive = false;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Particle::Update(const float& elapsedTime)
{
    if (!m_isActive) return;

    // 時間を減らす
    m_currentLifetime -= elapsedTime;
    if (m_currentLifetime <= 0.0f) {
        m_currentLifetime = 0.0f;

        m_isActive = false;
        return;
    }

    // 位置更新
    m_velocity += m_acceleration * elapsedTime;
    m_position += m_velocity * elapsedTime;

    // 残り時間の割合
    float lifeRatio = (m_totalLifetime > 0.0f) ? (1.0f - (m_currentLifetime / m_totalLifetime)) : 1.0f;
    lifeRatio = std::clamp(lifeRatio, 0.0f, 1.0f);

    // サイズ補間
    m_currentSize = m_startSize + (m_endSize - m_startSize) * lifeRatio;
    // カラー補間
    m_currentColor = m_startColor + (m_endColor - m_startColor) * lifeRatio;

    // 頂点データの更新
    m_inputData.position = m_position;
    m_inputData.color = m_currentColor;
    m_inputData.textureCoordinate.x = m_currentSize;
}

/// <summary>
/// 値を設定する
/// </summary>
/// <param name="position"></param>
/// <param name="velocity"></param>
/// <param name="acceleration"></param>
/// <param name="lifetime"></param>
/// <param name="startSize"></param>
/// <param name="endSize"></param>
/// <param name="startColor"></param>
/// <param name="endColor"></param>
void Particle::SetParameters(
    const DirectX::SimpleMath::Vector3& position,
    const DirectX::SimpleMath::Vector3& velocity,
    const DirectX::SimpleMath::Vector3& acceleration,
    const float& lifetime,
    const float& startSize,
    const float& endSize,
    const DirectX::SimpleMath::Vector4& startColor,
    const DirectX::SimpleMath::Vector4& endColor
)
{
    m_position = position;
    m_velocity = velocity;
    m_acceleration = acceleration;
    m_totalLifetime = lifetime;
    m_currentLifetime = m_totalLifetime;
    m_startSize = startSize;
    m_endSize = endSize;
    m_startColor = startColor;
    m_endColor = endColor;

    m_isActive = true;
}
