#pragma once
#include "Interface/ISteeringBehavior.h"
#include <random>


class WindBehavior : public ISteeringBehavior
{
public:

    // ���𐶐�
    void GenerateNewWind();

    // �r�w�C�r�A��L���ɂ���
    void On() override;
    // �r�w�C�r�A�𖳌��ɂ���
    void Off() override;

    // �X�e�A�����O�͂��v�Z����
    DirectX::SimpleMath::Vector3 Calculate() override;
    // �X�V�ŕ���ω�������
    void Update(float deltaTime);

private:
    //	�R���X�g���N�^
    WindBehavior();
    //	�f�X�g���N�^
    ~WindBehavior() = default;
public:
    WindBehavior(const WindBehavior&) = delete;             // �R�s�[�֎~
    WindBehavior& operator=(const WindBehavior&) = delete;  // �R�s�[����֎~
    WindBehavior(const WindBehavior&&) = delete;            // ���[�u�֎~
    WindBehavior& operator=(const WindBehavior&&) = delete; // ���[�u����֎~

    //	�V���O���g���C���X�^���X�̎擾
    static WindBehavior* GetInstance()
    {
        static WindBehavior instance;
        return &instance;
    }

private:

    // �L�����ǂ����̃t���O
    bool m_isActive;

    static const std::string PARAMETERS_ID;

    static const std::string WIND_MIN_STRENGTH;
    static const std::string WIND_MAX_STRENGTH;
    static const std::string WIND_MIN_DURATION;
    static const std::string WIND_MAX_DURATION;
    static const std::string WIND_IDLE_TIME; 

    // �����_��������
    mutable std::default_random_engine m_rng;
    // ���̋��������߂邽�߂̕��z�i�ŏ��`�ő�j
    std::uniform_real_distribution<float> m_strengthDist;
    // ���̕����x�N�g�������߂邽�߂̕��z�i-1.0�`1.0�j
    std::uniform_real_distribution<float> m_dirDist;
    // ���̌p�����Ԃ����߂邽�߂̕��z�i�ŒZ�`�Œ��j
    std::uniform_real_distribution<float> m_timeDist;   

    // ���ݕ��������Ă��邩�ǂ����̃t���O
    bool m_isWind;
    // �o�ߎ���
    float m_timer;
    // �p������
    float m_idleTime;
    // ���̎���
    float m_windTimer;
    // ���݂̕��̌p������
    float m_currentDuration;                        
    // ���݂̕��x�N�g��
    DirectX::SimpleMath::Vector3 m_currentWind;     
};