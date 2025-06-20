#pragma once


class GameConfig
{
	using json = nlohmann::json;

public:

	// Json�t�@�C�������[�h����
	void LoadJsonFile();

	// �f�[�^�̎擾����
	template <typename T>
	T GetParameters(const std::string& key) const
	{
		json j = m_datas[key];

		T parameters = j.get<T>;

		// �p�����[�^��Ԃ�
		return parameters;
	}

	// �f�[�^��ݒ肷��
	template<typename T>
	void SetParameters(const std::string& key, const T& parameters)
	{
		// JSON�ɕϊ�
		json j = parameters;

		// �f�[�^��ݒ�
		m_datas[key] = j;
	}

	json GetParameters(const std::string& key)
	{
		return m_datas[key];
	}


private:
	//	�R���X�g���N�^
	GameConfig();
	// �f�X�g���N�^
	~GameConfig() = default;
public:
	GameConfig(const GameConfig&) = delete;             // �R�s�[�֎~
	GameConfig& operator=(const GameConfig&) = delete;  // �R�s�[����֎~
	GameConfig(const GameConfig&&) = delete;            // ���[�u�֎~
	GameConfig& operator=(const GameConfig&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static GameConfig* GetInstance()
	{
		static GameConfig instance;
		return &instance;
	}

private:

	// �f�[�^�i�[�}�b�v
	std::unordered_map<std::string, json> m_datas;

};