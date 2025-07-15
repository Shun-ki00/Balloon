#include "pch.h"
#include "Game/Particle/ParticleEmitter.h"
#include "Framework/Resources/Resources.h"
#include "Framework/CommonResources.h"
#include "Game/Particle/Particle.h"
#include "Framework/Utilities/RandomUtilities.h"
#include "Game/Parameters/ParameterBuffers.h"
#include <random>

/// <summary>
/// �R���X�g���N�^
/// </summary>
ParticleEmitter::ParticleEmitter(const ParticleParameters& parametersData)
{
    m_particleParameters = parametersData;
}

/// <summary>
/// ����������
/// </summary>
void ParticleEmitter::Initialize()
{

    // ���q��p��
    const size_t poolSize = 256;
    m_particles.reserve(poolSize);
    for (size_t i = 0; i < poolSize; ++i) {
        m_particles.emplace_back(std::make_unique<Particle>());
    }

    // �p�����[�^�̃f�[�^��ݒ�


    auto textureKey = magic_enum::enum_cast<TextureKeyID>(m_particleParameters.texture);
    auto shaderKey  = magic_enum::enum_cast<PS_ID>(m_particleParameters.shader);

    // �e�N�X�`����ݒ�
    m_texture = Resources::GetInstance()->GetTextureResources()->GetTexture(
        textureKey.value()
    );
    // �V�F�[�_�[��ݒ�
    m_pixelShader = Resources::GetInstance()->GetShaderResources()->GetPixelShader(
        shaderKey.value()
    );

    // �����͔�A�N�e�B�u
    m_isActive = false;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void ParticleEmitter::Update(const float& elapsedTime)
{
    if (!m_particleParameters.isPlaying)
        return;

    // �o�ߎ��Ԃ��X�V
    m_elapsedTime += elapsedTime;

    // ���[�v���Ȃ��ꍇ�Aduration �𒴂������~
    if (!m_particleParameters.isLooping && m_elapsedTime > m_duration)
    {
        Stop();
        return;
    }

    // �G�~�b�V��������
    static float emissionTimer = 0.0f;
    emissionTimer += elapsedTime;

    // �����^�C�~���O�ɒB������ Emit()
    float emitInterval = 1.0f / m_particleParameters.emissionRate;
    while (emissionTimer >= emitInterval)
    {
        Emit(); // �p�[�e�B�N���𔭐�������
        emissionTimer -= emitInterval;
    }

    m_inputDatas.clear();

    // �A�N�e�B�u�p�[�e�B�N���̍X�V
    for (auto it = m_activeParticles.begin(); it != m_activeParticles.end(); )
    {
        Particle* p = *it;
        p->Update(elapsedTime);

        if (!p->GetIsActive())
        {
            // �������s���Ĕ�A�N�e�B�u�ɂȂ����ꍇ�A���X�g����폜
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
/// �J�n����
/// </summary>
void ParticleEmitter::Play()
{
}

/// <summary>
/// ��~����
/// </summary>
void ParticleEmitter::Stop()
{
}


/// <summary>
/// ���q��������
/// </summary>
void ParticleEmitter::Emit()
{
    DirectX::SimpleMath::Vector3 outPosition;
    DirectX::SimpleMath::Vector3 outVelocity;
    switch (m_shape)
    {
        case ParticleEmitter::Shape::CONE:

            // �����_������
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

            // �����_������
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


    // --- ���� ---
    float lifetime = m_particleParameters.lifeTime;

    // --- �T�C�Y ---
    float startSize = m_particleParameters.startScale.x;
    float endSize = m_particleParameters.startScale.x;

    // --- �F ---
    DirectX::SimpleMath::Vector4 startColor = m_particleParameters.startColor;
    DirectX::SimpleMath::Vector4 endColor = m_particleParameters.startColor;

    // --- �����x ---
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