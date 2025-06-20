#pragma once


class GameConfig
{
	using json = nlohmann::json;

public:

	// Jsonファイルをロードする
	void LoadJsonFile();

	// データの取得する
	template <typename T>
	T GetParameters(const std::string& key) const
	{
		json j = m_datas[key];

		T parameters = j.get<T>;

		// パラメータを返す
		return parameters;
	}

	// データを設定する
	template<typename T>
	void SetParameters(const std::string& key, const T& parameters)
	{
		// JSONに変換
		json j = parameters;

		// データを設定
		m_datas[key] = j;
	}

	json GetParameters(const std::string& key)
	{
		return m_datas[key];
	}


private:
	//	コンストラクタ
	GameConfig();
	// デストラクタ
	~GameConfig() = default;
public:
	GameConfig(const GameConfig&) = delete;             // コピー禁止
	GameConfig& operator=(const GameConfig&) = delete;  // コピー代入禁止
	GameConfig(const GameConfig&&) = delete;            // ムーブ禁止
	GameConfig& operator=(const GameConfig&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static GameConfig* GetInstance()
	{
		static GameConfig instance;
		return &instance;
	}

private:

	// データ格納マップ
	std::unordered_map<std::string, json> m_datas;

};