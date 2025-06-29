#pragma once
#include "pch.h"

// �p�����[�^�̃f�[�^�\��



// === �I�u�W�F�N�g ===

// �v���C���[
struct PlayerParams
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
	bool fixed;
	float balloonIndex;
};
// �G
struct EnemyParams
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
	bool fixed;
	float balloonIndex;
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

// === �X�e�A�����O�r�w�C�r�A ===

// ���͂𔭐�������r�w�C�r�A�i��ɏ�������j
struct FloatForceBehaviorParams
{
	bool isActive{};                            // �r�w�C�r�A���L����
	DirectX::SimpleMath::Vector3 direction{};   // �͂�����������i�ʏ�͏�����j
	float power{};                              // ������͂̋���
};


// �m�b�N�o�b�N���̔����𐧌䂷��r�w�C�r�A
struct KnockbackBehaviorParams
{
	bool isActive{};     // �r�w�C�r�A���L����
	int count{};         // �m�b�N�o�b�N�񐔂܂��͑Ώې�
	float radius{};      // �m�b�N�o�b�N�̗L���͈�
	float force{};       // �m�b�N�o�b�N�̋���
};


// �����Ԃ��i�����j�𐧌䂷��r�w�C�r�A
struct PushBackBehaviorParams
{
	bool isActive{};     // �r�w�C�r�A���L����
	float stageMin{};    // ���ʂ̍ŏ������i�J�n�_�j
	float stageMax{};    // ���ʂ̍ő勗���i�I���_�j
	float strength{};    // �����Ԃ��̋���
};


// �^�[�Q�b�g��ǐՂ���r�w�C�r�A
struct SeekBehaviorParams
{
	bool isActive{};             // �r�w�C�r�A���L����
	float predictionMultiplier{}; // �^�[�Q�b�g�̖����ʒu���ǂꂾ���\�����邩�i�b�j
	float speed{};               // �ړ����x
	float forceStrength{};       // ������ǐ՗͂̋���
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


// �����_���ɓ������ӂ�ӂ�ړ��r�w�C�r�A
struct WanderBehaviorParams
{
	bool isActive{};         // �r�w�C�r�A���L����
	float jitter{};          // �����_���ϓ��̋����i�����ω��j
	float radius{};          // �~���ړ��̔��a
	float distance{};        // �i�s�����ւ̋����i���S�_����̋����j
	float speed{};           // �ړ����x
	float forceStrength{};   // ������͂̋���
};


// �^�[�Q�b�g���痣��铦���r�w�C�r�A
struct FleeBehaviorParams
{
	bool isActive{};         // �r�w�C�r�A���L����
	float detectionRadius{}; // �G�����m����͈�
	float speed{};           // �ړ����x
	float forceStrength{};   // �����铦���͂̋���
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