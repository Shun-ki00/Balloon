#pragma once
#include "pch.h"

// �p�����[�^�̃f�[�^�\��



// === �I�u�W�F�N�g ===

// �v���C���[
struct Player
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
	bool fixed;
	float balloonIndex;
};
// �G
struct Enemy
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
	bool fixed;
	float balloonIndex;
};
// ���D
struct Balloon
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
};

// �ؔ�
struct WoodBox
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
};

// UI
struct UI
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 rotation;
	DirectX::SimpleMath::Vector3 scale;
};




// === �J���� ===

// �Œ�J����
struct FixedCamera
{
	DirectX::SimpleMath::Vector3 direction;
	DirectX::SimpleMath::Vector3 rotation;
};
// �ǐՃJ����
struct FollowCamera
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

using json = nlohmann::json;

inline DirectX::SimpleMath::Vector3 ParseVector3(const nlohmann::json& j)
{
	return {
		j.at(0).get<float>(),
		j.at(1).get<float>(),
		j.at(2).get<float>()
	};
}

inline void from_json(const nlohmann::json& j, Player& p)
{
	auto player = j.at("Player");

	p.position = ParseVector3(player.at("position"));
	p.rotation = ParseVector3(player.at("rotation"));
	p.scale = ParseVector3(player.at("scale"));
	p.fixed = player.at("fixed").get<bool>();
	p.balloonIndex = player.at("balloonIndex").get<float>();
}

inline void from_json(const nlohmann::json& j, Enemy& e)
{
	auto enemy = j.at("Enemy");

	e.position = ParseVector3(enemy.at("position"));
	e.rotation = ParseVector3(enemy.at("rotation"));
	e.scale = ParseVector3(enemy.at("scale"));
	e.fixed = enemy.at("fixed").get<bool>();
	e.balloonIndex = enemy.at("balloonIndex").get<float>();
}

inline void from_json(const nlohmann::json& j, Balloon& b)
{
	b.position = ParseVector3(j.at("position"));
	b.rotation = ParseVector3(j.at("rotation"));
	b.scale = ParseVector3(j.at("scale"));
}

inline void from_json(const nlohmann::json& j, WoodBox& w)
{
	w.position = ParseVector3(j.at("position"));
	w.rotation = ParseVector3(j.at("rotation"));
	w.scale = ParseVector3(j.at("scale"));
}

inline void from_json(const nlohmann::json& j, UI& u)
{
	u.position = ParseVector3(j.at("position"));
	u.rotation = ParseVector3(j.at("rotation"));
	u.scale = ParseVector3(j.at("scale"));
}