#pragma once

class CommonResources;
class Resources;

class Sea
{
private:
	//	�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4    TessellationFactor;
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
	void CreateConstantBuffer();

	// �u�����h�X�e�[�g�̍쐬
	void CreateBlendState(ID3D11Device1* device);
	// �[�x�X�e���V���X�e�[�g�̍쐬
	void CreateDepthStencilState(ID3D11Device1* device);
	// ���X�^���C�U�[�X�e�[�g�̍쐬
	void CreateRasterizerState(ID3D11Device1* device);

private:

	// �^�C��
	float m_time;
	// �e�b�Z���[�V����
	float m_index;

	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �R�����X�e�[�g
	DirectX::CommonStates* m_commonStates;

	//	�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
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

	ID3D11ShaderResourceView* m_NormalTexture;
	ID3D11ShaderResourceView* m_CubeTexture;

	// �u�����h�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;
	// �[�x�X�e���V���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	// ���X�^���C�U�[�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;


	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;
	// �g�p�����[�^
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_waveConstantBuffer;



	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;

};