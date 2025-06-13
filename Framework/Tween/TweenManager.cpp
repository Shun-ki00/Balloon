// ============================================
// 
// �t�@�C����: TweenManager.cpp
// �T�v: Tween �̃C���X�^���X���Ǘ����A�A�j���[�V�����̍X�V�������s���i�V���O���g���j
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Framework/Tween/TweenManager.h"
#include "Framework/CommonResources.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TweenManager::TweenManager()
{
    // ���L���\�[�X���擾����
    m_commonResources = CommonResources::GetInstance();
    
    // �����Ƃ���10��Tween��p�ӂ��Ă���
    for (int i = 0; i < INITIAL_TWEEN_COUNT; i++)
    {
        tweens.push_back(std::make_unique<Tween>());
    }
}


/// <summary>
/// Tween���擾����
/// </summary>
Tween* TweenManager::GetTween()
{
    for (const auto& tween : tweens)
    {
        // ��A�N�e�B�u�ȏ�Ԃ�Tween��n��
        if (!tween->GetIsActive())
        {
            return tween.get();
        }
    }
    // �����S�ċN�����Ȃ�ΐV��Tween���쐬����
    tweens.push_back(std::make_unique<Tween>());
    // �N�����Ă��Ȃ�Tween��Ԃ�
    return tweens.back().get();
}

/// <summary>
/// �X�V����
/// </summary>
void TweenManager::Update()
{
    // �o�ߎ��ԁi�b�P�ʁj���擾
    const float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

    // Tween�̍X�V����
    for (const auto& tween : tweens)
    {
        // Tween���i�s���̕��̂ݍX�V�������s��
        if (tween->GetIsActive())
        {
            tween->Update(elapsedTime);
        }
    }
}

/// <summary>
/// �S�Ă�Tween���~����
/// </summary>
void TweenManager::Stop()
{
    for (const auto& tween : tweens)
    {
        tween->Stop();
    }
}