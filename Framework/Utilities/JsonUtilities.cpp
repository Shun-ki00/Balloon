#include "pch.h"
#include "Framework/Utilities/JsonUtilities.h"
#include <fstream>

/// <summary>
/// JSONファイルを読み込む
/// </summary>
/// <param name="path">ファイルパス</param>
/// <returns>JSONデータ</returns>
json JsonUtilities::LoadJsonFile(const std::string& path)
{
	// ファイルを開く
	std::ifstream file(path);

	// JSONとして読み込む
	json j;
	file >> j;

	return j;
}


/// <summary>
/// JSONファイルへ保存
/// </summary>
/// <param name="path">ファイルパス</param>
/// <param name="data">JSONデータ</param>
void JsonUtilities::SaveJsonFile(const std::string& path, const json& data)
{
	// ファイルを開く
	std::ofstream file(path);
	// 整形して書き込む
	file << data.dump(4);
}


/// <summary>
/// バイナリファイルを読み込む
/// </summary>
/// <param name="path">ファイルパス</param>
/// <returns>JSONデータ</returns>
json JsonUtilities::LoadBinaryJsonFile(const std::string& path)
{
	// バイナリモードで開く
	std::ifstream file(path, std::ios::binary);
	// 読み込み
	std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});
	// MessagePack形式からjSONに変換して結果を返す
	return json::from_msgpack(buffer);
}


/// <summary>
/// JSONをバイナリとして保存
/// </summary>
/// <param name="path">ファイルパス</param>
/// <param name="data">JSONデータ</param>
void JsonUtilities::SaveBinaryJsonFIle(const std::string& path, const json& data)
{
	// JSONをMessagePack形式に変換
	std::vector<uint8_t> buffer = json::to_msgpack(data);
	// バイナリモードで開く
	std::ofstream file(path, std::ios::binary);
	// 書き込む
	file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
}