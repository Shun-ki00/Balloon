#include "pch.h"
#include "Game/Particle/ParticleEmitter.h"
#include "Framework/Resources/Resources.h"
#include "Framework/CommonResources.h"
#include "Game/Particle/Particle.h"
#include "Game/Parameters/ParameterKeys.h"
#include "Game/Parameters/Parameters.h"
#include <random>

ParticleEmitter::ParticleEmitter()
{
	m_parameters = Parameters::GetInstance();
}

void ParticleEmitter::Initialize(ParametersID id)
{

    const size_t poolSize = 256;
    m_particles.reserve(poolSize);
    for (size_t i = 0; i < poolSize; ++i) {
        m_particles.emplace_back(std::make_unique<Particle>());
    }

    m_emissionRate = m_parameters->GetParameter(id, ParameterKeysF::EmissionRate);
    m_emissionDuration = m_parameters->GetParameter(id, ParameterKeysF::EmissionDuration);
    m_particleLifetime = m_parameters->GetParameter(id, ParameterKeysF::ParticleLifetime);

    m_emitSpeedMin = m_parameters->GetParameter(id, ParameterKeysF::EmitSpeedMin);
    m_emitSpeedMax = m_parameters->GetParameter(id, ParameterKeysF::EmitSpeedMax);

    m_startSizeMin = m_parameters->GetParameter(id, ParameterKeysF::StartSizeMin);
    m_startSizeMax = m_parameters->GetParameter(id, ParameterKeysF::StartSizeMax);
    m_endSizeMin = m_parameters->GetParameter(id, ParameterKeysF::EndSizeMin);
    m_endSizeMax = m_parameters->GetParameter(id, ParameterKeysF::EndSizeMax);

    m_startRotationMin = m_parameters->GetParameter(id, ParameterKeysF::StartRotationMin);
    m_startRotationMax = m_parameters->GetParameter(id, ParameterKeysF::StartRotationMax);
    m_rotationSpeedMin = m_parameters->GetParameter(id, ParameterKeysF::RotationSpeedMin);
    m_rotationSpeedMax = m_parameters->GetParameter(id, ParameterKeysF::RotationSpeedMax);

    m_randomnessFactor = m_parameters->GetParameter(id, ParameterKeysF::RandomnessFactor);

    m_isLooping = m_parameters->GetParameter(id, ParameterKeysB::IsLooping);
    m_isGravityEnabled = m_parameters->GetParameter(id, ParameterKeysB::IsGravityEnabled);

    m_emitPositionMin = m_parameters->GetParameter(id, ParameterKeysV3::EmitPositionMin);
    m_emitPositionMax = m_parameters->GetParameter(id, ParameterKeysV3::EmitPositionMax);

    m_emitDirectionMin = m_parameters->GetParameter(id, ParameterKeysV3::EmitDirectionMin);
    m_emitDirectionMax = m_parameters->GetParameter(id, ParameterKeysV3::EmitDirectionMax);

    m_gravityAcceleration = m_parameters->GetParameter(id, ParameterKeysV3::GravityAcceleration);

    m_startColor = m_parameters->GetParameter(id, ParameterKeysV4::StartColor);
    m_endColor = m_parameters->GetParameter(id, ParameterKeysV4::EndColor);

    auto textureKey = magic_enum::enum_cast<TextureKeyID>(m_parameters->GetParameter(id, ParameterKeysS::Texture));
    auto shaderKey = magic_enum::enum_cast<PS_ID>(m_parameters->GetParameter(id, ParameterKeysS::Shader));

    // テクスチャを設定
    m_texture = Resources::GetInstance()->GetTextureResources()->GetTexture(
        textureKey.value()
    );

    // シェーダーを設定
    m_pixelShader = Resources::GetInstance()->GetShaderResources()->GetPixelShader(
        shaderKey.value()
    );

    m_isEmitting = false;
}


void ParticleEmitter::Update(const float& elapsedTime)
{
    if (!m_isEmitting) return;

    // エミット全体の残り時間を減らす
    m_emissionDurationTimer -= elapsedTime;
    if (m_emissionDurationTimer <= 0.0f)
    {
        // ループする場合
        if (m_isLooping)
        {
            // タイマーリセット
            m_emissionDurationTimer = m_emissionDuration;
        }
        // ループしない場合
        else
        {
            // 発生停止
            m_isEmitting = false;

            return;
        }
    }

    // エミット間隔管理
    m_emitTimer += elapsedTime;
    m_emissionInterval = (m_emissionRate > 0.0f) ? (1.0f / m_emissionRate) : FLT_MAX;

    // 粒子を間隔ごとに発生
    while (m_emitTimer >= m_emissionInterval)
    {
        this->Emit();

        m_emitTimer -= m_emissionInterval;
    }


    m_inputDatas.clear();

    auto it = m_activeParticles.begin();

    while (it != m_activeParticles.end()) 
    {
        Particle* p = *it;

        p->Update(elapsedTime);

        if (!p->GetIsActive()) 
        {
            it = m_activeParticles.erase(it);
        }
        else 
        {
            m_inputDatas.push_back({ p->GetPosition(),p->GetColor(), DirectX::SimpleMath::Vector2::Zero });
            ++it;                    
        }                           
    }


    //m_inputDatas.clear();

    //// 全粒子更新
    //for (auto& particle : m_particles)
    //{
    //    if (particle)
    //    {
    //        particle->Update(elapsedTime);

    //        // 頂点データを設定
    //        m_inputDatas.push_back(
    //            {
    //                particle->GetPosition(),
    //                particle->GetColor(),
    //                DirectX::SimpleMath::Vector2::Zero
    //            }
    //        );
    //    }
    //}

    //// 死亡粒子削除
    //m_particles.erase(
    //    std::remove_if(m_particles.begin(), m_particles.end(),
    //        [](const std::unique_ptr<Particle>& p) { return !p->GetIsActive(); }),
    //    m_particles.end()
    //);
}


void ParticleEmitter::Play()
{
    m_isEmitting = true;                   // 発生開始
    m_emitTimer = 0.0f;                     // 粒子発生間隔タイマーリセット
    m_emissionDurationTimer = m_emissionDuration; // 全体継続タイマーリセット
}

void ParticleEmitter::Stop()
{
    m_isEmitting = false;                   // 発生停止
    m_emitTimer = 0.0f;                     // タイマーリセット
    m_emissionDurationTimer = 0.0f;          // 継続時間もゼロにする
}



void ParticleEmitter::Emit()
{
    if (!m_isEmitting) return;

    // 乱数生成機
    static std::default_random_engine rng(std::random_device{}());

    // --- 位置 ---
    std::uniform_real_distribution<float> posX(m_emitPositionMin.x, m_emitPositionMax.x);
    std::uniform_real_distribution<float> posY(m_emitPositionMin.y, m_emitPositionMax.y);
    std::uniform_real_distribution<float> posZ(m_emitPositionMin.z, m_emitPositionMax.z);
    DirectX::SimpleMath::Vector3 position(posX(rng), posY(rng), posZ(rng));

    // --- 方向 ---
    std::uniform_real_distribution<float> dirX(m_emitDirectionMin.x, m_emitDirectionMax.x);
    std::uniform_real_distribution<float> dirY(m_emitDirectionMin.y, m_emitDirectionMax.y);
    std::uniform_real_distribution<float> dirZ(m_emitDirectionMin.z, m_emitDirectionMax.z);
    DirectX::SimpleMath::Vector3 direction(dirX(rng), dirY(rng), dirZ(rng));
    if (direction.Length() < 0.001f) direction = DirectX::SimpleMath::Vector3::UnitY;
    direction.Normalize();

    // --- 速度 ---
    std::uniform_real_distribution<float> speedDist(m_emitSpeedMin, m_emitSpeedMax);
    float speed = speedDist(rng);
    DirectX::SimpleMath::Vector3 velocity = direction * speed;

    // --- 寿命 ---
    float lifetime = m_particleLifetime;

    // --- サイズ ---
    std::uniform_real_distribution<float> startSizeDist(m_startSizeMin, m_startSizeMax);
    std::uniform_real_distribution<float> endSizeDist(m_endSizeMin, m_endSizeMax);
    float startSize = startSizeDist(rng);
    float endSize = endSizeDist(rng);

    // --- 色 ---
    DirectX::SimpleMath::Vector4 startColor = m_startColor;
    DirectX::SimpleMath::Vector4 endColor = m_endColor;

    // --- 加速度 ---
    DirectX::SimpleMath::Vector3 acceleration = m_isGravityEnabled ? m_gravityAcceleration : DirectX::SimpleMath::Vector3::Zero;

    for (auto& p : m_particles)
    {
        if (!p->GetIsActive()) 
        {
            p->Initialize(
                position,
                velocity,
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