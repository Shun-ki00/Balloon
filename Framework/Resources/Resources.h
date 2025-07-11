// ============================================
// 
// �t�@�C����: Resources.h
// �T�v: Resources.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================

#pragma once
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"
#include "Game/GameConfig/GameConfig.h"

class CommonResources;

class ModelResources;
class ShaderResources;
class TextureResources;

// Resources�N���X���`����
class Resources
{
public:
	// �ȈՓI�� UTF-8 �� UTF-16 �ϊ�
	static std::wstring ConvertToWString(const std::string& str) {
		return std::wstring(str.begin(), str.end()); 
	};


	static std::wstring GetDirectoryFromJSON(const nlohmann::json& data, const std::string& key) {
		if (data.contains(key) && data[key].is_string()) {
			return Resources::ConvertToWString(data[key]);
		}
		return L"";  // fallback: �󕶎�
	}

public:
	// ���f�����\�[�X���擾����
	ModelResources* GetModelResources() { return m_modelResources; }
	// �V�F�[�_�[���\�[�X���擾����
	ShaderResources* GetShaderResources() { return m_shaderResources; }
	// �e�N�X�`�����\�[�X���擾����
	TextureResources* GetTextureResources() { return m_textureResources; }

public:
	Resources(const Resources&) = delete;             // �R�s�[�֎~
	Resources& operator=(const Resources&) = delete;  // �R�s�[����֎~
	Resources(const Resources&&) = delete;            // ���[�u�֎~
	Resources& operator=(const Resources&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static Resources* GetInstance()
	{
		static Resources instance;
		return &instance;
	}
	// ���\�[�X�����[�h����
	void LoadResource();

private:
	// �R���X�g���N�^
	Resources();

	// ���f���̃��[�h
	void LoadModel() { m_modelResources->LoadResource(m_data); }
	// �V�F�[�_�[�̃��[�h
	void LoadShader()  { m_shaderResources->LoadResource(m_data); }
	// �e�N�X�`���̃��[�h
	void LoadTexture() { m_textureResources->LoadResource(m_data); }
	// �Q�[���f�[�^�����[�h
	void LoadGameData() { GameConfig::GetInstance()->LoadJsonFile(); }

private:
	// ���f�����\�[�X
	ModelResources* m_modelResources;
	// �V�F�[�_�[���\�[�X
	ShaderResources* m_shaderResources;
	// �e�N�X�`�����\�[�X
	TextureResources* m_textureResources;

	// Json�f�[�^
	nlohmann::json m_data;

	float m_time;
};