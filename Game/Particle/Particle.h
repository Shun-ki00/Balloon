#pragma once

class Particle
{

public:

    // 値を設定する
    void SetParameters(
        const DirectX::SimpleMath::Vector3& position,
        const DirectX::SimpleMath::Vector3& velocity,
        const DirectX::SimpleMath::Vector3& acceleration,
        const float& lifetime,
        const float& startSize,
        const float& endSize,
        const DirectX::SimpleMath::Vector4& startColor,
        const DirectX::SimpleMath::Vector4& endColor
    );

    // 状態を取得
    bool GetIsActive() const { return m_isActive; }
    // 頂点データを取得
    DirectX::VertexPositionColorTexture GetVertexData() const { return m_inputData; }

public:

    // コンストラクタ
	Particle();
    // デストラクタ
	~Particle() = default;

    // 初期化処理
    void Initialize();
    // 更新処理
    void Update(const float& elapsedTime);
    
private:

    bool m_isActive;

    // 頂点データ
    DirectX::VertexPositionColorTexture m_inputData;

    // 座標
    DirectX::SimpleMath::Vector3 m_position;
    // 回転角
    float m_angle;

    // 速度
    DirectX::SimpleMath::Vector3 m_velocity;
    // 加速度
    DirectX::SimpleMath::Vector3 m_acceleration;

    // 重力値
    float m_gravity;

    // ライフタイム
    float m_totalLifetime; // 最大寿命
    float m_currentLifetime; // 残り寿命

    // サイズ補間
    float m_startSize;
    float m_endSize;
    float m_currentSize;

    // カラー補間
    DirectX::SimpleMath::Vector4 m_startColor;
    DirectX::SimpleMath::Vector4 m_endColor;
    DirectX::SimpleMath::Vector4 m_currentColor;
};