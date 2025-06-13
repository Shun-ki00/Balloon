#pragma once
#include "Interface/IObject.h"
#include "Game/Message/Message.h"

class ObjectMessenger
{
public:

	// �I�u�W�F�N�g�������A�擾����
	IObject* FindObject(const IObject::ObjectID& objectId, const int& objectNumber);
	// �I�u�W�F�N�g��o�^����
	void Register(const IObject::ObjectID& objectId ,const int& objectNumber, IObject* object);

	// ���b�Z�[�W�𑗐M����
	void Dispatch(const IObject::ObjectID& objectId, const int& objectNumber
		, Message::MessageData messageData);
	// ���b�Z�[�W�𑗐M���� ID�̂�
	void Dispatch(const IObject::ObjectID& objectId, const int& objectNumber
		, Message::MessageID messageID);

private:
	//	�R���X�g���N�^
	ObjectMessenger();
	//	�f�X�g���N�^
	~ObjectMessenger() = default;
public:
	ObjectMessenger(const ObjectMessenger&) = delete;             // �R�s�[�֎~
	ObjectMessenger& operator=(const ObjectMessenger&) = delete;  // �R�s�[����֎~
	ObjectMessenger(const ObjectMessenger&&) = delete;            // ���[�u�֎~
	ObjectMessenger& operator=(const ObjectMessenger&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static ObjectMessenger* GetInstance()
	{
		static ObjectMessenger instance;
		return &instance;
	}

	// �A�^�b�`�J�n
	void Begin();
	// �A�^�b�`�I��
	void End();

	// ���X�g�̍폜
	void Clear();

private:
	
	// �I�u�W�F�N�gID���L�[�ɃI�u�W�F�N�g�ԍ��ƃI�u�W�F�N�g���}�b�s���O
	std::unordered_map<IObject::ObjectID, std::unordered_map<int, IObject*>> m_objects;

	// �A�^�b�`����
	bool m_isAttach;
};