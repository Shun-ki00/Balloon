// ============================================
// 
// �t�@�C����: SkyBox.h
// �T�v: SkyBox.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once

class SkyBox
{
public:
	// �R���X�g���N�^
	SkyBox();
	// �f�X�g���N�^
	~SkyBox() = default;

	// ����������
	void Initialize();
	// �X�V����
	void Update(DirectX::SimpleMath::Matrix view , DirectX::SimpleMath::Matrix projection);
	// �`�揈��
	void Render(ID3D11DeviceContext1* context , DirectX::CommonStates* states);

	// �e�N�X�`����ύX
	void SetDayProgress(float progress) { m_dayProgress = progress; }

private:

	// �X�J�C�{�b�N�X���f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_skyboxModel;

	// ���_�V�F�[�_�[
	ID3D11VertexShader*   m_vertexShader;
	// �s�N�Z���V�F�[�_�[
	ID3D11PixelShader*    m_pixelShader;

	// �L���[�u�}�b�v
	ID3D11ShaderResourceView* m_cubemap;
	// �L���[�u�}�b�v�@�[��
	ID3D11ShaderResourceView* m_eveningCubeMap;

	// �萔�o�b�t�@�p�̃o�b�t�@�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	// ��]�p
	float m_angle;
	// ����̐i�s�x
	float m_dayProgress;

};