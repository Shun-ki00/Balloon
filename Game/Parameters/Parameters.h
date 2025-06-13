#pragma once
#include <variant>
#include <SimpleMath.h>
#include <string>
#include "Game/Parameters/ParameterKeys.h"

class Parameters
{
public:

	// バリアント
	using ParameterValue = std::variant<float, int,bool , std::string , DirectX::SimpleMath::Vector3 , DirectX::SimpleMath::Vector4>;
	using json = nlohmann::json;

	// パラメータを取得 int
	int GetParameter(const ParametersID& id , const ParameterKeysI& key) const;
	// パラメータを取得 float
	float GetParameter(const ParametersID& id , const ParameterKeysF& key) const;
	// パラメータを取得 bool
	bool GetParameter(const ParametersID& id, const ParameterKeysB& key) const;
	// パラメータを取得 string
	std::string GetParameter(const ParametersID& id, const ParameterKeysS& key) const;
	// パラメータを取得 Vector3
	DirectX::SimpleMath::Vector3 GetParameter(const ParametersID& id, const ParameterKeysV3& key) const;
	// パラメータを取得 Vector3
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
	

	// JSONデータをロード
	void LoadFromJson(const std::string& filepath);

	// デバッグウィンドウ
	void ShowImGuiEditor();
private:

	// ファイルを開く
	std::string OpenFile() const;
	// データを保存
	std::string SaveFile() const;
	// JSONデータを保存
	void SaveToJson(const std::string& filepath);

private:
	//	コンストラクタ
	Parameters();
	//	デストラクタ
	~Parameters() = default;
public:
	Parameters(const Parameters&) = delete;             // コピー禁止
	Parameters& operator=(const Parameters&) = delete;  // コピー代入禁止
	Parameters(const Parameters&&) = delete;            // ムーブ禁止
	Parameters& operator=(const Parameters&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static Parameters* GetInstance()
	{
		static Parameters instance;
		return &instance;
	}

private:

	std::unordered_map<std::string, std::unordered_map<std::string, ParameterValue> > m_parameters;
};