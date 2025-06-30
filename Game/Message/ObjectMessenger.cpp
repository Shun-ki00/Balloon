// ============================================
// 
// �t�@�C����: ObjectMessenger.cpp
// �T�v: �I�u�W�F�N�g�̃��b�Z���W���[�i�V���O���g���j
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/Message/ObjectMessenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ObjectMessenger::ObjectMessenger()
	:
	m_objects{},
	m_isAttach{}
{
	m_isAttach = false;
}


/// <summary>
/// �I�u�W�F�N�g��o�^����
/// </summary>
/// <param name="objectId">�I�u�W�F�N�gID</param>
/// <param name="objectNumber">�I�u�W�F�N�g�ԍ�</param>
/// <param name="object">�I�u�W�F�N�g</param>
void ObjectMessenger::Register(const IObject::ObjectID& objectId, const int& objectNumber, IObject* object)
{
	// �A�^�b�`��������ĂȂ���Γo�^���s��Ȃ�
	if (!m_isAttach) return;

	// �I�u�W�F�N�gID�����Ƃɔԍ��ƃI�u�W�F�N�g��o�^����
	m_objects[objectId].emplace(objectNumber, object);
}



/// <summary>
/// �I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗐M����
/// </summary>
/// <param name="objectId">�I�u�W�F�N�gID</param>
/// <param name="objectNumber">�I�u�W�F�N�g�ԍ�</param>
/// <param name="messageData">���b�Z�[�W�f�[�^</param>
void ObjectMessenger::Dispatch(const IObject::ObjectID& objectId, const int& objectNumber, const Message::MessageData& messageData)
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
/// <summary>
/// �I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗐M����
/// </summary>
/// <param name="objectId">�I�u�W�F�N�gID</param>
/// <param name="objectNumber">�I�u�W�F�N�g�ԍ�</param>
/// <param name="messageID">���b�Z�[�WID</param>
void ObjectMessenger::Dispatch(const IObject::ObjectID& objectId, const int& objectNumber, const Message::MessageID& messageID)
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
/// <summary>
/// �I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗐M����
/// </summary>
/// <param name="objectId">�I�u�W�F�N�gID</param>
/// <param name="messageData">���b�Z�[�W�f�[�^</param>
void ObjectMessenger::Dispatch(const IObject::ObjectID& objectId, const Message::MessageData& messageData)
{
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g����������
	auto typeIt = m_objects.find(objectId);

	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g�����������ꍇ
	if (typeIt != m_objects.end())
	{
		for (const auto it : typeIt->second)
		{
			if (typeIt == m_objects.end()) break;
			// ���M����I�u�W�F�N�g�̃��b�Z�[�W�n���h�����Ăяo��
			it.second->OnMessegeAccepted(messageData);
		}
	}
}


/// <summary>
/// �I�u�W�F�N�g���擾����
/// </summary>
/// <param name="objectId">�I�u�W�F�N�gID</param>
/// <param name="objectNumber">�I�u�W�F�N�g�ԍ�</param>
/// <returns>�I�u�W�F�N�g</returns>
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

/// <summary>
/// �I�u�W�F�N�g���擾����
/// </summary>
/// <param name="objectId">�I�u�W�F�N�gID</param>
/// <returns>�I�u�W�F�N�g</returns>
std::vector<IObject*> ObjectMessenger::FindObject(const IObject::ObjectID& objectId)
{
	std::vector<IObject*> objects;

	// �I�u�W�F�N�gID�ɑΉ�����}�b�v�����݂��邩�m�F
	auto typeIt = m_objects.find(objectId);
	if (typeIt == m_objects.end()) return objects;

	// �Ώۂ̃I�u�W�F�N�g��z��ɋl�߂ĕԂ�
	for (const auto& [objectNumber, object] : typeIt->second)
	{
		if (object->GetObjectID() == objectId)
			objects.push_back(object);
	}

	return objects;
}

/// <summary>
/// �A�^�b�`������
/// </summary>
void ObjectMessenger::Begin()
{
	// �A�^�b�`������
	m_isAttach = true;
	// ���X�g�폜
	this->Clear();

}

/// <summary>
/// �A�^�b�`�I��
/// </summary>
void ObjectMessenger::End()
{
	// �A�^�b�`�I��
	m_isAttach = false;
}


/// <summary>
/// �o�^���Ă�����̂��폜
/// </summary>
void ObjectMessenger::Clear()
{
	m_objects.clear();
}