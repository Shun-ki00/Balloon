// ============================================
// 
// �t�@�C����: TextureResources.cpp
// �T�v: �e�N�X�`���̃��\�[�X���Ǘ�����N���X�i�V���O���g���j
// 
// ����� : �����x��
// 
// ============================================

#include "pch.h"
#include "Framework/Resources/TextureResources.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>


/// <summary>
/// �R���X�g���N�^
/// </summary>
TextureResources::TextureResources()
	:
	m_textures{}
{
	// �f�o�C�X�̃C���X�^���X���擾����
	m_device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
}


/// <summary>
/// ���[�h����
/// </summary>
/// <param name="data">Josn�f�[�^</param>
void TextureResources::LoadResource(const nlohmann::json& data)
{
	// �e�N�X�`���̃f�B���N�g�����擾
	const std::wstring directory          = Resources::GetDirectoryFromJSON(data, "TextureDirectory");
	const std::wstring normalMapDirectory = Resources::GetDirectoryFromJSON(data, "NormalMapTextureDirectory");
	const std::wstring ddsDirectory       = Resources::GetDirectoryFromJSON(data, "DDSTextureDirectory");

	// �e�N�X�`��
	if (data.contains("Textures") && data["Textures"].is_object()) 
	{
		for (const auto& [key, value] : data["Textures"].items()) 
		{
			// �����ȃL�[�܂��͔񕶎���l�̓X�L�b�v
			if (!value.is_string() || key.empty()) continue;

			// �p�X�\�z
			std::wstring path = directory + L"/" + Resources::ConvertToWString(value);

			// �e�N�X�`�������[�h����
			HRESULT hr = DirectX::CreateWICTextureFromFile(
				m_device,
				path.c_str(),
				nullptr,
				m_textures[key].ReleaseAndGetAddressOf()
			);

			// ���[�h���s���̓f�o�b�O���̂ݒ�~
			assert(SUCCEEDED(hr)); 
		}
	}

	// �m�[�}���}�b�v
	if (data.contains("Textures_NormalMaps") && data["Textures_NormalMaps"].is_object()) 
	{
		for (const auto& [key, value] : data["Textures_NormalMaps"].items()) 
		{

			// �����ȃL�[�܂��͔񕶎���l�̓X�L�b�v
			if (!value.is_string() || key.empty()) continue;

			// �p�X�\�z
			std::wstring path = normalMapDirectory + L"/" + Resources::ConvertToWString(value);

			// �m�[�}���}�b�v�����[�h����
			HRESULT hr = DirectX::CreateWICTextureFromFile(
				m_device,
				path.c_str(),
				nullptr,
				m_textures[key].ReleaseAndGetAddressOf()
			);

			// ���[�h���s���̓f�o�b�O���̂ݒ�~
			assert(SUCCEEDED(hr)); 
		}
	}

	// DDS�e�N�X�`��
	if (data.contains("Textures_DDS") && data["Textures_DDS"].is_object()) {
		for (const auto& [key, value] : data["Textures_DDS"].items()) {

			// �����ȃL�[�܂��͔񕶎���l�̓X�L�b�v
			if (!value.is_string() || key.empty()) continue;

			// �p�X�\�z
			std::wstring path = ddsDirectory + L"/" + Resources::ConvertToWString(value);

			// dds�e�N�X�`�������[�h����
			HRESULT hr = DirectX::CreateDDSTextureFromFile(
				m_device,
				path.c_str(),
				nullptr,
				m_textures[key].ReleaseAndGetAddressOf()
			);

			// ���[�h���s���̓f�o�b�O���̂ݒ�~
			assert(SUCCEEDED(hr)); 
		}
	}
}

/// <summary>
/// �e�N�X�`�����擾����
/// </summary>
/// <param name="id">�e�N�X�`��ID</param>
/// <returns>���\�[�X</returns>
ID3D11ShaderResourceView* TextureResources::GetTexture(TextureKeyID id)
{
	// �L�[��string�^�ɕύX
	std::string key = std::string(magic_enum::enum_name(id));

	// ����
	auto it = m_textures.find(key);
	return (it != m_textures.end()) ? it->second.Get() : nullptr;
}


/// <summary>
/// �e�N�X�`���̃T�C�Y���擾����
/// </summary>
/// <param name="id">�e�N�X�`��ID</param>
/// <param name="width">�e�N�X�`���T�C�Y�@��</param>
/// <param name="height">�e�N�X�`���T�C�Y�@�c</param>
void TextureResources::GetTextureSize(const TextureKeyID& id, float& width, float& height)
{
	// �摜�̃T�C�Y���擾����
	// �ꎞ�I�ȕϐ��̐錾
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	D3D11_TEXTURE2D_DESC desc;

	// �e�N�X�`���̏����擾����================================
	// �e�N�X�`����ID3D11Resource�Ƃ��Č���
	this->GetTexture(id)->GetResource(resource.GetAddressOf());
	// ID3D11Resource��ID3D11Texture2D�Ƃ��Č���
	resource.As(&texture2D);
	// �e�N�X�`�������擾����
	texture2D->GetDesc(&desc);

	// �e�N�X�`���T�C�Y���擾���Afloat�^�ɕϊ�����
	width  = static_cast<float>(desc.Width);
	height = static_cast<float>(desc.Height);
}