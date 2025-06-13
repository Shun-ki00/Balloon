// ============================================
// 
// �t�@�C����: ShaderResources.h
// �T�v: ShaderResources.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Framework/Resources/ResourceKeys.h"

class ShaderResources
{
public:
	//	UI�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> UI_INPUT_LAYOUT;
	//	�C�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> SEA_INPUT_LAYOUT;
public:
	// UI �C���v�b�g���C�A�E�g���擾����
	ID3D11InputLayout* GetUIinputLayout() { return m_UIinputLayout.Get(); }
	// �C �C���v�b�g���C�A�E�g���擾
	ID3D11InputLayout* GetSeaInputLayout() { return m_SeaInputLayout.Get(); }
	// �����x�[�X�����_�����O �C���v�b�g���C�A�E�g���擾
	ID3D11InputLayout* GetPBRLitInputLayout() { return m_PBRLitInputLayout.Get(); }
	// �p�[�e�B�N�� �C���v�b�g���C�A�E�g���擾
	ID3D11InputLayout* GetParticleInputLayout() { return m_particleInputLayout.Get(); }

	// ���_�V�F�[�_�[���擾����
	ID3D11VertexShader* GetVertexShader(VS_ID id);
	// �n���V�F�[�_�[���擾����
	ID3D11HullShader* GetHullShader(HS_ID id);
	// �h���C���V�F�[�_�[���擾����
	ID3D11DomainShader* GetDomainShader(DS_ID id);
	// �W�I���g���V�F�[�_�[���擾����
	ID3D11GeometryShader* GetGeometryShader(GS_ID id);
	// �s�N�Z���V�F�[�_�[���擾����
	ID3D11PixelShader* GetPixelShader(PS_ID id);

public:
	ShaderResources(const ShaderResources&) = delete;             // �R�s�[�֎~
	ShaderResources& operator=(const ShaderResources&) = delete;  // �R�s�[����֎~
	ShaderResources(const ShaderResources&&) = delete;            // ���[�u�֎~
	ShaderResources& operator=(const ShaderResources&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static ShaderResources* GetInstance()
	{
		static ShaderResources instance;
		return &instance;
	}
	// ���\�[�X�����[�h����
	void LoadResource(const nlohmann::json& data);

private:
	// �R���X�g���N�^
	ShaderResources();

private:
	// ���̓��C�A�E�g UI
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_UIinputLayout;
	// ���̓��C�A�E�g Sea
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_SeaInputLayout;
	// ���̓��C�A�E�g PBRLit
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_PBRLitInputLayout;
	// ���̓��C�A�E�g Particle
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_particleInputLayout;

	// ���_�V�F�[�_�[
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11VertexShader>> m_vertexShaders;
	// �n���V�F�[�_�[
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11HullShader>> m_hullShaders;
	// �h���C���V�F�[�_�[
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11DomainShader>> m_domainShaders;
	// �W�I���g���V�F�[�_�[
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11GeometryShader>> m_geometryShaders;
	// �s�N�Z���V�F�[�_�[
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11PixelShader>> m_pixelShaders;
};