// ============================================
// 
// �t�@�C����: AudioManager.h
// �T�v: AudioManager.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include <future>
#include "Sounds.h"
#include <Audio.h>

class AudioManager
{
public :
	// �}�X�^�[���ʂ�ݒ肷��
	void SetMasterVolume(const float& volume);
	// SE�̉��ʂ�ݒ肷��
	void SetSeVolume(const float& volume);
	// BGM�̉��ʂ�ݒ肷��
	void SetBgmVolume(const float& volume);

public:
	// ����������
	void Initialize();
	// �X�V����
	void Update(DX::StepTimer const& timer);

	// BGM���Đ�����
	void PlayBgm(XACT_WAVEBANK_SOUNDS bgmName, float fadeTime = 1.0f);
	void PlayBgm(XACT_WAVEBANK_SOUNDS bgmName);
	// BGM���~����
	void StopBgm(float fadeTime = 1.0f);
	void StopBgm();


	// SE���Đ�
	void PlaySE(XACT_WAVEBANK_SOUNDS_SE bgmName);
	int PlayLoopSE(XACT_WAVEBANK_SOUNDS_SE bgmName);
	void StopSE(int index);

private:

	// BGM�̃��[�h���s��
	void LoadBGM();
	// SE�̃��[�h���s��
	void LoadSE();

	DirectX::SoundEffectInstance* SetSE(DirectX::SoundEffectInstance* instance);

private:
	//	�R���X�g���N�^
	AudioManager();
	// �f�X�g���N�^
	~AudioManager();
public:
	AudioManager(const AudioManager&) = delete;             // �R�s�[�֎~
	AudioManager& operator=(const AudioManager&) = delete;  // �R�s�[����֎~
	AudioManager(const AudioManager&&) = delete;            // ���[�u�֎~
	AudioManager& operator=(const AudioManager&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static AudioManager* GetInstance()
	{
		static AudioManager instance;
		return &instance;
	}

private:
	
	using BgmMap = std::unordered_map<XACT_WAVEBANK_SOUNDS, std::unique_ptr<DirectX::SoundEffectInstance>>;
	using SeMap  = std::unordered_map<XACT_WAVEBANK_SOUNDS_SE, std::unique_ptr<DirectX::SoundEffectInstance>>;

	// �I�[�f�B�I�G���W��
	std::unique_ptr<DirectX::AudioEngine> m_audioEngine;

	// BGM�̃o���N
	std::unique_ptr<DirectX::WaveBank> m_waveBankBgm;
	// BGM�̊i�[
	BgmMap m_bgmMaps;
	// �Đ���BGM�̃C���X�^���X
	DirectX::SoundEffectInstance* m_currentBgm;

	// SE�̃o���N
	std::unique_ptr<DirectX::WaveBank> m_waveBankSe;
	// SE�̊i�[
	SeMap m_seMaps;
	// SE�̃C���X�^���X
	std::vector<DirectX::SoundEffectInstance*> m_currentSes;

	// �}�X�^�[����
	float m_masterVolume;
	// SE�̉���
	float m_seVolume;
	// BGM�̉���
	float m_bgmVolume;


	// �t�F�[�h�t���O
	bool m_isActive;
	// �t�F�[�h�^�C��
	float m_fadeTime;
	// ���݂̉���
	float m_currentValue;

	// �t�F�[�h���̌o�ߎ���
	float m_fadeElapsedTime;
	// �X�^�[�g�{�����[��
	float m_startValueme;
	// �I���{�����[��
	float m_endValueme;
};