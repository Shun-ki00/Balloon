#pragma once
#include "pch.h"

// パラメータのデータ構造



// === オブジェクト ===

// プレイヤー
struct PlayerParams
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
	bool fixed;
	float balloonIndex;
};
// 敵
struct EnemyParams
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
	bool fixed;
	float balloonIndex;
};
// 風船
struct BalloonParams
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
};

// 木箱
struct WoodBoxParams
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
};

// UI
struct UIParams
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
};




// === カメラ ===

// 固定カメラ
struct FixedCameraParams
{
	DirectX::SimpleMath::Vector3 direction;
	DirectX::SimpleMath::Vector3 rotation;
};
// 追跡カメラ
struct FollowCameraParams
{
	std::string objectId;
	int objectNumber;
	DirectX::SimpleMath::Vector3 distance;
};

// === ステアリングビヘイビア ===

// 浮力を発生させるビヘイビア（常に上向き等）
struct FloatForceBehaviorParams
{
	bool isActive{};                            // ビヘイビアが有効か
	DirectX::SimpleMath::Vector3 direction{};   // 力を加える方向（通常は上向き）
	float power{};                              // 加える力の強さ
};


// ノックバック時の反応を制御するビヘイビア
struct KnockbackBehaviorParams
{
	bool isActive{};     // ビヘイビアが有効か
	int count{};         // ノックバック回数または対象数
	float radius{};      // ノックバックの有効範囲
	float force{};       // ノックバックの強さ
};


// 押し返し（反発）を制御するビヘイビア
struct PushBackBehaviorParams
{
	bool isActive{};     // ビヘイビアが有効か
	float stageMin{};    // 効果の最小距離（開始点）
	float stageMax{};    // 効果の最大距離（終了点）
	float strength{};    // 押し返しの強さ
};


// ターゲットを追跡するビヘイビア
struct SeekBehaviorParams
{
	bool isActive{};             // ビヘイビアが有効か
	float predictionMultiplier{}; // ターゲットの未来位置をどれだけ予測するか（秒）
	float speed{};               // 移動速度
	float forceStrength{};       // 加える追跡力の強さ
};


// 風による外力のビヘイビア
struct WindBehaviorParams
{
	bool isActive{};        // ビヘイビアが有効か
	float minStrength{};    // 風の最小強度
	float maxStrength{};    // 風の最大強度
	float minDuration{};    // 風が吹く最短時間
	float maxDuration{};    // 風が吹く最長時間
	float idleTime{};       // 次の風までの待機時間
	float currentDuration{};// 現在の風の残り継続時間
};


// ランダムに動き回るふらふら移動ビヘイビア
struct WanderBehaviorParams
{
	bool isActive{};         // ビヘイビアが有効か
	float jitter{};          // ランダム変動の強さ（方向変化）
	float radius{};          // 円周移動の半径
	float distance{};        // 進行方向への距離（中心点からの距離）
	float speed{};           // 移動速度
	float forceStrength{};   // 加える力の強さ
};


// ターゲットから離れる逃走ビヘイビア
struct FleeBehaviorParams
{
	bool isActive{};         // ビヘイビアが有効か
	float detectionRadius{}; // 敵を検知する範囲
	float speed{};           // 移動速度
	float forceStrength{};   // 加える逃走力の強さ
};



// パーティクル構造体
struct ParticleParameters
{
	// float
	float duration = 0.0f;
	float startDelay = 0.0f;
	float lifeTime = 0.0f;
	float speed = 0.0f;
	float rotation = 0.0f;
	float gravityModifier = 0.0f;
	float emissionRate = 0.0f;
	float coneAngle = 0.0f;
	float coneRadius = 0.0f;
	float coneHeight = 0.0f;
	float sphereRadius = 0.0f;
	float sphereRandomDirectionStrength = 0.0f;

	// string
	std::string texture;
	std::string shader;

	// bool
	bool isLooping = false;
	bool prewarm = false;
	bool isPlaying = false;
	bool coneEmitFromShell = false;
	bool sphereEmitFromShell = false;

	// Vector3
	DirectX::SimpleMath::Vector3 startScale = { 1.0f, 1.0f, 1.0f };
	DirectX::SimpleMath::Vector3 coneDirection = { 0.0f, 1.0f, 0.0f };
	DirectX::SimpleMath::Vector3 conePosition = { 0.0f, 0.0f, 0.0f };
	DirectX::SimpleMath::Vector3 sphereCenter = { 0.0f, 0.0f, 0.0f };

	// Vector4
	DirectX::SimpleMath::Vector4 startColor = { 1.0f, 1.0f, 1.0f, 1.0f };
};


// ゲームデータ
struct SceneLinkParams
{
	int stageNumber = 0;                
};


using json = nlohmann::json;

inline DirectX::SimpleMath::Vector3 ParseVector3(const nlohmann::json& j)
{
	return {
		j.at(0).get<float>(),
		j.at(1).get<float>(),
		j.at(2).get<float>()
	};
}

inline void from_json(const nlohmann::json& j, SceneLinkParams& s)
{
	//auto stage = j.at("SceneLinkParams");

	s.stageNumber = j.at("stageNumber").get<int>();
}

inline void to_json(nlohmann::json& j, const SceneLinkParams& p)
{
	j = {
		  { "stageNumber", p.stageNumber },
	};
}


inline void from_json(const nlohmann::json& j, PlayerParams& p)
{
	auto player = j.at("Player");

	p.position = ParseVector3(player.at("position"));
	p.rotation = ParseVector3(player.at("rotation"));
	p.scale = ParseVector3(player.at("scale"));
	p.fixed = player.at("fixed").get<bool>();
	p.balloonIndex = player.at("balloonIndex").get<float>();
}

inline void from_json(const nlohmann::json& j, EnemyParams& e)
{
	e.position = ParseVector3(j.at("position"));
	e.rotation = ParseVector3(j.at("rotation"));
	e.scale = ParseVector3(j.at("scale"));
	e.fixed = j.at("fixed").get<bool>();
	e.balloonIndex = j.at("balloonIndex").get<float>();
}

inline void from_json(const nlohmann::json& j, BalloonParams& b)
{
	b.position = ParseVector3(j.at("position"));
	b.rotation = ParseVector3(j.at("rotation"));
	b.scale = ParseVector3(j.at("scale"));
}

inline void from_json(const nlohmann::json& j, WoodBoxParams& w)
{
	auto woodBox = j.at("WoodBox");

	w.position = ParseVector3(woodBox.at("position"));
	w.rotation = ParseVector3(woodBox.at("rotation"));
	w.scale = ParseVector3(woodBox.at("scale"));
}

inline void from_json(const nlohmann::json& j, UIParams& u)
{
	u.position = ParseVector3(j.at("position"));
	u.rotation = ParseVector3(j.at("rotation"));
	u.scale = ParseVector3(j.at("scale"));
}