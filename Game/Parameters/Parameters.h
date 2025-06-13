#pragma once
#include <variant>
#include <SimpleMath.h>
#include <string>
#include "Game/Parameters/ParameterKeys.h"

class Parameters
{
public:

	// �o���A���g
	using ParameterValue = std::variant<float, int,bool , std::string , DirectX::SimpleMath::Vector3 , DirectX::SimpleMath::Vector4>;
	using json = nlohmann::json;

	// �p�����[�^���擾 int
	int GetParameter(const ParametersID& id , const ParameterKeysI& key) const;
	// �p�����[�^���擾 float
	float GetParameter(const ParametersID& id , const ParameterKeysF& key) const;
	// �p�����[�^���擾 bool
	bool GetParameter(const ParametersID& id, const ParameterKeysB& key) const;
	// �p�����[�^���擾 string
	std::string GetParameter(const ParametersID& id, const ParameterKeysS& key) const;
	// �p�����[�^���擾 Vector3
	DirectX::SimpleMath::Vector3 GetParameter(const ParametersID& id, const ParameterKeysV3& key) const;
	// �p�����[�^���擾 Vector3
	DirectX::SimpleMath::Vector4 GetParameter(const ParametersID& id, const ParameterKeysV4& key) const;


	template<typename T>
	T GetParameter(const std::string& category, const std::string& key) const
	{
		auto catIt = m_parameters.find(category);
		if (catIt != m_parameters.end()) {
			auto paramIt = catIt->second.find(key);
			if (paramIt != catIt->second.end() && std::holds_alternative<T>(paramIt->second)) {
				return std::get<T>(paramIt->second);
			}
		}
		throw std::runtime_error("Parameter not found or type mismatch: " + category + "::" + key);
	}
	

	// JSON�f�[�^�����[�h
	void LoadFromJson(const std::string& filepath);

	// �f�o�b�O�E�B���h�E
	void ShowImGuiEditor();
private:

	// �t�@�C�����J��
	std::string OpenFile() const;
	// �f�[�^��ۑ�
	std::string SaveFile() const;
	// JSON�f�[�^��ۑ�
	void SaveToJson(const std::string& filepath);

private:
	//	�R���X�g���N�^
	Parameters();
	//	�f�X�g���N�^
	~Parameters() = default;
public:
	Parameters(const Parameters&) = delete;             // �R�s�[�֎~
	Parameters& operator=(const Parameters&) = delete;  // �R�s�[����֎~
	Parameters(const Parameters&&) = delete;            // ���[�u�֎~
	Parameters& operator=(const Parameters&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static Parameters* GetInstance()
	{
		static Parameters instance;
		return &instance;
	}

private:

	std::unordered_map<std::string, std::unordered_map<std::string, ParameterValue> > m_parameters;
};