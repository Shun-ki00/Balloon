// ============================================
// 
// ファイル名: AudioManager.h
// 概要: AudioManager.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include <future>
#include "Sounds.h"
#include <Audio.h>

class AudioManager
{
public :
	// マスター音量を設定する
	void SetMasterVolume(const float& volume);
	// SEの音量を設定する
	void SetSeVolume(const float& volume);
	// BGMの音量を設定する
	void SetBgmVolume(const float& volume);

public:
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(DX::StepTimer const& timer);

	// BGMを再生する
	void PlayBgm(XACT_WAVEBANK_SOUNDS bgmName, float fadeTime );
	void PlayBgm(XACT_WAVEBANK_SOUNDS bgmName);
	// BGMを停止する
	void StopBgm(float fadeTime = 1.0f);
	void StopBgm();


	// SEを再生
	void PlaySE(XACT_WAVEBANK_SOUNDS_SE bgmName);
	int PlayLoopSE(XACT_WAVEBANK_SOUNDS_SE bgmName);

	// SEを停止
	void StopSE(int index);
	void StopSE();

private:

	// BGMのロードを行う
	void LoadBGM();
	// SEのロードを行う
	void LoadSE();

	DirectX::SoundEffectInstance* SetSE(DirectX::SoundEffectInstance* instance);

private:
	//	コンストラクタ
	AudioManager();
	// デストラクタ
	~AudioManager();
public:
	AudioManager(const AudioManager&) = delete;             // コピー禁止
	AudioManager& operator=(const AudioManager&) = delete;  // コピー代入禁止
	AudioManager(const AudioManager&&) = delete;            // ムーブ禁止
	AudioManager& operator=(const AudioManager&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static AudioManager* GetInstance()
	{
		static AudioManager instance;
		return &instance;
	}

private:
	
	using BgmMap = std::unordered_map<XACT_WAVEBANK_SOUNDS, std::unique_ptr<DirectX::SoundEffectInstance>>;
	using SeMap  = std::unordered_map<XACT_WAVEBANK_SOUNDS_SE, std::unique_ptr<DirectX::SoundEffectInstance>>;

	// オーディオエンジン
	std::unique_ptr<DirectX::AudioEngine> m_audioEngine;

	// BGMのバンク
	std::unique_ptr<DirectX::WaveBank> m_waveBankBgm;
	// BGMの格納
	BgmMap m_bgmMaps;
	// 再生中BGMのインスタンス
	DirectX::SoundEffectInstance* m_currentBgm;

	// SEのバンク
	std::unique_ptr<DirectX::WaveBank> m_waveBankSe;
	// SEの格納
	SeMap m_seMaps;
	// SEのインスタンス
	std::vector<DirectX::SoundEffectInstance*> m_currentSes;

	// マスター音量
	float m_masterVolume;
	// SEの音量
	float m_seVolume;
	// BGMの音量
	float m_bgmVolume;


	// フェードフラグ
	bool m_isActive;
	// フェードタイム
	float m_fadeTime;
	// 現在の音量
	float m_currentValue;

	// フェード中の経過時間
	float m_fadeElapsedTime;
	// スタートボリューム
	float m_startValueme;
	// 終了ボリューム
	float m_endValueme;
};