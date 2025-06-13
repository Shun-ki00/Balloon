#pragma once
#include "Game/Parameters/ParameterKeys.h"
#include "Game/Particle/Particle.h"

class Particle;
class Parameters;

class ParticleEmitter
{
public:

	bool GetIsActive() const { return m_isEmitting; }

	// インプットデータを取得する
	std::vector<DirectX::VertexPositionColorTexture> GetInputDatas() const { return m_inputDatas; }
	// ピクセルシェーダを取得する
	ID3D11PixelShader* GetPixelShader() const { return m_pixelShader; }

	// テクスチャを取得する
	ID3D11ShaderResourceView* GetTexture() { return m_texture; }


public:

	// コンストラクタ
	ParticleEmitter();
	// デストラクタ
	~ParticleEmitter() = default;

	// 初期化処理
	void Initialize(ParametersID id);

	// 更新処理
	void Update(const float& elapsedTime);

	void Emit();

	void Play();

	void Stop();


private:
	Parameters* m_parameters;

	// パーティクル粒子
	std::vector<std::unique_ptr<Particle>> m_particles;
	std::vector<Particle*> m_activeParticles;
	// インプットデータ
	std::vector<DirectX::VertexPositionColorTexture> m_inputDatas;
	// テクスチャ
	ID3D11ShaderResourceView* m_texture;
	// ピクセルシェーダー
	ID3D11PixelShader* m_pixelShader;

	float m_emitTimer;               // エミットタイマー
	float m_emissionInterval;         // 1個発生するまでの間隔 ( = 1.0f / m_emissionRate )
	float m_emissionDurationTimer;    // エミッション継続時間管理

	bool m_isEmitting = true;                // 発生中かどうか

	// 基本設定
	float m_emissionRate;              // 1秒あたり出す粒子数
	float m_emissionDuration;          // エミットする継続時間
	float m_particleLifetime;          // 1粒子の寿命

	// 発生範囲
	DirectX::SimpleMath::Vector3 m_emitPositionMin;  // 発生範囲 最小座標
	DirectX::SimpleMath::Vector3 m_emitPositionMax;  // 発生範囲 最大座標

	// 発生方向
	DirectX::SimpleMath::Vector3 m_emitDirectionMin; // 発射方向 最小ベクトル
	DirectX::SimpleMath::Vector3 m_emitDirectionMax; // 発射方向 最大ベクトル

	// 速度
	float m_emitSpeedMin;             // 最小発射速度
	float m_emitSpeedMax;             // 最大発射速度

	// サイズ
	float m_startSizeMin;             // 開始サイズ最小
	float m_startSizeMax;             // 開始サイズ最大
	float m_endSizeMin;               // 終了サイズ最小
	float m_endSizeMax;               // 終了サイズ最大

	// 回転
	float m_startRotationMin;         // 開始回転最小角（度）
	float m_startRotationMax;         // 開始回転最大角（度）
	float m_rotationSpeedMin;         // 回転速度最小（度/秒）
	float m_rotationSpeedMax;         // 回転速度最大（度/秒）

	// 色
	DirectX::SimpleMath::Vector4 m_startColor;        // 開始色
	DirectX::SimpleMath::Vector4 m_endColor;           // 終了色

	// 重力・加速度
	bool m_isGravityEnabled;          // 重力有効フラグ
	DirectX::SimpleMath::Vector3 m_gravityAcceleration; // 重力加速度ベクトル

	// その他演出
	float m_randomnessFactor;         // ランダムばらつきの強さ
	bool m_isLooping;                 // ループするかどうか

	
};