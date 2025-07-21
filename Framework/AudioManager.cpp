// ============================================
// 
// �t�@�C����: AudioManager.cpp
// �T�v: ���S�ʂ��Ǘ�����N���X�i�V���O���g���j
// 
// ����� : �����x��
// 
// ============================================

#include "pch.h"
#include "Framework/AudioManager.h"
#include "Framework/Sounds.h"
#include <Audio.h>
#include "Framework/Tween/Tween.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
AudioManager::AudioManager()
	:
	m_audioEngine{},
	m_waveBankSe{},
	m_masterVolume{},
	m_seVolume{},
	m_bgmVolume{},
	m_fadeTime{},
	m_currentValue{},
	m_fadeElapsedTime{},
	m_startValueme{},
	m_endValueme{}
{
	m_isActive = false;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
AudioManager::~AudioManager()
{
	m_isActive = false;

	// �I�[�f�B�I�G���W���̌�n��
	if (m_audioEngine)
	{
		m_audioEngine->Suspend();
	}
}

/// <summary>
/// ����������
/// </summary>
void AudioManager::Initialize()
{
	// �I�[�f�B�I�G���W���̃t���O
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AUDIO_ENGINE_FLAGS::AudioEngine_Default;
#ifdef _DEBUG
	eflags |= DirectX::AUDIO_ENGINE_FLAGS::AudioEngine_Debug;
#endif

	// ���ʂ����ׂ�1�ɏ�����
	m_masterVolume = 1.0f;
	m_seVolume = 1.0f;
	m_bgmVolume = 1.0f;

	// �I�[�f�B�I�G���W�����쐬����
	m_audioEngine = std::make_unique<DirectX::AudioEngine>(eflags);
	// �}�X�^�[���ʂ̏�����
	m_audioEngine->SetMasterVolume(m_masterVolume);

	// ���f�������[�h����
	std::thread bgm(&AudioManager::LoadBGM, this);
	// �V�F�[�_�[�����[�h����
	std::thread se(&AudioManager::LoadSE, this);

	// 10�قǗp�ӂ��Ă���
	m_currentSes = std::vector<DirectX::SoundEffectInstance*>(10);
	// �C���X�^���X�̏�����
	for ( auto& se : m_currentSes) se = nullptr;
	// �C���X�^���X�̏�����
	m_currentBgm = nullptr;

	// ���[�h������҂�
	bgm.join();
	se.join();

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�o�ߎ���</param>
void AudioManager::Update(DX::StepTimer const& timer)
{
	// �I�[�f�B�I�G���W�����X�V����
	if (!m_audioEngine->Update())
	{
		// No audio device is active
		if (m_audioEngine->IsCriticalError())
		{
			OutputDebugString(L"AudioEngine Error!\n");
		}
	}

	// ���ʉ���~�������͉̂������
	for (auto& se : m_currentSes)
	{
		if (se == nullptr) continue;

		// ��~���Ă�����ʉ�������ꍇ
		if (DirectX::SoundState::STOPPED == se->GetState())
			// �������
			se = nullptr;
	}

	
	// BGM�̃t�F�[�h����
	if (!m_isActive) return;

	// �o�ߎ��Ԃ��X�V
	m_fadeElapsedTime += (float)timer.GetElapsedSeconds();

	// ���`��Ԃ��g�p���ĉ��ʂ��X�V
	float t = m_fadeElapsedTime / m_fadeTime; // 0.0f�`1.0f �͈̔�
	t = std::min(t, 1.0f); // t��1�𒴂��Ȃ��悤�ɐ���
	
	// ���݂̉��ʂ��X�V
	m_currentValue = m_startValueme + t * (m_endValueme - m_startValueme);
	// ���ʐݒ�
	m_currentBgm->SetVolume(m_currentValue);
	
	// �t�F�[�h���I��������
	if (t >= 1.0f) {
		m_currentValue = m_endValueme;
		// �ŏI���ʂ�ݒ�
		m_currentBgm->SetVolume(m_currentValue);

		if (m_currentValue <= 0.0f)
		{
			// ���ʂ�0�ɂȂ�������BGM���~����
			m_currentBgm->Stop(true);
			// �������
			m_currentBgm = nullptr;
		}
		
		// �t�F�[�h���A�N�e�B�u
		m_isActive = false;
	}
}

/// <summary>
/// �t�F�[�h�C�����Ȃ���BGM���Đ�
/// </summary>
/// <param name="bgmName">BGM</param>
/// <param name="fadeTime">�t�F�[�h����</param>
void AudioManager::PlayBgm(XACT_WAVEBANK_SOUNDS bgmName, float fadeTime)
{
	// �t�F�[�h���̓X�L�b�v
	if (m_isActive) return;

	// ����BGM���~����
	if (m_currentBgm) m_currentBgm->Stop(true);

	// �V����BGM���Đ�����
	m_bgmMaps.at(bgmName)->Play(true);
	// �V����BGM������BGM�Ƃ���
	m_currentBgm = m_bgmMaps.at(bgmName).get();
	// �V����BGM�̉��ʂ�0�ɂ���
	m_currentBgm->SetVolume(0.0f);

	// �t�F�[�h���Ԃ�ݒ�
	m_fadeTime = fadeTime;
	// �X�^�[�g���ʐݒ�
	m_startValueme = 0.0f;
	// �I�����ʐݒ�
	m_endValueme = m_bgmVolume;
	// ���݂̉��ʂ�������
	m_currentValue = 0.0f;
	m_fadeElapsedTime = 0.0f;

	// �t�F�[�h���A�N�e�B�u�ɂ���
	m_isActive = true;
}

/// <summary>
/// BGM���Đ�����
/// </summary>
/// <param name="bgmName">BGM</param>
/// <param name="fadeTime">�t�F�[�h����</param>
void AudioManager::PlayBgm(XACT_WAVEBANK_SOUNDS bgmName)
{
	// ����BGM���~����
	if (m_currentBgm) m_currentBgm->Stop(true);

	// �V����BGM���Đ�����
	m_bgmMaps.at(bgmName)->Play(true);
	// �V����BGM������BGM�Ƃ���
	m_currentBgm = m_bgmMaps.at(bgmName).get();
	// �V����BGM�̉��ʂ�0�ɂ���
	m_currentBgm->SetVolume(m_bgmVolume);
}


/// <summary>
/// �t�F�[�h�A�E�g���Ȃ���BGM���~����
/// </summary>
/// <param name="fadeTime">�t�F�[�h����</param>
void AudioManager::StopBgm( float fadeTime)
{
	// �t�F�[�h���̓X�L�b�v
	if (m_isActive) return;

	// �t�F�[�h���Ԃ�ݒ�
	m_fadeTime = fadeTime;
	// �X�^�[�g���ʐݒ�
	m_startValueme = m_bgmVolume;
	// �I�����ʐݒ�
	m_endValueme = 0.0f;
	// ���݂̉��ʂ�������
	m_currentValue = 0.0f;
	m_fadeElapsedTime = 0.0f;

	// �t�F�[�h���A�N�e�B�u�ɂ���
	m_isActive = true;
}


/// <summary>
/// BGM���~����
/// </summary>
/// <param name="fadeTime">�t�F�[�h����</param>
void AudioManager::StopBgm()
{
	// BGM���~����
	m_currentBgm->Stop();
	// �C���X�^���X�̉��
	m_currentBgm = nullptr;
}



/// <summary>
/// SE���Đ�����
/// </summary>
void AudioManager::PlaySE(XACT_WAVEBANK_SOUNDS_SE bgmName)
{
	for (int i = 0; i < m_currentSes.size(); i++)
	{
		// �g�p���Ă��Ȃ����̂�T��
		if (m_currentSes[i] != nullptr) continue;

		// �g�p���Ă��Ȃ��ꍇ�C���X�^���X��ݒ肷��
		m_currentSes[i] = m_seMaps.at(bgmName).get();

		// ���ʂ�ݒ肷��
		m_currentSes[i]->SetVolume(m_seVolume);

		// ���[�v�Đ��͍s��Ȃ�
		m_currentSes[i]->Play(false);
	}
}

/// <summary>
/// SE�����[�v�Đ�
/// </summary>
/// <param name="bgmName"></param>
int AudioManager::PlayLoopSE(XACT_WAVEBANK_SOUNDS_SE bgmName)
{
	for (int i = 0; i < m_currentSes.size(); i++)
	{
		// �g�p���Ă��Ȃ����̂�T��
		if (m_currentSes[i] != nullptr) continue;

		// �g�p���Ă��Ȃ��ꍇ�C���X�^���X��ݒ肷��
		m_currentSes[i] = m_seMaps.at(bgmName).get();

		// ���ʂ�ݒ肷��
		m_currentSes[i]->SetVolume(m_seVolume);

		// ���[�v�Đ����s��
		m_currentSes[i]->Play(true);

		// �C���f�b�N�X��Ԃ�
		return i;
	}

	return 0;
}

/// <summary>
/// ���[�v�Đ����~����
/// </summary>
void AudioManager::StopSE(int index)
{
	// index �͈̔̓`�F�b�N�ƃ|�C���^�� null �`�F�b�N
	if (index >= 0 && index < static_cast<int>(m_currentSes.size()) && m_currentSes[index])
	{
		// ���ʉ����~����
		m_currentSes[index]->Stop();
		// �C���X�^���X�����
		m_currentSes[index] = nullptr;
	}
}

/// <summary>
/// �Đ�����SE��S�Ď~�߂�
/// </summary>
void AudioManager::StopSE()
{
	for (auto& se : m_currentSes)
	{
		if (se == nullptr) continue;

		// �Đ����̕�������Β�~���ĉ��
		if (DirectX::SoundState::PLAYING == se->GetState())
		{
			// ��~����
			se->Stop();
			// ������� 
			se = nullptr;
		}
	}
}


/// <summary>
/// �}�X�^�[���ʂ�ݒ�
/// </summary>
/// <param name="volume">����</param>
void AudioManager::SetMasterVolume(const float& volume)
{
	// �}�X�^�[���ʂ�ݒ�
	m_masterVolume = volume;
	// �I�[�f�B�I�G���W���ɉ��ʐݒ�
	m_audioEngine->SetMasterVolume(volume);
}

/// <summary>
/// SE���ʂ�ݒ�
/// </summary>
/// <param name="volume">����</param>
void AudioManager::SetSeVolume(const float& volume)
{
	// SE���ʂ�ݒ�
	m_seVolume = volume;
	// �T�E���h�G�t�F�N�g�ɉ��ʂ�ݒ肷��
	for (auto& se : m_seMaps)
	{
		se.second->SetVolume(m_seVolume);
	}
}

/// <summary>
/// BGM���ʂ�ݒ�
/// </summary>
/// <param name="volume">����</param>
void AudioManager::SetBgmVolume(const float& volume)
{
	// BGM���ʂ�ݒ�
	m_bgmVolume = volume;
	// �T�E���h�G�t�F�N�g�ɉ��ʂ�ݒ肷��
	for (auto& bgm : m_bgmMaps)
	{
		bgm.second->SetVolume(m_seVolume);
	}
}


// �Đ�����SE�̃C���X�^���X���Z�b�g����
DirectX::SoundEffectInstance* AudioManager::SetSE(DirectX::SoundEffectInstance* instance)
{
	for (auto& se : m_currentSes)
	{
		if (se != nullptr)
		{
			se = instance;
			return se;
		}
	}

	return nullptr;
}


/// <summary>
/// BGM�����[�h����
/// </summary>
void AudioManager::LoadBGM()
{
	// �T�E���h�o���N���쐬����
	m_waveBankBgm = std::make_unique<DirectX::WaveBank>
		(m_audioEngine.get(), L"Resources/Sounds/BGM.xwb");

	// BGM���}�b�v�ɓo�^����
	for (int i = 0; i < XACT_WAVEBANK_SOUNDS_ENTRY_COUNT; i++)
	{
		m_bgmMaps.insert(BgmMap::value_type((XACT_WAVEBANK_SOUNDS)i, m_waveBankBgm->CreateInstance((XACT_WAVEBANK_SOUNDS)i)));
	}
}

void AudioManager::LoadSE()
{
	// �T�E���h�o���N���쐬����
	m_waveBankSe = std::make_unique<DirectX::WaveBank>
		(m_audioEngine.get(), L"Resources/Sounds/SE.xwb");

	// SE���}�b�v�ɓo�^����
	for (int i = 0; i < XACT_WAVEBANK_SOUNDS_ENTRY_COUNT_SE; i++)
	{
		m_seMaps.insert(SeMap::value_type((XACT_WAVEBANK_SOUNDS_SE)i, m_waveBankSe->CreateInstance((XACT_WAVEBANK_SOUNDS_SE)i)));
	}
}