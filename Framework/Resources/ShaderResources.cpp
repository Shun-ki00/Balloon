// ============================================
// 
// �t�@�C����: ShaderResources.cpp
// �T�v: �V�F�[�_�[�̃��\�[�X���Ǘ�����N���X�i�V���O���g���j
// 
// ����� : �����x��
// 
// ============================================

#include "pch.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/Resources.h"
#include <Framework/Microsoft/ReadData.h>
#include <VertexTypes.h>


const std::vector<D3D11_INPUT_ELEMENT_DESC> ShaderResources::UI_INPUT_LAYOUT =
{
	// �Z�}���e�B�b�N�� �C���f�b�N�X �t�H�[�}�b�g         ���̓X���b�g    �I�t�Z�b�g                                                                                                                                         �f�[�^���        �C���X�^���X�X�e�b�v��
	{ "SV_Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  0,  D3D11_INPUT_PER_VERTEX_DATA, 0 }, // position
	{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 16,  D3D11_INPUT_PER_VERTEX_DATA, 0 }, // rotate
	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, 28,  D3D11_INPUT_PER_VERTEX_DATA, 0 }, // size
	{ "TEXCOORD",    1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 36,  D3D11_INPUT_PER_VERTEX_DATA, 0 }, // rect
	{ "COLOR",       0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 52,  D3D11_INPUT_PER_VERTEX_DATA, 0 }, // color
	{ "TEXCOORD",    2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 68,  D3D11_INPUT_PER_VERTEX_DATA, 0 }, // rule
};
const std::vector<D3D11_INPUT_ELEMENT_DESC> ShaderResources::SEA_INPUT_LAYOUT =
{
	{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,                                    D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,    0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


/// <summary>
/// �R���X�g���N�^
/// </summary>
ShaderResources::ShaderResources()
	:
	m_UIinputLayout{},
	m_SeaInputLayout{},
	m_PBRLitInputLayout{},
	m_particleInputLayout{}
{
}


/// <summary>
/// �V�F�[�_�[�̃��\�[�X�����[�h����
/// </summary>
/// <param name="data">Json�f�[�^</param>
void ShaderResources::LoadResource(const nlohmann::json& data)
{
	// �f�o�C�X
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	// ���f���̊e�f�B���N�g�����擾����
	const std::wstring directory = Resources::GetDirectoryFromJSON(data, "ShaderDirectory");

	std::vector<uint8_t> blob;

	// ���_�V�F�[�_�[
	if (data["Shaders"].contains("VS")) {
		for (const auto& [key, value] : data["Shaders"]["VS"].items()) {
			std::wstring path = directory + L"/" + Resources::ConvertToWString(value);

			// �V�F�[�_�[�����[�h����
			blob = DX::ReadData(path.c_str());
			DX::ThrowIfFailed(
				device->CreateVertexShader(blob.data(), blob.size(), nullptr, 
					m_vertexShaders[key].ReleaseAndGetAddressOf())
			);
		}
	}
	// �n���V�F�[�_�[
	if (data["Shaders"].contains("HS")) {
		for (const auto& [key, value] : data["Shaders"]["HS"].items()) {
			std::wstring path = directory + L"/" + Resources::ConvertToWString(value);

			// �V�F�[�_�[�����[�h����
			blob = DX::ReadData(path.c_str());
			DX::ThrowIfFailed(
				device->CreateHullShader(blob.data(), blob.size(), nullptr,
					m_hullShaders[key].ReleaseAndGetAddressOf())
			);
		}
	}
	// �h���C���V�F�[�_�[
	if (data["Shaders"].contains("DS")) {
		for (const auto& [key, value] : data["Shaders"]["DS"].items()) {
			std::wstring path = directory + L"/" + Resources::ConvertToWString(value);

			// �V�F�[�_�[�����[�h����
			blob = DX::ReadData(path.c_str());
			DX::ThrowIfFailed(
				device->CreateDomainShader(blob.data(), blob.size(), nullptr,
					m_domainShaders[key].ReleaseAndGetAddressOf())
			);
		}
	}
	// �W�I���g���V�F�[�_�[
	if (data["Shaders"].contains("GS")) {
		for (const auto& [key, value] : data["Shaders"]["GS"].items()) {
			std::wstring path = directory + L"/" + Resources::ConvertToWString(value);

			// �V�F�[�_�[�����[�h����
			blob = DX::ReadData(path.c_str());
			DX::ThrowIfFailed(
				device->CreateGeometryShader(blob.data(), blob.size(), nullptr,
					m_geometryShaders[key].ReleaseAndGetAddressOf())
			);
		}
	}
	// �s�N�Z���V�F�[�_�[
	if (data["Shaders"].contains("PS")) {
		for (const auto& [key, value] : data["Shaders"]["PS"].items()) {
			std::wstring path = directory + L"/" + Resources::ConvertToWString(value);

			// �V�F�[�_�[�����[�h����
			blob = DX::ReadData(path.c_str());
			DX::ThrowIfFailed(
				device->CreatePixelShader(blob.data(), blob.size(), nullptr,
					m_pixelShaders[key].ReleaseAndGetAddressOf())
			);
		}
	}


	// ���̓��C�A�E�g�̍\�z�i�K�v�Ȃ��̂����j
	if (m_vertexShaders.contains("UI_VS")) {
		blob = DX::ReadData((directory + L"/UI_VS.cso").c_str());
		device->CreateInputLayout(UI_INPUT_LAYOUT.data(),
			(UINT)UI_INPUT_LAYOUT.size(),
			blob.data(), blob.size(),
			m_UIinputLayout.GetAddressOf());
	}

	if (m_vertexShaders.contains("Sea_VS")) {
		blob = DX::ReadData((directory + L"/Sea_VS.cso").c_str());
		device->CreateInputLayout(SEA_INPUT_LAYOUT.data(),
			(UINT)SEA_INPUT_LAYOUT.size(),
			blob.data(), blob.size(),
			m_SeaInputLayout.GetAddressOf());
	}

	if (m_vertexShaders.contains("PBRLit_VS")) {
		blob = DX::ReadData((directory + L"/PBRLit_VS.cso").c_str());
		device->CreateInputLayout(
			DirectX::VertexPositionNormalTangentColorTexture::InputElements,
			DirectX::VertexPositionNormalTangentColorTexture::InputElementCount,
			blob.data(), blob.size(),
			m_PBRLitInputLayout.GetAddressOf());
	}

	if (m_vertexShaders.contains("Particle_VS")) {
		blob = DX::ReadData((directory + L"/Particle_VS.cso").c_str());
		device->CreateInputLayout(
			DirectX::VertexPositionColorTexture::InputElements,
			DirectX::VertexPositionColorTexture::InputElementCount,
			blob.data(), blob.size(),
			m_particleInputLayout.GetAddressOf());
	}
}

/// <summary>
/// ���_�V�F�[�_�[���擾����
/// </summary>
/// <param name="id">���_�V�F�[�_�[ID</param>
/// <returns>���_�V�F�[�_�[</returns>
ID3D11VertexShader* ShaderResources::GetVertexShader(VS_ID id)
{
	std::string key = std::string(magic_enum::enum_name(id));
	auto it = m_vertexShaders.find(key);
	return (it != m_vertexShaders.end()) ? it->second.Get() : nullptr;
}

/// <summary>
/// �n���V�F�[�_�[���擾����
/// </summary>
/// <param name="id">�n���V�F�[�_�[ID</param>
/// <returns>�n���V�F�[�_�[</returns>
ID3D11HullShader* ShaderResources::GetHullShader(HS_ID id)
{
	std::string key = std::string(magic_enum::enum_name(id));
	auto it = m_hullShaders.find(key);
	return (it != m_hullShaders.end()) ? it->second.Get() : nullptr;
}

/// <summary>
/// �h���C���V�F�[�_�[���擾����
/// </summary>
/// <param name="id">�h���C���V�F�[�_�[ID</param>
/// <returns>�h���C���V�F�[�_�[</returns>
ID3D11DomainShader* ShaderResources::GetDomainShader(DS_ID id)
{
	std::string key = std::string(magic_enum::enum_name(id));
	auto it = m_domainShaders.find(key);
	return (it != m_domainShaders.end()) ? it->second.Get() : nullptr;
}

/// <summary>
/// �W�I���g���V�F�[�_�[���擾����
/// </summary>
/// <param name="id">�W�I���g���V�F�[�_�[ID</param>
/// <returns>�W�I���g���V�F�[�_�[</returns>
ID3D11GeometryShader* ShaderResources::GetGeometryShader(GS_ID id)
{
	std::string key = std::string(magic_enum::enum_name(id));
	auto it = m_geometryShaders.find(key);
	return (it != m_geometryShaders.end()) ? it->second.Get() : nullptr;
}

/// <summary>
/// �s�N�Z���V�F�[�_�[���擾����
/// </summary>
/// <param name="id">�s�N�Z���V�F�[�_�[ID</param>
/// <returns>�s�N�Z���V�F�[�_�[</returns>
ID3D11PixelShader* ShaderResources::GetPixelShader(PS_ID id)
{
	std::string key = std::string(magic_enum::enum_name(id));
	auto it = m_pixelShaders.find(key);
	return (it != m_pixelShaders.end()) ? it->second.Get() : nullptr;
}
