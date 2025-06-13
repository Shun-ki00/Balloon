// ============================================
// 
// �t�@�C����: ModelResources.cpp
// �T�v: ���f���̃��\�[�X���Ǘ�����N���X�i�V���O���g���j
// 
// ����� : �����x��
// 
// ============================================

#include "pch.h"
#include "Framework/Resources/ModelResources.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include <Framework/Microsoft/ReadData.h>
#include "Framework/Resources/ResourceKeys.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ModelResources::ModelResources()
	:
	m_models{}
{

}

/// <summary>
/// ���f���̃��\�[�X�����[�h����
/// </summary>
/// <param name="data">Json�f�[�^</param>
void ModelResources::LoadResource(const nlohmann::json& data)
{
	// �f�o�C�X
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	// �G�t�F�N�g�t�@�N�g���𐶐�����
	std::unique_ptr<DirectX::EffectFactory> effectFactory = std::make_unique<DirectX::EffectFactory>(device);

	// ���f���̊e�f�B���N�g�����擾����
	const std::wstring directory       = Resources::GetDirectoryFromJSON(data,"ModelDirectory");
	const std::wstring playerDirectory = Resources::GetDirectoryFromJSON(data,"PlayerModelDirectory");
	const std::wstring EnemyDirectory  = Resources::GetDirectoryFromJSON(data,"EnemyModelDirectory");
	// �f�B���N�g����ݒ肷��
	effectFactory->SetDirectory(directory.c_str());

	// ���f�������[�h����
	if (data.contains("Models") && data["Models"].is_object()) {
		const auto& models = data["Models"];

		for (const auto& [key, value] : models.items()) 
		{
			// �p�X�\�z
			std::wstring path = directory + L"/" + Resources::ConvertToWString(value);

			// ���f���̃��[�h
			m_models[key] = DirectX::Model::CreateFromCMO(device, path.c_str(), *effectFactory);
		}
	}

	// �v���C���[���f���̃f�B���N�g����ݒ肷��
	effectFactory->SetDirectory(playerDirectory.c_str());

	// �v���C���[���f�������[�h����
	if (data.contains("PlayerModels") && data["PlayerModels"].is_object()) {
		const auto& models = data["PlayerModels"];

		for (const auto& [key, value] : models.items())
		{
			// �p�X�\�z
			std::wstring path = playerDirectory + L"/" + Resources::ConvertToWString(value);

			// ���f���̃��[�h
			m_models[key] = DirectX::Model::CreateFromCMO(device, path.c_str(), *effectFactory);
		}
	}

	// �G���f���̃f�B���N�g����ݒ肷��
	effectFactory->SetDirectory(EnemyDirectory.c_str());

	// �G���f�������[�h����
	if (data.contains("EnemyModel") && data["EnemyModel"].is_object()) {
		const auto& models = data["EnemyModel"];

		for (const auto& [key, value] : models.items())
		{
			// �p�X�\�z
			std::wstring path = EnemyDirectory + L"/" + Resources::ConvertToWString(value);

			// ���f���̃��[�h
			m_models[key] = DirectX::Model::CreateFromCMO(device, path.c_str(), *effectFactory);
		}
	}
}

/// <summary>
/// ���f�����擾����
/// </summary>
/// <param name="id">�e�N�X�`��ID</param>
/// <returns>���\�[�X</returns>
DirectX::Model* ModelResources::GetModel(ModelKeyID id)
{
	// �L�[��string�^�ɕύX
	std::string key = std::string(magic_enum::enum_name(id));

	// ����
	auto it = m_models.find(key);
	return (it != m_models.end()) ? it->second.get() : nullptr;
}