#pragma once
#include "Interface/IObject.h"
#include "Interface/IComposite.h"

class Transform;

class NodeBase : public IObject
{
public:

	// �I�u�W�F�N�g�̃A�N�e�B�u�ݒ�
	void SetIsActive(const bool& isActive) override { m_isActive = isActive; }
	// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾
	bool GetIsActive() const override { return m_isActive; }

	// �I�u�W�F�N�gID���擾����
	IObject::ObjectID GetObjectID() const override { return m_objectID; }
	// Transform���擾����
	Transform* GetTransform() const override { return nullptr; }


public:

	// �R���X�g���N�^
	NodeBase();
	// �f�X�g���N�^
	~NodeBase();
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// �㏈�����s��
	void Finalize() override;

	// �I�u�W�F�N�g���A�^�b�`����
	void Attach(std::unique_ptr<IObject> node);
	// �I�u�W�F�N�g���폜����
	void Detach(IObject* node);

	// �V�[���P�̂Ńm�[�h�̍폜
	void ResetSceneNode(int nodeCount);

public:
	// �m�[�h�J�E���g�̃J�E���g�A�b�v��m�[�h�J�E���g���擾����(1����J�n����)
	static int GetNodeCountAfterCountUp() 
	{
		return s_nodeCount + 1000;
	}
	// �m�[�h�J�E���g���擾����
	static int GetNodeCount() { return s_nodeCount; }
	// �m�[�h�J�E���g�����Z�b�g����
	static void ResetNodeCount() { s_nodeCount = 1000; }

private:
	// �m�[�h�J�E���g
	static int s_nodeCount;

	// �m�[�h�z��
	std::vector<std::unique_ptr<IObject>> m_nodes;

	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectID;
	// ���
	bool m_isActive;
};