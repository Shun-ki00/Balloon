#pragma once

//// 浮力を発生させるビヘイビア（常に上向き等）
//struct FloatForceBehaviorParams
//{
//	bool isActive{};                 // ビヘイビアが有効か
//	DirectX::XMFLOAT3 direction{};   // 力を加える方向（通常は上向き）
//	float power{};                   // 加える力の強さ
//};
//
//
//// ノックバック時の反応を制御するビヘイビア
//struct KnockbackBehaviorParams
//{
//	bool isActive{};     // ビヘイビアが有効か
//	int count{};         // ノックバック回数または対象数
//	float radius{};      // ノックバックの有効範囲
//	float force{};       // ノックバックの強さ
//};
//
//
//// 押し返し（反発）を制御するビヘイビア
//struct PushBackBehaviorParams
//{
//	bool isActive{};     // ビヘイビアが有効か
//	float stageMin{};    // 効果の最小距離（開始点）
//	float stageMax{};    // 効果の最大距離（終了点）
//	float strength{};    // 押し返しの強さ
//};
//
//
//// ターゲットを追跡するビヘイビア
//struct SeekBehaviorParams
//{
//	bool isActive{};             // ビヘイビアが有効か
//	float predictionMultiplier{}; // ターゲットの未来位置をどれだけ予測するか（秒）
//	float speed{};               // 移動速度
//	float forceStrength{};       // 加える追跡力の強さ
//};
//
//
//// 風による外力のビヘイビア
//struct WindBehaviorParams
//{
//	bool isActive{};        // ビヘイビアが有効か
//	float minStrength{};    // 風の最小強度
//	float maxStrength{};    // 風の最大強度
//	float minDuration{};    // 風が吹く最短時間
//	float maxDuration{};    // 風が吹く最長時間
//	float idleTime{};       // 次の風までの待機時間
//	float currentDuration{};// 現在の風の残り継続時間
//};
//
//
//// ランダムに動き回るふらふら移動ビヘイビア
//struct WanderBehaviorParams
//{
//	bool isActive{};         // ビヘイビアが有効か
//	float jitter{};          // ランダム変動の強さ（方向変化）
//	float radius{};          // 円周移動の半径
//	float distance{};        // 進行方向への距離（中心点からの距離）
//	float speed{};           // 移動速度
//	float forceStrength{};   // 加える力の強さ
//};
//
//
//// ターゲットから離れる逃走ビヘイビア
//struct FleeBehaviorParams
//{
//	bool isActive{};         // ビヘイビアが有効か
//	float detectionRadius{}; // 敵を検知する範囲
//	float speed{};           // 移動速度
//	float forceStrength{};   // 加える逃走力の強さ
//};
//
//
//// すべてのステアリングビヘイビアをまとめた構造体
//struct SteeringBehaviorParams
//{
//	FloatForceBehaviorParams floatForce;       // 浮力ビヘイビア
//	KnockbackBehaviorParams knockback;         // ノックバックビヘイビア
//	PushBackBehaviorParams pushBack;           // プッシュバックビヘイビア
//	SeekBehaviorParams seek;             // 追跡ビヘイビア
//	WindBehaviorParams wind;             // 風ビヘイビア
//	WanderBehaviorParams wander;         // ふらふら移動ビヘイビア
//	FleeBehaviorParams flee;             // 逃走ビヘイビア
//};


// プレイヤー


// 敵










// パラメータの種類
enum class ParametersID
{
	// エフェクト
	EFFECT,
	// ステアリングビヘイビア
	STEERING_BEHAVIOR, 
	// プレイヤー
	PLAYER,
	// 敵
	ENEMY,

	PARTICLE,

	BALLOON_EXPLOSION,

};


enum class ParameterKeysF
{
	// プレイヤー
	PlayerBrakingRate,
	PlayerMass,
	PlayerMaxForce,
	PlayerMaxSpeed,
	PlayerMaxTurnRate,
	PlayerRadius,
	PlayerScale,
	// 敵

	// 風船

	// UI

	// 風の挙動 
	WindMinStrength,
	WindMaxStrength,
	WindMinDuration,
	WindMaxDuration,
	WindIdleTime,

	// ノックバック
	KnockbackCount,
	KnockbackFoce,
	KnockbackRadius,

	// パーティクル
	EmissionRate,
	EmissionDuration,
	ParticleLifetime,
	EmitSpeedMin,
	EmitSpeedMax,
	StartSizeMin,
	StartSizeMax,
	EndSizeMin,
	EndSizeMax,
	StartRotationMin,
	StartRotationMax,
	RotationSpeedMin,
	RotationSpeedMax,
	RandomnessFactor

};

enum class ParameterKeysI
{
	// プレイヤー
	Player,
	// 敵
	Number
	// 風船

	// UI
};

enum class ParameterKeysB
{
	// パーティクル
	IsLooping,
	IsGravityEnabled,
};

enum class ParameterKeysV3
{
	// プレイヤー
	Player,
	// 敵

	// 風船

	// UI


	// パーティクル
	EmitPositionMin,
	EmitPositionMax,
	EmitDirectionMin,
	EmitDirectionMax,
	GravityAcceleration,
};

enum class ParameterKeysV4
{
	// パーティクル
	StartColor,
	EndColor,
};

enum class ParameterKeysS
{
	Texture,
	Shader,
};
