#pragma once
#include "Interface/IObject.h"
#include "Game/Particle/Particle.h"
#include "Game/Parameters/ParameterBuffers.h"

class Particle;
class Parameters;

class ParticleEmitter 
{
private:

	enum class Shape
	{
		CONE,
		SPHERE,
	};


public:

	// ��Ԃ�ݒ肷��
	void SetIsActive(const bool& isActive) { m_isActive = isActive; }
	// ��Ԃ��擾����
	bool GetIsActive() const { return m_isActive; }

	// �C���v�b�g�f�[�^���擾����
	std::vector<DirectX::VertexPositionColorTexture> GetInputDatas() const { return m_inputDatas; }
	// �s�N�Z���V�F�[�_���擾����
	ID3D11PixelShader* GetPixelShader() const { return m_pixelShader; }
	// �e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetTexture() { return m_texture; }

	// ���[���h�s����擾����
	DirectX::SimpleMath::Matrix GetWorldMatrix() const { return m_worldMatrix; }
	// ���[���h�s���ݒ肷��
	void SetWorldMatrix(const DirectX::SimpleMath::Matrix& world) { m_worldMatrix = world; }

	// �p�����[�^�f�[�^��ݒ�
	void SetParticleParameters(const ParticleParameters& parameters) { m_particleParameters = parameters; }
	// �^�[�Q�b�g�I�u�W�F�N�g��ݒ肷��
	void SetTargetObject(IObject* target) { m_target = target; }


public:

	// �R���X�g���N�^
	ParticleEmitter(const ParticleParameters& parametersData);
	// �f�X�g���N�^
	~ParticleEmitter() = default;

	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Emit();

	void Play();

	void Stop();


private:

	// �A�N�e�B�u���
	bool m_isActive;

	// �^�[�Q�b�g�I�u�W�F�N�g
	IObject* m_target;

	// �p�[�e�B�N�����q
	std::vector<std::unique_ptr<Particle>> m_particles;

	std::vector<Particle*> m_activeParticles;
	// �C���v�b�g�f�[�^
	std::vector<DirectX::VertexPositionColorTexture> m_inputDatas;

	// �e�N�X�`��
	ID3D11ShaderResourceView* m_texture;
	// �s�N�Z���V�F�[�_�[
	ID3D11PixelShader* m_pixelShader;

	// �p�[�e�B�N���p�����[�^
	ParticleParameters m_particleParameters;

	Shape m_shape;

	float m_elapsedTime;
	float m_duration;

	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
};