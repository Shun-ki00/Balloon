#include "pch.h"
#include "Game/Particle/ParticleEmitter.h"
#include "Framework/Resources/Resources.h"
#include "Framework/CommonResources.h"
#include "Game/Particle/Particle.h"
#include "Framework/Utilities/RandomUtilities.h"
#include "Game/Parameters/ParameterBuffers.h"
#include <random>

/// <summary>
/// コンストラクタ
/// </summary>
ParticleEmitter::ParticleEmitter(const ParticleParameters& parametersData)
{
    m_particleParameters = parametersData;
}

/// <summary>
/// 初期化処理
/// </summary>
void ParticleEmitter::Initialize()
{

    // 粒子を用意
    const size_t poolSize = 256;
    m_particles.reserve(poolSize);
    for (size_t i = 0; i < poolSize; ++i) {
        m_particles.emplace_back(std::make_unique<Particle>());
    }

    // パラメータのデータを設定


    auto textureKey = magic_enum::enum_cast<TextureKeyID>(m_particleParameters.texture);
    auto shaderKey  = magic_enum::enum_cast<PS_ID>(m_particleParameters.shader);

    // テクスチャを設定
    m_texture = Resources::GetInstance()->GetTextureResources()->GetTexture(
        textureKey.value()
    );
    // シェーダーを設定
    m_pixelShader = Resources::GetInstance()->GetShaderResources()->GetPixelShader(
        shaderKey.value()
    );

    // 初期は非アクティブ
    m_isActive = false;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void ParticleEmitter::Update(const float& elapsedTime)
{
    if (!m_particleParameters.isPlaying)
        return;

    // 経過時間を更新
    m_elapsedTime += elapsedTime;

    // ループしない場合、duration を超えたら停止
    if (!m_particleParameters.isLooping && m_elapsedTime > m_duration)
    {
        Stop();
        return;
    }

    // エミッション処理
    static float emissionTimer = 0.0f;
    emissionTimer += elapsedTime;

    // 発生タイミングに達したら Emit()
    float emitInterval = 1.0f / m_particleParameters.emissionRate;
    while (emissionTimer >= emitInterval)
    {
        Emit(); // パーティクルを発生させる
        emissionTimer -= emitInterval;
    }

    m_inputDatas.clear();

    // アクティブパーティクルの更新
    for (auto it = m_activeParticles.begin(); it != m_activeParticles.end(); )
    {
        Particle* p = *it;
        p->Update(elapsedTime);

        if (!p->GetIsActive())
        {
            // 寿命が尽きて非アクティブになった場合、リストから削除
            it = m_activeParticles.erase(it);
        }
        else
        {
            m_inputDatas.push_back(p->GetVertexData());
            ++it;
        }
    }
}

/// <summary>
/// 開始処理
/// </summary>
void ParticleEmitter::Play()
{
}

/// <summary>
/// 停止処理
/// </summary>
void ParticleEmitter::Stop()
{
}


/// <summary>
/// 粒子発生処理
/// </summary>
void ParticleEmitter::Emit()
{
    DirectX::SimpleMath::Vector3 outPosition;
    DirectX::SimpleMath::Vector3 outVelocity;
    switch (m_shape)
    {
        case ParticleEmitter::Shape::CONE:

            // ランダム生成
            RandomUtilities::GenerateConeEmissio(
                m_particleParameters.coneAngle,
                m_particleParameters.coneRadius,
                m_particleParameters.coneHeight,
                m_particleParameters.coneEmitFromShell,
                m_particleParameters.conePosition,
                outPosition,
                outVelocity
            );

            break;
        case ParticleEmitter::Shape::SPHERE:

            // ランダム生成
            RandomUtilities::GenerateSphereEmission(
                m_particleParameters.sphereRadius,
                m_particleParameters.sphereEmitFromShell,
                m_particleParameters.sphereCenter,
                m_particleParameters.sphereRandomDirectionStrength,
                outPosition,
                outVelocity
            );

            break;
        default:
            break;
    }


    // --- 寿命 ---
    float lifetime = m_particleParameters.lifeTime;

    // --- サイズ ---
    float startSize = m_particleParameters.startScale.x;
    float endSize = m_particleParameters.startScale.x;

    // --- 色 ---
    DirectX::SimpleMath::Vector4 startColor = m_particleParameters.startColor;
    DirectX::SimpleMath::Vector4 endColor = m_particleParameters.startColor;

    // --- 加速度 ---
    DirectX::SimpleMath::Vector3 acceleration = DirectX::SimpleMath::Vector3::Zero;

    for (auto& p : m_particles)
    {
        if (!p->GetIsActive())
        {
            p->SetParameters(
                outPosition,
                outVelocity,
                acceleration,
                lifetime,
                startSize,
                endSize,
                startColor,
                endColor
            );
            m_activeParticles.push_back(p.get());
            break;
        }
    }
}