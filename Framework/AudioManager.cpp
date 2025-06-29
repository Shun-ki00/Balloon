// ============================================
// 
// ファイル名: AudioManager.cpp
// 概要: 音全般を管理するクラス（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================

#include "pch.h"
#include "Framework/AudioManager.h"
#include "Framework/Sounds.h"
#include <Audio.h>
#include "Framework/Tween/Tween.h"

/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
AudioManager::~AudioManager()
{
	m_isActive = false;

	// オーディオエンジンの後始末
	if (m_audioEngine)
	{
		m_audioEngine->Suspend();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void AudioManager::Initialize()
{
	// オーディオエンジンのフラグ
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AUDIO_ENGINE_FLAGS::AudioEngine_Default;
#ifdef _DEBUG
	eflags |= DirectX::AUDIO_ENGINE_FLAGS::AudioEngine_Debug;
#endif

	// オーディオエンジンを作成する
	m_audioEngine = std::make_unique<DirectX::AudioEngine>(eflags);
	// マスター音量の初期化
	m_audioEngine->SetMasterVolume(m_masterVolume);

	// モデルをロードする
	std::thread bgm(&AudioManager::LoadBGM, this);
	// シェーダーをロードする
	std::thread se(&AudioManager::LoadSE, this);

	// 音量をすべて1に初期化
	m_masterVolume = 1.0f;
	m_seVolume     = 1.0f;
	m_bgmVolume    = 0.5f;

	// 10個ほど用意しておく
	m_currentSes = std::vector<DirectX::SoundEffectInstance*>(10);
	// インスタンスの初期化
	for ( auto& se : m_currentSes) se = nullptr;
	// インスタンスの初期化
	m_currentBgm = nullptr;

	// ロード完了を待つ
	bgm.join();
	se.join();

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">経過時間</param>
void AudioManager::Update(DX::StepTimer const& timer)
{
	// オーディオエンジンを更新する
	if (!m_audioEngine->Update())
	{
		// No audio device is active
		if (m_audioEngine->IsCriticalError())
		{
			OutputDebugString(L"AudioEngine Error!\n");
		}
	}

	// 効果音停止したものは解放する
	for (auto& se : m_currentSes)
	{
		if (se == nullptr) continue;

		// 停止している効果音がある場合
		if (DirectX::SoundState::STOPPED == se->GetState())
			// 解放する
			se = nullptr;
	}

	
	// BGMのフェード処理
	if (!m_isActive) return;

	// 経過時間を更新
	m_fadeElapsedTime += (float)timer.GetElapsedSeconds();

	// 線形補間を使用して音量を更新
	float t = m_fadeElapsedTime / m_fadeTime; // 0.0f～1.0f の範囲
	t = std::min(t, 1.0f); // tが1を超えないように制限
	
	// 現在の音量を更新
	m_currentValue = m_startValueme + t * (m_endValueme - m_startValueme);
	// 音量設定
	m_currentBgm->SetVolume(m_currentValue);
	
	// フェードが終了したら
	if (t >= 1.0f) {
		m_currentValue = m_endValueme;
		// 最終音量を設定
		m_currentBgm->SetVolume(m_currentValue);

		if(m_currentValue <= 0.0f)
		// 音量が0になった時はBGMを停止する
		m_currentBgm->Stop(true);

		// 解放する
		m_currentBgm = nullptr;

		// フェードを非アクティブ
		m_isActive = false;
	}
}

/// <summary>
/// フェードインしながらBGMを再生
/// </summary>
/// <param name="bgmName">BGM</param>
/// <param name="fadeTime">フェード時間</param>
void AudioManager::PlayBgm(XACT_WAVEBANK_SOUNDS bgmName, float fadeTime)
{
	// フェード中はスキップ
	if (m_isActive) return;

	// 今のBGMを停止する
	if (m_currentBgm) m_currentBgm->Stop(true);

	// 新しいBGMを再生する
	m_bgmMaps.at(bgmName)->Play(true);
	// 新しいBGMを今のBGMとする
	m_currentBgm = m_bgmMaps.at(bgmName).get();
	// 新しいBGMの音量を0にする
	m_currentBgm->SetVolume(0.0f);

	// フェード時間を設定
	m_fadeTime = fadeTime;
	// スタート音量設定
	m_startValueme = 0.0f;
	// 終了音量設定
	m_endValueme = m_bgmVolume;
	// 現在の音量を初期化
	m_currentValue = 0.0f;
	m_fadeElapsedTime = 0.0f;

	// フェードをアクティブにする
	m_isActive = true;
}

/// <summary>
/// BGMを再生する
/// </summary>
/// <param name="bgmName">BGM</param>
/// <param name="fadeTime">フェード時間</param>
void AudioManager::PlayBgm(XACT_WAVEBANK_SOUNDS bgmName)
{
	// 今のBGMを停止する
	if (m_currentBgm) m_currentBgm->Stop(true);

	// 新しいBGMを再生する
	m_bgmMaps.at(bgmName)->Play(true);
	// 新しいBGMを今のBGMとする
	m_currentBgm = m_bgmMaps.at(bgmName).get();
	// 新しいBGMの音量を0にする
	m_currentBgm->SetVolume(m_bgmVolume);
}


/// <summary>
/// フェードアウトしながらBGMを停止する
/// </summary>
/// <param name="fadeTime">フェード時間</param>
void AudioManager::StopBgm( float fadeTime)
{
	// フェード中はスキップ
	if (m_isActive) return;

	// フェード時間を設定
	m_fadeTime = fadeTime;
	// スタート音量設定
	m_startValueme = m_bgmVolume;
	// 終了音量設定
	m_endValueme = 0.0f;
	// 現在の音量を初期化
	m_currentValue = 0.0f;
	m_fadeElapsedTime = 0.0f;

	// フェードをアクティブにする
	m_isActive = true;
}


/// <summary>
/// BGMを停止する
/// </summary>
/// <param name="fadeTime">フェード時間</param>
void AudioManager::StopBgm()
{
	// BGMを停止する
	m_currentBgm->Stop();
	// インスタンスの解放
	m_currentBgm = nullptr;
}



/// <summary>
/// SEを再生する
/// </summary>
void AudioManager::PlaySE(XACT_WAVEBANK_SOUNDS_SE bgmName)
{
	// サウンドエフェクトをセットして取得する
	auto soundEffect = this->SetSE(m_seMaps.at(bgmName).get());
	// 一応再度音量を設定する
	soundEffect->SetVolume(m_seVolume);
	// SEを再生する（ループ再生は行わない）
	soundEffect->Play(false);
}

/// <summary>
/// SEをループ再生
/// </summary>
/// <param name="bgmName"></param>
int AudioManager::PlayLoopSE(XACT_WAVEBANK_SOUNDS_SE bgmName)
{
	for (int i = 0; i < m_currentSes.size(); i++)
	{
		// 使用していないものを探す
		if (m_currentSes[i] == nullptr) continue;

		// 使用していない場合インスタンスを設定する
		m_currentSes[i] = m_seMaps.at(bgmName).get();

		// 音量を設定する
		m_currentSes[i]->SetVolume(m_seVolume);

		// ループ再生を行う
		m_currentSes[i]->Play(true);

		// インデックスを返す
		return i;
	}

	return 0;
}

/// <summary>
/// ループ再生を停止する
/// </summary>
void AudioManager::StopSE(int index)
{
	// 効果音を停止する
	m_currentSes[index]->Stop();
	// インスタンスを解放
	m_currentSes[index] = nullptr;
}

/// <summary>
/// マスター音量を設定
/// </summary>
/// <param name="volume">音量</param>
void AudioManager::SetMasterVolume(const float& volume)
{
	// マスター音量を設定
	m_masterVolume = volume;
	// オーディオエンジンに音量設定
	m_audioEngine->SetMasterVolume(volume);
}

/// <summary>
/// SE音量を設定
/// </summary>
/// <param name="volume">音量</param>
void AudioManager::SetSeVolume(const float& volume)
{
	// SE音量を設定
	m_seVolume = volume;
	// サウンドエフェクトに音量を設定する
	for (auto& se : m_seMaps)
	{
		se.second->SetVolume(m_seVolume);
	}
}

/// <summary>
/// BGM音量を設定
/// </summary>
/// <param name="volume">音量</param>
void AudioManager::SetBgmVolume(const float& volume)
{
	// BGM音量を設定
	m_bgmVolume = volume;
	// サウンドエフェクトに音量を設定する
	for (auto& bgm : m_bgmMaps)
	{
		bgm.second->SetVolume(m_seVolume);
	}
}


// 再生するSEのインスタンスをセットする
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
/// BGMをロードする
/// </summary>
void AudioManager::LoadBGM()
{
	// サウンドバンクを作成する
	m_waveBankBgm = std::make_unique<DirectX::WaveBank>
		(m_audioEngine.get(), L"Resources/Sounds/BGM.xwb");

	// BGMをマップに登録する
	for (int i = 0; i < XACT_WAVEBANK_SOUNDS_ENTRY_COUNT; i++)
	{
		m_bgmMaps.insert(BgmMap::value_type((XACT_WAVEBANK_SOUNDS)i, m_waveBankBgm->CreateInstance((XACT_WAVEBANK_SOUNDS)i)));
	}
}

void AudioManager::LoadSE()
{
	// サウンドバンクを作成する
	m_waveBankSe = std::make_unique<DirectX::WaveBank>
		(m_audioEngine.get(), L"Resources/Sounds/SE.xwb");

	// SEをマップに登録する
	for (int i = 0; i < XACT_WAVEBANK_SOUNDS_ENTRY_COUNT_SE; i++)
	{
		m_seMaps.insert(SeMap::value_type((XACT_WAVEBANK_SOUNDS_SE)i, m_waveBankSe->CreateInstance((XACT_WAVEBANK_SOUNDS_SE)i)));
	}
}