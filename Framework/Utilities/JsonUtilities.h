#pragma once

using json = nlohmann::json;

class JsonUtilities
{
public:

	// JSON�t�@�C����ǂݍ���
	static json LoadJsonFile(const std::string& path);
	// JSON�t�@�C���֕ۑ�
	static void SaveJsonFile(const std::string& path, const json& data);

	// �o�C�i���t�@�C����ǂݍ���
	static json LoadBinaryJsonFile(const std::string& path);
	// JSON���o�C�i���Ƃ��ĕۑ�
	static void SaveBinaryJsonFIle(const std::string& path, const json& data);

};