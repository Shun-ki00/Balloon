#include "pch.h"
#include "Framework/Utilities/JsonUtilities.h"
#include <fstream>

/// <summary>
/// JSON�t�@�C����ǂݍ���
/// </summary>
/// <param name="path">�t�@�C���p�X</param>
/// <returns>JSON�f�[�^</returns>
json JsonUtilities::LoadJsonFile(const std::string& path)
{
	// �t�@�C�����J��
	std::ifstream file(path);

	// JSON�Ƃ��ēǂݍ���
	json j;
	file >> j;

	return j;
}


/// <summary>
/// JSON�t�@�C���֕ۑ�
/// </summary>
/// <param name="path">�t�@�C���p�X</param>
/// <param name="data">JSON�f�[�^</param>
void JsonUtilities::SaveJsonFile(const std::string& path, const json& data)
{
	// �t�@�C�����J��
	std::ofstream file(path);
	// ���`���ď�������
	file << data.dump(4);
}


/// <summary>
/// �o�C�i���t�@�C����ǂݍ���
/// </summary>
/// <param name="path">�t�@�C���p�X</param>
/// <returns>JSON�f�[�^</returns>
json JsonUtilities::LoadBinaryJsonFile(const std::string& path)
{
	// �o�C�i�����[�h�ŊJ��
	std::ifstream file(path, std::ios::binary);
	// �ǂݍ���
	std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});
	// MessagePack�`������jSON�ɕϊ����Č��ʂ�Ԃ�
	return json::from_msgpack(buffer);
}


/// <summary>
/// JSON���o�C�i���Ƃ��ĕۑ�
/// </summary>
/// <param name="path">�t�@�C���p�X</param>
/// <param name="data">JSON�f�[�^</param>
void JsonUtilities::SaveBinaryJsonFIle(const std::string& path, const json& data)
{
	// JSON��MessagePack�`���ɕϊ�
	std::vector<uint8_t> buffer = json::to_msgpack(data);
	// �o�C�i�����[�h�ŊJ��
	std::ofstream file(path, std::ios::binary);
	// ��������
	file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
}