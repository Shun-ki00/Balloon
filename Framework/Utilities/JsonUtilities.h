#pragma once

using json = nlohmann::json;

class JsonUtilities
{
public:

	// JSONファイルを読み込む
	static json LoadJsonFile(const std::string& path);
	// JSONファイルへ保存
	static void SaveJsonFile(const std::string& path, const json& data);

	// バイナリファイルを読み込む
	static json LoadBinaryJsonFile(const std::string& path);
	// JSONをバイナリとして保存
	static void SaveBinaryJsonFIle(const std::string& path, const json& data);

};