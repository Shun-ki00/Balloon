#pragma once
#include "Game/Buffers/ConstantBuffer.h"

class CommonResources;
class Resources;

class Sea
{
private:

	// �ϊ��p�萔�o�b�t�@
	struct TransformConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4    cameraPosition;
		DirectX::SimpleMath::Vector4    TessellationFactor;
	};

	// �C���X�^���X�f�[�^
	struct InstanceData
	{
		DirectX::SimpleMath::Vector4 offset;
	};


	// �C�̃m�C�Y�p�̒萔�o�b�t�@
	struct SeaNoiseConstBuffer
	{
		float flowVelocity;    // ������
		float swingSpeed;      // ���E�̐U��
		float fnUVPath1;       // �m�C�Y�̉e�� (x��)
		float fnUVPath2;       // �m�C�Y�̉e�� (y��)

		float fnUVPower;       // UV�X�P�[��
		float fnOctaves;       // �m�C�Y�̃I�N�^�[�u��
		float fnPersistence;   // �m�C�Y�����x
		float padding;         // �p�f�B���O
	};

	// �Q���X�g�i�g�̒萔�o�b�t�@
	struct GerstnerWaveConstBuffer
	{
		// Wave1
		float active1, direction1X, direction1Z, amplitude1;
		float waveLength1, speed1, qRatio1, pad1;

		// Wave2
		float active2, direction2X, direction2Z, amplitude2;
		float waveLength2, speed2, qRatio2, pad2;

		// Wave3
		float active3, direction3X, direction3Z, amplitude3;
		float waveLength3, speed3, qRatio3, pad3;
	};

public:
	// �R���X�g���N�^
	Sea();
	// �f�X�g���N�^
	~Sea() = default;

public:

	// ����������
	void Initialize();
	// �`�揈��
	void Render();

private:

	// �萔�o�b�t�@�̍쐬
	void CreateConstBuffer();
	// ���_�̐���
	void CreateVertexBuffer();
	// �C���X�^���X�f�[�^�̍쐬
	void CreateInstanceData();

private:

	// �^�C��
	float m_time;
	
	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �R�����X�e�[�g
	DirectX::CommonStates* m_commonStates;
	// �R���e�L�X�g
	ID3D11DeviceContext1* m_context;
	// �f�o�C�X
	ID3D11Device1* m_device;
	// ���\�[�X
	Resources* m_resources;

	// ���̓��C�A�E�g
	ID3D11InputLayout* m_inputLayout;
	// ���_�V�F�[�_�[
	ID3D11VertexShader* m_vertexShader;
	// �n���V�F�[�_�[
	ID3D11HullShader* m_hullShader;
	// �h���C���V�F�[�_�[
	ID3D11DomainShader* m_domainShader;
	// �s�N�Z���V�F�[�_�[
	ID3D11PixelShader* m_pixelShader;

	// �e�N�X�`��
	ID3D11ShaderResourceView* m_texture;

	// Transform�萔�o�b�t�@
	std::unique_ptr<ConstantBuffer<TransformConstBuffer>> m_transformBuffer;
	// �C�m�C�Y�萔�o�b�t�@
	std::unique_ptr<ConstantBuffer<SeaNoiseConstBuffer>> m_seaNoiseBuffer;
	// �g�萔�o�b�t�@
	std::unique_ptr<ConstantBuffer<GerstnerWaveConstBuffer>> m_gerstnerWaveBuffer;

	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	// �C���X�^���X�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_instanceStructuredBuffer;
	// �C���X�^���X�̃V�F�[�_�[���\�[�X�r���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_instanceSRV;
};