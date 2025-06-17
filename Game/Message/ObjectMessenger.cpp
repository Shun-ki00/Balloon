#include "pch.h"
#include "Game/Message/ObjectMessenger.h"

ObjectMessenger::ObjectMessenger()
{
	m_isAttach = false;
}


// �I�u�W�F�N�g��o�^����
void ObjectMessenger::Register(const IObject::ObjectID& objectId, const int& objectNumber, IObject* object)
{
	// �A�^�b�`��������ĂȂ���Γo�^���s��Ȃ�
	if (!m_isAttach) return;

	// �I�u�W�F�N�gID�����Ƃɔԍ��ƃI�u�W�F�N�g��o�^����
	m_objects[objectId].emplace(objectNumber, object);
}

// �I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗐M����
void ObjectMessenger::Dispatch(const IObject::ObjectID& objectId, const int& objectNumber
	, Message::MessageData messageData)
{
	// �A�^�b�`���̏ꍇ���b�Z�[�W�̑��M���s��Ȃ�
	if (m_isAttach) return;
	
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g����������
	auto typeIt = m_objects.find(objectId);

	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g�����������ꍇ
	if (typeIt != m_objects.end())
	{
		// ��ID�Ō���
		auto instanceIt = typeIt->second.find(objectNumber);

		// �̂����������ꍇ�̓|�C���^��Ԃ�
		if (instanceIt != typeIt->second.end())
		{
			// ���M����I�u�W�F�N�g�̃��b�Z�[�W�n���h�����Ăяo��
			instanceIt->second->OnMessegeAccepted(messageData);
		}
	}
}

// �I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗐M����
void ObjectMessenger::Dispatch(const IObject::ObjectID& objectId, const int& objectNumber
	, Message::MessageID messageID)
{
	// �A�^�b�`���̏ꍇ���b�Z�[�W�̑��M���s��Ȃ�
	if (m_isAttach) return;

	Message::MessageData messageData(messageID);

	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g����������
	auto typeIt = m_objects.find(objectId);

	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g�����������ꍇ
	if (typeIt != m_objects.end())
	{
		// ��ID�Ō���
		auto instanceIt = typeIt->second.find(objectNumber);

		// �̂����������ꍇ�̓|�C���^��Ԃ�
		if (instanceIt != typeIt->second.end())
		{
			// ���M����I�u�W�F�N�g�̃��b�Z�[�W�n���h�����Ăяo��
			instanceIt->second->OnMessegeAccepted(messageData);
		}
	}
}

void ObjectMessenger::Dispatch(const IObject::ObjectID& objectId, const Message::MessageData& messageData)
{
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g����������
	auto typeIt = m_objects.find(objectId);

	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g�����������ꍇ
	if (typeIt != m_objects.end())
	{
		for (const auto it : typeIt->second)
		{
			// ���M����I�u�W�F�N�g�̃��b�Z�[�W�n���h�����Ăяo��
			it.second->OnMessegeAccepted(messageData);
		}
	}
}


// �I�u�W�F�N�g���擾����
IObject* ObjectMessenger::FindObject(const IObject::ObjectID& objectId, const int& objectNumber)
{
	// ��ނ��Ƃ̃I�u�W�F�N�g�}�b�v������
	auto typeIt = m_objects.find(objectId);

	// ��ނ����������ꍇ
	if (typeIt != m_objects.end())
	{
		// ��ID�Ō���
		auto instanceIt = typeIt->second.find(objectNumber);

		// �̂����������ꍇ�̓|�C���^��Ԃ�
		if (instanceIt != typeIt->second.end())
		{
			return instanceIt->second;
		}
	}

	// ������Ȃ������ꍇ�� nullptr ��Ԃ�
	return nullptr;
}

void ObjectMessenger::Begin()
{
	// �A�^�b�`������
	m_isAttach = true;
	// ���X�g�폜
	this->Clear();

}

void ObjectMessenger::End()
{
	// �A�^�b�`�I��
	m_isAttach = false;
}

void ObjectMessenger::Clear()
{
	m_objects.clear();
}