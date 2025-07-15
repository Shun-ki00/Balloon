#pragma once
#include "pch.h"

// パラメータのデータ構造

// === ステアリングビヘイビア ===

// 揺れるビヘイビア
struct FloatBehaviorParams
{
	bool isActive{};                          // ビヘイビアが有効か
	float floatRange{};                       // 揺れ幅
	float floatCycleSpeed{};                  // 周期の速さ
	float floatSpeed{};                       // 速度
	DirectX::SimpleMath::Vector3 direction{}; // 方向
};

// ノックバック時の反応を制御するビヘイビア
struct KnockbackBehaviorParams
{
	bool isActive{};     // ビヘイビアが有効か
	int count{};         // ノックバック回数または対象数
	float radius{};      // ノックバックの有効範囲
	float force{};       // ノックバックの強さ
};

// ターゲットを追跡するビヘイビア
struct SeekBehaviorParams
{
	bool isActive{};                       // ビヘイビアが有効か
	DirectX::SimpleMath::Vector3 offset{}; // 位置のオフセット
	float predictionMultiplier{};          // 予測時間の倍率
	float seekSpeed{};                     // 移動速度
};

// ターゲットから離れる逃走ビヘイビア
struct FleeBehaviorParams
{
	bool isActive{};         // ビヘイビアが有効か
	float detectionRadius{}; // 敵を検知する範囲
	float speed{};           // 移動速度
	float forceStrength{};   // 加える逃走力の強さ
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





// === オブジェクト ===

// プレイヤー
struct PlayerParams
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
	bool fixed;
	float balloonIndex;
	FloatBehaviorParams floatBehaviorParams;
	KnockbackBehaviorParams knockbackBehaviorParams;
};
// 敵
struct EnemyParams 
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
	bool fixed;
	float balloonIndex;
	FloatBehaviorParams floatBehaviorParams;
	KnockbackBehaviorParams knockbackBehaviorParams;
	SeekBehaviorParams seekBehaviorParams;
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

// ==== ステアリングビヘイビア ====

inline void from_json(const nlohmann::json& j, FloatBehaviorParams& p)
{
	auto node = j.at("FloatBehavior");

	p.isActive = node.at("isActive").get<bool>();
	p.floatRange = node.at("floatRange").get<float>();
	p.floatCycleSpeed = node.at("floatCycleSpeed").get<float>();
	p.floatSpeed = node.at("floatSpeed").get<float>();
	p.direction = ParseVector3(node.at("direction"));
}

inline void from_json(const nlohmann::json& j, KnockbackBehaviorParams& p)
{
	auto node = j.at("KnockbackBehavior");

	p.isActive = node.at("isActive").get<bool>();
	p.count = node.at("count").get<int>();
	p.radius = node.at("radius").get<float>();
	p.force = node.at("force").get<float>();
}

inline void from_json(const nlohmann::json& j, SeekBehaviorParams& p)
{
	auto node = j.at("SeekBehavior");

	p.isActive = node.at("isActive").get<bool>();
	p.offset = ParseVector3(node.at("offset"));
	p.predictionMultiplier = node.at("predictionMultiplier").get<float>();
	p.seekSpeed = node.at("seekSpeed").get<float>();
}

inline void from_json(const nlohmann::json& j, FleeBehaviorParams& p)
{
	auto node = j.at("FleeBehavior");

	p.isActive = node.at("isActive").get<bool>();
	p.detectionRadius = node.at("detectionRadius").get<float>();
	p.speed = node.at("speed").get<float>();
	p.forceStrength = node.at("forceStrength").get<float>();
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
	p.floatBehaviorParams = player.get<FloatBehaviorParams>();
	p.knockbackBehaviorParams = player.get<KnockbackBehaviorParams>();
}

inline void from_json(const nlohmann::json& j, EnemyParams& e)
{
	e.position = ParseVector3(j.at("position"));
	e.rotation = ParseVector3(j.at("rotation"));
	e.scale = ParseVector3(j.at("scale"));
	e.fixed = j.at("fixed").get<bool>();
	e.balloonIndex = j.at("balloonIndex").get<float>();
	e.floatBehaviorParams = j.get<FloatBehaviorParams>();
	e.knockbackBehaviorParams = j.get<KnockbackBehaviorParams>();
	e.seekBehaviorParams = j.get<SeekBehaviorParams>();
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


inline void from_json(const nlohmann::json& j, ParticleParameters& p)
{
	j.at("duration").get_to(p.duration);
	j.at("startDelay").get_to(p.startDelay);
	j.at("lifeTime").get_to(p.lifeTime);
	j.at("speed").get_to(p.speed);
	j.at("rotation").get_to(p.rotation);
	j.at("gravityModifier").get_to(p.gravityModifier);
	j.at("emissionRate").get_to(p.emissionRate);
	j.at("coneAngle").get_to(p.coneAngle);
	j.at("coneRadius").get_to(p.coneRadius);
	j.at("coneHeight").get_to(p.coneHeight);
	j.at("sphereRadius").get_to(p.sphereRadius);
	j.at("sphereRandomDirectionStrength").get_to(p.sphereRandomDirectionStrength);

	j.at("texture").get_to(p.texture);
	j.at("shader").get_to(p.shader);

	j.at("isLooping").get_to(p.isLooping);
	j.at("prewarm").get_to(p.prewarm);
	j.at("isPlaying").get_to(p.isPlaying);
	j.at("coneEmitFromShell").get_to(p.coneEmitFromShell);
	j.at("sphereEmitFromShell").get_to(p.sphereEmitFromShell);

	std::vector<float> vec3;
	j.at("startScale").get_to(vec3); p.startScale = { vec3[0], vec3[1], vec3[2] };
	j.at("coneDirection").get_to(vec3); p.coneDirection = { vec3[0], vec3[1], vec3[2] };
	j.at("conePosition").get_to(vec3); p.conePosition = { vec3[0], vec3[1], vec3[2] };
	j.at("sphereCenter").get_to(vec3); p.sphereCenter = { vec3[0], vec3[1], vec3[2] };

	std::vector<float> vec4;
	j.at("startColor").get_to(vec4); p.startColor = { vec4[0], vec4[1], vec4[2], vec4[3] };
}


