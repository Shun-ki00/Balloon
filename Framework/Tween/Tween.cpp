// ============================================
// 
// ファイル名: Tween.cpp
// 概要: オブジェクトの移動・回転・スケール変化を補間するアニメーション処理を実装
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Framework/Tween/Tween.h"
#include "Game/Transform/Transform.h"
#include "Framework/Easing.h"

/// <summary>
/// コンストラクタ
/// </summary>
Tween::Tween()
    :
    m_transform(nullptr),
    m_onComplete(nullptr),
    m_startPosition{},
    m_endPosition{},
    m_startRotation{},
    m_endRotation{},
    m_startScale{},
    m_endScale{},
    m_isActive(false),
    m_doMove(false),
    m_doRotation(false),
    m_doScale(false),
    m_duration{},
    m_delay{},
    m_loopCount{},
    m_easeType(Tween::EasingType::Linear),
    m_loopType(Tween::LoopType::None),
    m_elapsed{}
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
/// <returns></returns>
bool Tween::Update(float deltaTime)
{
    // 進行中ではないときはスキップ
    if (!m_isActive) return false;
    // 現在の時間を更新する
    m_elapsed += deltaTime;
    // 遅延がある場合は待機
    if (m_elapsed < m_delay) return false; 

    // Transformが途中で破棄されたらTweenを停止する
    if (m_transform == nullptr)
    {
        this->Stop();
    }

    // アニメーションの進行度を計算（0.0 ～ 1.0 に正規化）
    float t = (m_elapsed - m_delay) / m_duration;
    // t を 1.0 にクランプ（補間の上限を超えないようにする）
    if (t > 1.0f) t = 1.0f;

    // イージングを適用
    float easeT = EasingFunction(m_easeType, t);

    // 移動処理 (DoMove)
    if (m_doMove) 
        m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Lerp(m_startPosition, m_endPosition, easeT));
    // 回転処理 (DoRotation)
    if (m_doRotation) 
        m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Slerp(m_startRotation, m_endRotation, easeT));
    // スケール処理 (DoScale)
    if (m_doScale) 
        m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::Lerp(m_startScale, m_endScale, easeT));

    // ループ処理
    if (t >= 1.0f) 
    {
        // ループがないときTweenを止める
        if (m_loopType == Tween::LoopType::None)
        {
            // アニメーションが完了したらコールバックを呼び出す
            if (m_onComplete)
            {
                m_onComplete();
            }
            this->Stop();
            return false;
        }
        // ループカウントが残っているかチェック
        if (--m_loopCount <= 0)
        {
            // アニメーションが完了したらコールバックを呼び出す
            if (m_onComplete)
            {
                m_onComplete();
            }
            this->Stop();
            return false;
        }

        DirectX::SimpleMath::Vector3    positionDelta;
        DirectX::SimpleMath::Quaternion rotationDelta;
        DirectX::SimpleMath::Vector3    scaleDelta;
    
        switch (m_loopType)
        {
            // 移動後、最初の位置から再び移動を開始します
            case Tween::LoopType::Restart:
                // 時間をリセット
                m_elapsed = 0.0f;
                break;
            // 移動後、最初の位置に戻るように動きます
            case Tween::LoopType::Yoyo:
                // スタートとエンドを入れ替える
                std::swap(m_startPosition, m_endPosition);
                std::swap(m_startRotation, m_endRotation);
                std::swap(m_startScale, m_endScale);
                // 時間をリセット
                m_elapsed = 0.0f;
                break;
            // 移動後、その位置から再び移動を開始します
            case Tween::LoopType::Increment:

                // 差分を計算
                positionDelta = m_endPosition - m_startPosition;
                m_startRotation.Inverse(m_startRotation);
                rotationDelta = m_endRotation * m_startRotation;
                scaleDelta    = m_endScale - m_startScale;

                // スタート地点をエンドに設定
                m_startPosition = m_endPosition;
                m_startRotation = m_endRotation;
                m_startScale    = m_endScale;
                // エンド地点を更新 差分を追加
                m_endPosition += positionDelta;
                m_endRotation *= rotationDelta;
                m_endScale += scaleDelta;
                // 時間をリセット
                m_elapsed = 0.0f;
                break;
            default:
                break;
        }
    }

    return m_isActive;
}

/// <summary>
/// イージンの適応
/// </summary>
/// <param name="type"></param>
/// <param name="t"></param>
/// <returns></returns>
float Tween::EasingFunction(EasingType type, float t)
{
    using namespace easing;

    switch (type) {
        case EasingType::EaseInSine: return EaseInSine(t);
        case EasingType::EaseOutSine: return EaseOutSine(t);
        case EasingType::EaseInOutSine: return EaseInOutSine(t);
        case EasingType::EaseInQuad: return EaseInQuad(t);
        case EasingType::EaseOutQuad: return EaseOutQuad(t);
        case EasingType::EaseInOutQuad: return EaseInOutQuad(t);
        case EasingType::EaseInCubic: return EaseInCubic(t);
        case EasingType::EaseOutCubic: return EaseOutCubic(t);
        case EasingType::EaseInOutCubic: return EaseInOutCubic(t);
        case EasingType::EaseInQuart: return EaseInQuart(t);
        case EasingType::EaseOutQuart: return EaseOutQuart(t);
        case EasingType::EaseInOutQuart: return EaseInOutQuart(t);
        case EasingType::EaseInQuint: return EaseInQuint(t);
        case EasingType::EaseOutQuint: return EaseOutQuint(t);
        case EasingType::EaseInOutQuint: return EaseInOutQuint(t);
        case EasingType::EaseInExpo: return EaseInExpo(t);
        case EasingType::EaseOutExpo: return EaseOutExpo(t);
        case EasingType::EaseInOutExpo: return EaseInOutExpo(t);
        case EasingType::EaseInCirc: return EaseInCirc(t);
        case EasingType::EaseOutCirc: return EaseOutCirc(t);
        case EasingType::EaseInOutCirc: return EaseInOutCirc(t);
        case EasingType::EaseInBack: return EaseInBack(t);
        case EasingType::EaseOutBack: return EaseOutBack(t);
        case EasingType::EaseInOutBack: return EaseInOutBack(t);
        case EasingType::EaseInElastic: return EaseInElastic(t);
        case EasingType::EaseOutElastic: return EaseOutElastic(t);
        case EasingType::EaseInOutElastic: return EaseInOutElastic(t);
        case EasingType::EaseInBounce: return EaseInBounce(t);
        case EasingType::EaseOutBounce: return EaseOutBounce(t);
        case EasingType::EaseInOutBounce: return EaseInOutBounce(t);
        default: return t; // Linear
    }
}


void Tween::Play()
{
    m_isActive = true;
    m_elapsed = 0.0f;
}

/// <summary>
/// 停止処理
/// </summary>
void Tween::Stop()
{
    // 非アクティブに設定
    m_isActive      = false;
    // Transformの登録を解除
    m_transform     = nullptr;
    m_onComplete    = nullptr;
    // 数値のリセット
    m_doMove        = false;
    m_doRotation    = false;
    m_doScale       = false;
    m_startPosition = DirectX::SimpleMath::Vector3::Zero;
    m_endPosition   = DirectX::SimpleMath::Vector3::Zero;
    m_startRotation = DirectX::SimpleMath::Quaternion::Identity;
    m_endRotation   = DirectX::SimpleMath::Quaternion::Identity;
    m_startScale    = DirectX::SimpleMath::Vector3::Zero;
    m_endScale      = DirectX::SimpleMath::Vector3::Zero;
    m_duration      = 0.0f;
    m_delay         = 0.0f;
    m_loopCount     = 0;
    m_loopType      = Tween::LoopType::None;
    m_easeType      = Tween::EasingType::Linear;
}

/// <summary>
/// 指定した座標へ移動するアニメーションを設定する。
/// </summary>
/// <param name="end">移動先の座標</param>
/// <param name="duration">移動にかかる時間</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween &Tween::DOMove(const DirectX::SimpleMath::Vector3& end, float duration)
{
    m_startPosition = m_transform->GetLocalPosition();
    m_endPosition   = end;
    m_duration = duration;
    m_doMove = true;
    return *this;
}

/// <summary>
/// X軸方向の移動アニメーションを設定する。
/// </summary>
/// <param name="endX">X軸の移動先座標</param>
/// <param name="duration">移動にかかる時間</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween& Tween::DOMoveX(float endX, float duration)
{
    m_startPosition = m_transform->GetLocalPosition();
    m_endPosition = {endX,m_startPosition.y,m_startPosition.z};
    m_duration = duration;
    m_doMove = true;
    return *this;
}

/// <summary>
/// Y軸方向の移動アニメーションを設定する。
/// </summary>
/// <param name="endY">Y軸の移動先座標</param>
/// <param name="duration">移動にかかる時間</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween& Tween::DOMoveY(float endY, float duration)
{
    m_startPosition = m_transform->GetLocalPosition();
    m_endPosition = { m_startPosition.x,endY,m_startPosition.z };
    m_duration = duration;
    m_doMove = true;
    return *this;
}

/// <summary>
/// Z軸方向の移動アニメーションを設定する。
/// </summary>
/// <param name="endZ">Z軸の移動先座標</param>
/// <param name="duration">移動にかかる時間</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween& Tween::DOMoveZ(float endZ, float duration)
{
    m_startPosition = m_transform->GetLocalPosition();
    m_endPosition = { m_startPosition.x,m_startPosition.y,endZ };
    m_duration = duration;
    m_doMove = true;
    return *this;
}

/// <summary>
/// 指定した回転角度へ回転するアニメーションを設定する。
/// </summary>
/// <param name="end">回転の終了角度（度数法）</param>
/// <param name="duration">回転にかかる時間</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween& Tween::DORotation(const DirectX::SimpleMath::Vector3& end, float duration)
{
    m_startRotation = m_transform->GetLocalRotation();
    // クォータニオンに変換
    m_endRotation = this->ConvertToYawPitchRoll(end);
    m_duration = duration;
    m_doRotation = true;
    return *this;
}

/// <summary>
/// X軸の回転アニメーションを設定する。
/// </summary>
/// <param name="endX">X軸の回転終了角度（度数法）</param>
/// <param name="duration">回転にかかる時間</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween& Tween::DORotationX(float endX, float duration)
{
    m_startRotation = m_transform->GetLocalRotation();
    // 度数法に直す
    DirectX::SimpleMath::Vector3 endRotation = this->ConvertToDegrees(m_startRotation.ToEuler());
    // Xのみ終了値を変更
    endRotation.x = endX;
    // クォータニオンに変換
    m_endRotation = this->ConvertToYawPitchRoll(endRotation);

    m_duration = duration;
    m_doRotation = true;
    return *this;
}

/// <summary>
/// Y軸の回転アニメーションを設定する。
/// </summary>
/// <param name="endY">Y軸の回転終了角度（度数法）</param>
/// <param name="duration">回転にかかる時間</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween& Tween::DORotationY(float endY, float duration)
{
    m_startRotation = m_transform->GetLocalRotation();
    // 度数法に直す
    DirectX::SimpleMath::Vector3 endRotation = this->ConvertToDegrees(m_startRotation.ToEuler());
    // Yのみ終了値を変更
    endRotation.y = endY;
    // クォータニオンに変換
    m_endRotation = this->ConvertToYawPitchRoll(endRotation);
    m_duration = duration;
    m_doRotation = true;
    return *this;
}

/// <summary>
/// Z軸の回転アニメーションを設定する。
/// </summary>
/// <param name="endZ">Z軸の回転終了角度（度数法）</param>
/// <param name="duration">回転にかかる時間</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween& Tween::DORotationZ(float endZ, float duration)
{
    m_startRotation = m_transform->GetLocalRotation();
    // 度数法に直す
    DirectX::SimpleMath::Vector3 endRotation = this->ConvertToDegrees(m_startRotation.ToEuler());
    // Zのみ終了値を変更
    endRotation.z = endZ;
    // クォータニオンに変換
    m_endRotation = this->ConvertToYawPitchRoll(endRotation);
    m_duration = duration;
    m_doRotation = true;
    return *this;
}


/// <summary>
/// 指定したスケールへ変更するアニメーションを設定する。
/// </summary>
/// <param name="end">スケールの終了値</param>
/// <param name="duration">スケール変更にかかる時間</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween& Tween::DOScale(const DirectX::SimpleMath::Vector3& end, float duration)
{
    m_startScale = m_transform->GetLocalScale();
    m_endScale = end;
    m_duration = duration;
    m_doScale = true;
    return *this;
}

/// <summary>
/// X軸のスケール変更アニメーションを設定する。
/// </summary>
/// <param name="endX">X軸のスケール終了値</param>
/// <param name="duration">スケール変更にかかる時間</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween& Tween::DOScaleX(float endX, float duration)
{
    m_startScale = m_transform->GetLocalScale();
    m_endScale = { endX,m_startScale.y,m_startScale.z };
    m_duration = duration;
    m_doScale = true;
    return *this;
}

/// <summary>
/// Y軸のスケール変更アニメーションを設定する。
/// </summary>
/// <param name="endY">Y軸のスケール終了値</param>
/// <param name="duration">スケール変更にかかる時間</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween& Tween::DOScaleY(float endY, float duration)
{
    m_startScale = m_transform->GetLocalScale();
    m_endScale = { m_startScale.x,endY,m_startScale.z };
    m_duration = duration;
    m_doScale = true;
    return *this;
}

/// <summary>
/// Z軸のスケール変更アニメーションを設定する。
/// </summary>
/// <param name="endZ">Z軸のスケール終了値</param>
/// <param name="duration">スケール変更にかかる時間</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween& Tween::DOScaleZ(float endZ, float duration)
{
    m_startScale = m_transform->GetLocalScale();
    m_endScale = { m_startScale.x,m_startScale.y,endZ };
    m_duration = duration;
    m_doScale = true;
    return *this;
}

/// <summary>
/// イージングの種類を設定する。
/// </summary>
/// <param name="ease">イージングの種類</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween& Tween::SetEase(Tween::EasingType ease)
{
    m_easeType = ease;
    return *this;
}

/// <summary>
/// ループ回数とループの種類を設定する。
/// </summary>
/// <param name="count">ループ回数</param>
/// <param name="type">ループの種類</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween& Tween::SetLoops(int count, Tween::LoopType type)
{
    m_loopCount = count;
    m_loopType = type;
    return *this;
}

/// <summary>
/// 遅延時間を設定する。
/// </summary>
/// <param name="delayTime">遅延時間</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween &Tween::SetDelay(float delayTime)
{
    m_delay = delayTime;
    return *this;
}

/// <summary>
/// アニメーション完了時のコールバックを設定する。
/// </summary>
/// <param name="callback">完了時のコールバック関数</param>
/// <returns>自身のTweenオブジェクト</returns>
Tween& Tween::OnComplete(Callback callback)
{
    m_onComplete = callback;
    return *this;
}

/// <summary>
/// 回転ベクトルをクォータニオンに変換する。
/// </summary>
/// <param name="rotation">回転を表すベクトル（度数法）</param>
/// <returns>変換後のクォータニオン</returns>
DirectX::SimpleMath::Quaternion Tween::ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation) {
    return DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
        DirectX::XMConvertToRadians(rotation.y),
        DirectX::XMConvertToRadians(rotation.x),
        DirectX::XMConvertToRadians(rotation.z)
    );
}

/// <summary>
/// ラジアン単位のベクトルを度数（デグリー）に変換する。
/// </summary>
/// <param name="radianVec">変換対象のベクトル（ラジアン単位）</param>
/// <returns>変換後のベクトル（度数法）</returns>
DirectX::SimpleMath::Vector3 Tween::ConvertToDegrees(const DirectX::SimpleMath::Vector3& radianVec)
{
    return {
        DirectX::XMConvertToDegrees(radianVec.x),
        DirectX::XMConvertToDegrees(radianVec.y),
        DirectX::XMConvertToDegrees(radianVec.z)
    };
}