#pragma once

//// ���͂𔭐�������r�w�C�r�A�i��ɏ�������j
//struct FloatForceBehaviorParams
//{
//	bool isActive{};                 // �r�w�C�r�A���L����
//	DirectX::XMFLOAT3 direction{};   // �͂�����������i�ʏ�͏�����j
//	float power{};                   // ������͂̋���
//};
//
//
//// �m�b�N�o�b�N���̔����𐧌䂷��r�w�C�r�A
//struct KnockbackBehaviorParams
//{
//	bool isActive{};     // �r�w�C�r�A���L����
//	int count{};         // �m�b�N�o�b�N�񐔂܂��͑Ώې�
//	float radius{};      // �m�b�N�o�b�N�̗L���͈�
//	float force{};       // �m�b�N�o�b�N�̋���
//};
//
//
//// �����Ԃ��i�����j�𐧌䂷��r�w�C�r�A
//struct PushBackBehaviorParams
//{
//	bool isActive{};     // �r�w�C�r�A���L����
//	float stageMin{};    // ���ʂ̍ŏ������i�J�n�_�j
//	float stageMax{};    // ���ʂ̍ő勗���i�I���_�j
//	float strength{};    // �����Ԃ��̋���
//};
//
//
//// �^�[�Q�b�g��ǐՂ���r�w�C�r�A
//struct SeekBehaviorParams
//{
//	bool isActive{};             // �r�w�C�r�A���L����
//	float predictionMultiplier{}; // �^�[�Q�b�g�̖����ʒu���ǂꂾ���\�����邩�i�b�j
//	float speed{};               // �ړ����x
//	float forceStrength{};       // ������ǐ՗͂̋���
//};
//
//
//// ���ɂ��O�͂̃r�w�C�r�A
//struct WindBehaviorParams
//{
//	bool isActive{};        // �r�w�C�r�A���L����
//	float minStrength{};    // ���̍ŏ����x
//	float maxStrength{};    // ���̍ő勭�x
//	float minDuration{};    // ���������ŒZ����
//	float maxDuration{};    // ���������Œ�����
//	float idleTime{};       // ���̕��܂ł̑ҋ@����
//	float currentDuration{};// ���݂̕��̎c��p������
//};
//
//
//// �����_���ɓ������ӂ�ӂ�ړ��r�w�C�r�A
//struct WanderBehaviorParams
//{
//	bool isActive{};         // �r�w�C�r�A���L����
//	float jitter{};          // �����_���ϓ��̋����i�����ω��j
//	float radius{};          // �~���ړ��̔��a
//	float distance{};        // �i�s�����ւ̋����i���S�_����̋����j
//	float speed{};           // �ړ����x
//	float forceStrength{};   // ������͂̋���
//};
//
//
//// �^�[�Q�b�g���痣��铦���r�w�C�r�A
//struct FleeBehaviorParams
//{
//	bool isActive{};         // �r�w�C�r�A���L����
//	float detectionRadius{}; // �G�����m����͈�
//	float speed{};           // �ړ����x
//	float forceStrength{};   // �����铦���͂̋���
//};
//
//
//// ���ׂẴX�e�A�����O�r�w�C�r�A���܂Ƃ߂��\����
//struct SteeringBehaviorParams
//{
//	FloatForceBehaviorParams floatForce;       // ���̓r�w�C�r�A
//	KnockbackBehaviorParams knockback;         // �m�b�N�o�b�N�r�w�C�r�A
//	PushBackBehaviorParams pushBack;           // �v�b�V���o�b�N�r�w�C�r�A
//	SeekBehaviorParams seek;             // �ǐՃr�w�C�r�A
//	WindBehaviorParams wind;             // ���r�w�C�r�A
//	WanderBehaviorParams wander;         // �ӂ�ӂ�ړ��r�w�C�r�A
//	FleeBehaviorParams flee;             // �����r�w�C�r�A
//};


// �v���C���[


// �G










// �p�����[�^�̎��
enum class ParametersID
{
	// �G�t�F�N�g
	EFFECT,
	// �X�e�A�����O�r�w�C�r�A
	STEERING_BEHAVIOR, 
	// �v���C���[
	PLAYER,
	// �G
	ENEMY,

	PARTICLE,

	BALLOON_EXPLOSION,

};


enum class ParameterKeysF
{
	// �v���C���[
	PlayerBrakingRate,
	PlayerMass,
	PlayerMaxForce,
	PlayerMaxSpeed,
	PlayerMaxTurnRate,
	PlayerRadius,
	PlayerScale,
	// �G

	// ���D

	// UI

	// ���̋��� 
	WindMinStrength,
	WindMaxStrength,
	WindMinDuration,
	WindMaxDuration,
	WindIdleTime,

	// �m�b�N�o�b�N
	KnockbackCount,
	KnockbackFoce,
	KnockbackRadius,

	// �p�[�e�B�N��
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
	// �v���C���[
	Player,
	// �G
	Number
	// ���D

	// UI
};

enum class ParameterKeysB
{
	// �p�[�e�B�N��
	IsLooping,
	IsGravityEnabled,
};

enum class ParameterKeysV3
{
	// �v���C���[
	Player,
	// �G

	// ���D

	// UI


	// �p�[�e�B�N��
	EmitPositionMin,
	EmitPositionMax,
	EmitDirectionMin,
	EmitDirectionMax,
	GravityAcceleration,
};

enum class ParameterKeysV4
{
	// �p�[�e�B�N��
	StartColor,
	EndColor,
};

enum class ParameterKeysS
{
	Texture,
	Shader,
};
