#pragma once
#include "pch.h"

// �p�����[�^�̃f�[�^�\��

// === �X�e�A�����O�r�w�C�r�A ===

// �h���r�w�C�r�A
struct FloatBehaviorParams
{
	bool isActive{};                          // �r�w�C�r�A���L����
	float floatRange{};                       // �h�ꕝ
	float floatCycleSpeed{};                  // �����̑���
	float floatSpeed{};                       // ���x
	DirectX::SimpleMath::Vector3 direction{}; // ����
};

// �m�b�N�o�b�N���̔����𐧌䂷��r�w�C�r�A
struct KnockbackBehaviorParams
{
	bool isActive{};     // �r�w�C�r�A���L����
	int count{};         // �m�b�N�o�b�N�񐔂܂��͑Ώې�
	float radius{};      // �m�b�N�o�b�N�̗L���͈�
	float force{};       // �m�b�N�o�b�N�̋���
};

// �^�[�Q�b�g��ǐՂ���r�w�C�r�A
struct SeekBehaviorParams
{
	bool isActive{};                       // �r�w�C�r�A���L����
	DirectX::SimpleMath::Vector3 offset{}; // �ʒu�̃I�t�Z�b�g
	float predictionMultiplier{};          // �\�����Ԃ̔{��
	float seekSpeed{};                     // �ړ����x
};

// �^�[�Q�b�g���痣��铦���r�w�C�r�A
struct FleeBehaviorParams
{
	bool isActive{};         // �r�w�C�r�A���L����
	float detectionRadius{}; // �G�����m����͈�
	float speed{};           // �ړ����x
	float forceStrength{};   // �����铦���͂̋���
};


// ���ɂ��O�͂̃r�w�C�r�A
struct WindBehaviorParams
{
	bool isActive{};        // �r�w�C�r�A���L����
	float minStrength{};    // ���̍ŏ����x
	float maxStrength{};    // ���̍ő勭�x
	float minDuration{};    // ���������ŒZ����
	float maxDuration{};    // ���������Œ�����
	float idleTime{};       // ���̕��܂ł̑ҋ@����
	float currentDuration{};// ���݂̕��̎c��p������
};





// === �I�u�W�F�N�g ===

// �v���C���[
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
// �G
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
// ���D
struct BalloonParams
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
};

// �ؔ�
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




// === �J���� ===

// �Œ�J����
struct FixedCameraParams
{
	DirectX::SimpleMath::Vector3 direction;
	DirectX::SimpleMath::Vector3 rotation;
};
// �ǐՃJ����
struct FollowCameraParams
{
	std::string objectId;
	int objectNumber;
	DirectX::SimpleMath::Vector3 distance;
};


// �p�[�e�B�N���\����
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




// �Q�[���f�[�^
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

// ==== �X�e�A�����O�r�w�C�r�A ====

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


