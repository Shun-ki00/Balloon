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
	// �A�^�b�`���͑��M�֎~
	if (m_isAttach) return;

	// �ΏۃI�u�W�F�N�g���擾���Ēʒm
	if (IObject* target = this->FindObject(objectId, objectNumber))
	{
		target->OnMessegeAccepted(messageData);
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
	// �A�^�b�`���͑��M�֎~
	if (m_isAttach) return;

	this->Dispatch(objectId, objectNumber, Message::MessageData{ messageID });
}
/// <summary>
/// �I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗐M����
/// </summary>
/// <param name="objectId">�I�u�W�F�N�gID</param>
/// <param name="messageData">���b�Z�[�W�f�[�^</param>
void ObjectMessenger::Dispatch(const IObject::ObjectID& objectId, const Message::MessageData& messageData)
{
	// �A�^�b�`���͑��M�֎~
	if (m_isAttach) return;

	// �ΏۃI�u�W�F�N�g���擾
	const auto objects = this->FindObject(objectId);

	// �e�I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗐M
	for (const auto& object : objects)
	{
		if (object) object->OnMessegeAccepted(messageData);
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
	// �w�肳�ꂽ�I�u�W�F�N�gID�ɑΉ�����}�b�v��T��
	const auto idIt = m_objects.find(objectId);
	// �Y������I�u�W�F�N�gID�����݂��Ȃ���� nullptr ��Ԃ�
	if (idIt == m_objects.end()) return nullptr;
	// �I�u�W�F�N�g�ԍ����g���āA�Y������I�u�W�F�N�g����������
	const auto objectIt = idIt->second.find(objectNumber);
	// ������΃|�C���^��Ԃ��A������Ȃ���� nullptr ��Ԃ�
	return (objectIt != idIt->second.end()) ? objectIt->second : nullptr;
}

/// <summary>
/// �I�u�W�F�N�g���擾����
/// </summary>
/// <param name="objectId">�I�u�W�F�N�gID</param>
/// <returns>�I�u�W�F�N�g</returns>
std::vector<IObject*> ObjectMessenger::FindObject(const IObject::ObjectID& objectId)
{
	// �������ʂ��i�[���邽�߂̔z���p��
	std::vector<IObject*> results = {};

	// �w�肳�ꂽ�I�u�W�F�N�gID�ɑΉ�����}�b�v��T��
	const auto idIt = m_objects.find(objectId);
	// �O���[�v�����݂��Ȃ��ꍇ�͋�̃��X�g��Ԃ�
	if (idIt == m_objects.end()) return results;

	// �Ώۂ�ID�ɑΉ����邷�ׂẴI�u�W�F�N�g�𑖍�
	for (const auto& [_, object] : idIt->second)
	{
		// nullptr �`�F�b�N
		if (object) results.push_back(object); // �L���ȃI�u�W�F�N�g�̂݃��X�g�ɒǉ�
	}

	// �������ʂ�Ԃ�
	return results;
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