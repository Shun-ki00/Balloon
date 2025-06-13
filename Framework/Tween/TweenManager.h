// ============================================
// 
// ファイル名: TweenManager.h
// 概要: TweenManager.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Framework/Tween/Tween.h"

class Tween;
class CommonResources;


class TweenManager {

private:
	static constexpr int INITIAL_TWEEN_COUNT = 10;

private:
	//	コンストラクタ
	TweenManager();
	// デストラクタ
	~TweenManager() = default;
public:
	TweenManager(const TweenManager&) = delete;             // コピー禁止
	TweenManager& operator=(const TweenManager&) = delete;  // コピー代入禁止
	TweenManager(const TweenManager&&) = delete;            // ムーブ禁止
	TweenManager& operator=(const TweenManager&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static TweenManager* GetInstance()
	{
		static TweenManager instance;
		return &instance;
	}

public:
    // 更新処理
    void Update();
	// 停止処理
	void Stop();
	// 非アクティブのTweenを取得する
	Tween* GetTween();

private:
	// 共有リソース
	CommonResources* m_commonResources;
    // tweenを格納
    std::vector<std::unique_ptr<Tween>> tweens;
};