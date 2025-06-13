#pragma once
#include "Interface/IObject.h"


class InputManager;
class IObject;



class KeyboardMessenger
{
public:
	// �ώ@�҂��A�^�b�`����
	void Attach(const KeyType& type, const DirectX::Keyboard::Keys& keys, IObject* observer);
	// �ώ@�҂��f�^�b�`����
	void Detach(const KeyType& type, const DirectX::Keyboard::Keys& keys, IObject* object);

	void Dispatch();

	// �A�^�b�`�J�n
	void Begin();
	//�@�A�^�b�`�I��
	void End();

	void RemoveObserver();


private:
	//	�R���X�g���N�^
	KeyboardMessenger();
	//	�f�X�g���N�^
	~KeyboardMessenger() = default;
public:
	KeyboardMessenger(const KeyboardMessenger&) = delete;             // �R�s�[�֎~
	KeyboardMessenger& operator=(const KeyboardMessenger&) = delete;  // �R�s�[����֎~
	KeyboardMessenger(const KeyboardMessenger&&) = delete;            // ���[�u�֎~
	KeyboardMessenger& operator=(const KeyboardMessenger&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static KeyboardMessenger* GetInstance()
	{
		static KeyboardMessenger instance;
		return &instance;
	}

private:

	// �L�[�{�[�h�Ǘ���
	InputManager* m_inputManager;

	// �L�[�{�[�h�ώ@�҃��X�g
	std::unordered_map<KeyType,
		std::unordered_multimap<DirectX::Keyboard::Keys, IObject*>> m_observerList;

	// �A�^�b�`����
	bool m_isAttach;
};