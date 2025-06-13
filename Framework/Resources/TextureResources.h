// ============================================
// 
// �t�@�C����: TextureResources.h
// �T�v: TextureResources.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================

#pragma once
#include "Framework/Resources/ResourceKeys.h"


class TextureResources
{
public:
	// �e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetTexture(TextureKeyID id);

	// �e�N�X�`���T�C�Y���擾����
	void GetTextureSize(const TextureKeyID& id, float& width, float& height);


public:
	TextureResources(const TextureResources&) = delete;             // �R�s�[�֎~
	TextureResources& operator=(const TextureResources&) = delete;  // �R�s�[����֎~
	TextureResources(const TextureResources&&) = delete;            // ���[�u�֎~
	TextureResources& operator=(const TextureResources&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static TextureResources* GetInstance()
	{
		static TextureResources instance;
		return &instance;
	}
	// ���\�[�X�����[�h����
	void LoadResource(const nlohmann::json& data);

private:
	// �R���X�g���N�^
	TextureResources();
	// �f�X�g���N�^
	~TextureResources() = default;

private:

	// �f�o�C�X
	ID3D11Device1* m_device;

	// �e�N�X�`�����X�g
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textures;
};