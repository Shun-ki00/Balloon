#pragma once
#include "Game/Parameters/ParameterKeys.h"
#include "Game/Particle/Particle.h"

class Particle;
class Parameters;

class ParticleEmitter
{
public:

	bool GetIsActive() const { return m_isEmitting; }

	// �C���v�b�g�f�[�^���擾����
	std::vector<DirectX::VertexPositionColorTexture> GetInputDatas() const { return m_inputDatas; }
	// �s�N�Z���V�F�[�_���擾����
	ID3D11PixelShader* GetPixelShader() const { return m_pixelShader; }

	// �e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetTexture() { return m_texture; }


public:

	// �R���X�g���N�^
	ParticleEmitter();
	// �f�X�g���N�^
	~ParticleEmitter() = default;

	// ����������
	void Initialize(ParametersID id);

	// �X�V����
	void Update(const float& elapsedTime);

	void Emit();

	void Play();

	void Stop();


private:
	Parameters* m_parameters;

	// �p�[�e�B�N�����q
	std::vector<std::unique_ptr<Particle>> m_particles;
	std::vector<Particle*> m_activeParticles;
	// �C���v�b�g�f�[�^
	std::vector<DirectX::VertexPositionColorTexture> m_inputDatas;
	// �e�N�X�`��
	ID3D11ShaderResourceView* m_texture;
	// �s�N�Z���V�F�[�_�[
	ID3D11PixelShader* m_pixelShader;

	float m_emitTimer;               // �G�~�b�g�^�C�}�[
	float m_emissionInterval;         // 1��������܂ł̊Ԋu ( = 1.0f / m_emissionRate )
	float m_emissionDurationTimer;    // �G�~�b�V�����p�����ԊǗ�

	bool m_isEmitting = true;                // ���������ǂ���

	// ��{�ݒ�
	float m_emissionRate;              // 1�b������o�����q��
	float m_emissionDuration;          // �G�~�b�g����p������
	float m_particleLifetime;          // 1���q�̎���

	// �����͈�
	DirectX::SimpleMath::Vector3 m_emitPositionMin;  // �����͈� �ŏ����W
	DirectX::SimpleMath::Vector3 m_emitPositionMax;  // �����͈� �ő���W

	// ��������
	DirectX::SimpleMath::Vector3 m_emitDirectionMin; // ���˕��� �ŏ��x�N�g��
	DirectX::SimpleMath::Vector3 m_emitDirectionMax; // ���˕��� �ő�x�N�g��

	// ���x
	float m_emitSpeedMin;             // �ŏ����ˑ��x
	float m_emitSpeedMax;             // �ő唭�ˑ��x

	// �T�C�Y
	float m_startSizeMin;             // �J�n�T�C�Y�ŏ�
	float m_startSizeMax;             // �J�n�T�C�Y�ő�
	float m_endSizeMin;               // �I���T�C�Y�ŏ�
	float m_endSizeMax;               // �I���T�C�Y�ő�

	// ��]
	float m_startRotationMin;         // �J�n��]�ŏ��p�i�x�j
	float m_startRotationMax;         // �J�n��]�ő�p�i�x�j
	float m_rotationSpeedMin;         // ��]���x�ŏ��i�x/�b�j
	float m_rotationSpeedMax;         // ��]���x�ő�i�x/�b�j

	// �F
	DirectX::SimpleMath::Vector4 m_startColor;        // �J�n�F
	DirectX::SimpleMath::Vector4 m_endColor;           // �I���F

	// �d�́E�����x
	bool m_isGravityEnabled;          // �d�͗L���t���O
	DirectX::SimpleMath::Vector3 m_gravityAcceleration; // �d�͉����x�x�N�g��

	// ���̑����o
	float m_randomnessFactor;         // �����_���΂���̋���
	bool m_isLooping;                 // ���[�v���邩�ǂ���

	
};