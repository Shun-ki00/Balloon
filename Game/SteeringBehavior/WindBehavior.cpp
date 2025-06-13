#include "pch.h"
#include "Game/SteeringBehavior/WindBehavior.h"
#include "Game/Parameters/Parameters.h"
#include "Game/Parameters/ParameterKeys.h"


const std::string WindBehavior::WIND_MIN_STRENGTH = std::string(magic_enum::enum_name(ParameterKeysF::WindMinStrength));
const std::string WindBehavior::WIND_MAX_STRENGTH = std::string(magic_enum::enum_name(ParameterKeysF::WindMaxStrength));
const std::string WindBehavior::WIND_MIN_DURATION = std::string(magic_enum::enum_name(ParameterKeysF::WindMinDuration));
const std::string WindBehavior::WIND_MAX_DURATION = std::string(magic_enum::enum_name(ParameterKeysF::WindMaxDuration));
const std::string WindBehavior::WIND_IDLE_TIME    = std::string(magic_enum::enum_name(ParameterKeysF::WindIdleTime));

const std::string WindBehavior::PARAMETERS_ID = std::string(magic_enum::enum_name(ParametersID::STEERING_BEHAVIOR));


WindBehavior::WindBehavior()
    : 
    m_rng(std::random_device{}()),
    m_strengthDist(
        Parameters::GetInstance()->GetParameter<float>(PARAMETERS_ID,WIND_MIN_STRENGTH),
        Parameters::GetInstance()->GetParameter<float>(PARAMETERS_ID, WIND_MAX_STRENGTH)),
    m_timeDist(
        Parameters::GetInstance()->GetParameter<float>(PARAMETERS_ID, WIND_MIN_DURATION),
        Parameters::GetInstance()->GetParameter<float>(PARAMETERS_ID, WIND_MAX_DURATION)),
    m_dirDist(-1.0f, 1.0f),
    m_idleTime(Parameters::GetInstance()->GetParameter<float>(PARAMETERS_ID, WIND_IDLE_TIME)),
    m_timer(0.0f)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void WindBehavior::Update(float deltaTime) 
{
    // ���̋����������Ȃ牽�����Ȃ�
    if (m_isWind)
    {
        // �c�蕗�p�����Ԃ����炷
        m_windTimer -= deltaTime;

        // ���Ԑ؂�ŕ����~����
        if (m_windTimer <= 0.0f)
        {
            // ���𖳌���
            m_isWind = false;
            // ���Ȃ��Ƀ��Z�b�g
            m_currentWind = DirectX::SimpleMath::Vector3::Zero; 
        }

        // ���������Ă�Ԃ͉������Ȃ�
        return; 
    }

    // �����~�܂��Ă��鎞�Ԃ����Z����
    m_timer += deltaTime;
    if (m_timer >= m_idleTime)
    {
        // ���𐶐�
        GenerateNewWind();
        m_timer = 0.0f;
    }

    // �f�o�b�O�̎��̂݃p�����[�^���X�V��������
#ifdef _DEBUG

    m_strengthDist = std::uniform_real_distribution(
        Parameters::GetInstance()->GetParameter<float>(PARAMETERS_ID, WIND_MIN_STRENGTH),
        Parameters::GetInstance()->GetParameter<float>(PARAMETERS_ID, WIND_MAX_STRENGTH)
    );
    
    m_timeDist = std::uniform_real_distribution(
        Parameters::GetInstance()->GetParameter<float>(PARAMETERS_ID, WIND_MIN_DURATION),
        Parameters::GetInstance()->GetParameter<float>(PARAMETERS_ID, WIND_MAX_DURATION)
    );
    
    m_dirDist = std::uniform_real_distribution(-1.0f, 1.0f);

    m_idleTime = Parameters::GetInstance()->GetParameter<float>(PARAMETERS_ID, WIND_IDLE_TIME);

#endif
}


DirectX::SimpleMath::Vector3 WindBehavior::Calculate() 
{
    return m_currentWind;
}

void WindBehavior::GenerateNewWind() 
{
    // �V�������̕����������_�������iXZ���ʁj
    DirectX::SimpleMath::Vector3 dir(m_dirDist(m_rng), 0.0f, m_dirDist(m_rng));

    // ����[���x�N�g���Ȃ�X�����ɐݒ�
    if (dir.Length() < 0.001f) dir = DirectX::SimpleMath::Vector3::UnitX;

    // �����x�N�g���𐳋K��
    dir.Normalize();

    // ���̋����������_������
    float strength = m_strengthDist(m_rng);

    // ���݂̕��x�N�g�����X�V
    m_currentWind = dir * strength;

    // ���̌p�����Ԃ������_������
    m_currentDuration = m_timeDist(m_rng);

    // �^�C�}�[�����Z�b�g
    m_windTimer = m_currentDuration;

    // �A�N�e�B�u��Ԃɂ���
    m_isWind = true;
}

/// <summary>
/// �L���ɂ���
/// </summary>
void WindBehavior::On()
{
    // �t���O���I���ɂ���
    m_isActive = true;
}

/// <summary>
/// �����ɂ���
/// </summary>
void WindBehavior::Off()
{
    // �t���O���I�t�ɂ���
    m_isActive = false;
}
