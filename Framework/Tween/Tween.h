// ============================================
// 
// ファイル名: Tween.h
// 概要: Tween.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once

class Transform;

class Tween
{
public:
    // コールバック関数型
    using Callback = std::function<void()>;  
public:
        // Yoyo	     移動後、最初の位置に戻るように動きます
        // Restart	 移動後、最初の位置から再び移動を開始します
        // Increment 移動後、その位置から再び移動を開始します
    enum class LoopType { None , Restart, Yoyo, Increment };
    // イージングの種類
    enum class EasingType {
        Linear,         // リニア補間（デフォルト）
        EaseInSine,
        EaseOutSine,
        EaseInOutSine,
        EaseInQuad,
        EaseOutQuad,
        EaseInOutQuad,
        EaseInCubic,
        EaseOutCubic,
        EaseInOutCubic,
        EaseInQuart,
        EaseOutQuart,
        EaseInOutQuart,
        EaseInQuint,
        EaseOutQuint,
        EaseInOutQuint,
        EaseInExpo,
        EaseOutExpo,
        EaseInOutExpo,
        EaseInCirc,
        EaseOutCirc,
        EaseInOutCirc,
        EaseInBack,
        EaseOutBack,
        EaseInOutBack,
        EaseInElastic,
        EaseOutElastic,
        EaseInOutElastic,
        EaseInBounce,
        EaseOutBounce,
        EaseInOutBounce
    };

    // 進行状態を取得する
    bool GetIsActive() { return m_isActive; }
    // Transformを設定する
    void SetTransform(Transform* transform) { m_transform = transform; }

    // DOMoveメソッド
    Tween& DOMove(const DirectX::SimpleMath::Vector3& end, float duration);
    Tween& DOMoveX(float endX, float duration);
    Tween& DOMoveY(float endY, float duration);
    Tween& DOMoveZ(float endZ, float duration);

    // DORotationメソッド
    Tween& DORotation(const DirectX::SimpleMath::Vector3& end, float duration);
    Tween& DORotationX(float endX, float duration);
    Tween& DORotationY(float endY, float duration);
    Tween& DORotationZ(float endZ, float duration);

    // DOScaleメソッド
    Tween& DOScale(const DirectX::SimpleMath::Vector3& end, float duration);
    Tween& DOScaleX(float endX, float duration);
    Tween& DOScaleY(float endY, float duration);
    Tween& DOScaleZ(float endZ, float duration);

    // 遅延設定
    Tween& SetDelay(float delayTime);
    // ループ設定
    Tween& SetLoops(int count, Tween::LoopType type);
    // イージング設定
    Tween& SetEase(Tween::EasingType ease);
    // 完了時の処理を設定
    Tween& OnComplete(Callback callback);

    // 再生
    void Play();
    // 停止
    void Stop();
    // 更新処理
    bool Update(float deltaTime);
   
    // コンストラクタ
    Tween();
    // デストラクタ
    ~Tween() = default;

    // イージングの適応
    static float EasingFunction(EasingType type, float t);
    // 回転ベクトルをクォータニオンに変換する
    DirectX::SimpleMath::Quaternion ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation);
    // ラジアンを度数に変換する
    DirectX::SimpleMath::Vector3 ConvertToDegrees(const DirectX::SimpleMath::Vector3& radianVec);

private:

    // ターゲットのTransform
    Transform* m_transform;
    
    // 移動
    DirectX::SimpleMath::Vector3 m_startPosition;
    DirectX::SimpleMath::Vector3 m_endPosition;
    // 回転
    DirectX::SimpleMath::Quaternion m_startRotation;
    DirectX::SimpleMath::Quaternion m_endRotation;
    // スケール
    DirectX::SimpleMath::Vector3 m_startScale;
    DirectX::SimpleMath::Vector3 m_endScale;

    // 各処理の有効フラグ
    bool m_doMove;
    bool m_doRotation;
    bool m_doScale;
    // 進行中かどうか
    bool m_isActive;

    // 時間
    float m_duration;
    // 遅延時間
    float m_delay;
    // ループカウント
    int m_loopCount;

    // ループタイプ
    Tween::LoopType m_loopType;
    // イージングタイプ
    Tween::EasingType m_easeType;

    // 完了時に呼び出す関数
    Callback m_onComplete;

    // 経過時間
    float m_elapsed;
};

