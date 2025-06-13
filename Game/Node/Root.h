#pragma once
#include "Interface/IObject.h"
#include "Game/Node/NodeBase.h"
#include "Interface/IComposite.h"

class Transform;

class Root : public NodeBase, public IComposite
{
public:

	// �I�u�W�F�N�g�̃A�N�e�B�u�ݒ�
	void SetIsActive(const bool& isActive) override { m_isActive = isActive; }
	// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾
	bool GetIsActive() const override { return m_isActive; }

	// �I�u�W�F�N�gID���擾����
	IObject::ObjectID GetObjectID() const override { return m_objectID; }
	// Transform���擾����
	Transform* GetTransform() const override { return m_transform.get(); }

	// �e�I�u�W�F�N�g���擾����
	IObject* GetParent() const override { return nullptr; }

	// �m�[�h�ԍ����擾����
	int GetObjectNumber() const override { return NodeBase::GetNodeCount(); }

	// ����̃m�[�h�̐���ݒ�
	void SetNodeNumber() { m_nodeNumber = NodeBase::GetNodeCount(); }
	// �m�[�h�ԍ������Z�b�g
	void ResetNodeNumber() { NodeBase::ResetNodeCount(); }

	// �A�^�b�`�̋���
	void Begin();
	// �A�^�b�`�̏I��
	void End();

	// �I�u�W�F�N�g�̍폜
	void Reset();


private:
	// �R���X�g���N�^
	Root(IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale
	);

	//	�f�X�g���N�^
	~Root() = default;
public:
	Root(const Root&) = delete;             // �R�s�[�֎~
	Root& operator=(const Root&) = delete;  // �R�s�[����֎~
	Root(const Root&&) = delete;            // ���[�u�֎~
	Root& operator=(const Root&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static Root* GetInstance()
	{
		static Root instance(
			nullptr,IObject::ObjectID::NODE_BASE,
			DirectX::SimpleMath::Vector3::Zero,
			DirectX::SimpleMath::Quaternion::Identity,
			DirectX::SimpleMath::Vector3::One
		);
		return &instance;
	}

public:

	// ����������
	void Initialize() override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// �㏈�����s��
	void Finalize() override;

	// �I�u�W�F�N�g���A�^�b�`����
	void Attach(std::unique_ptr<IObject> node) override;
	// �I�u�W�F�N�g���폜����
	void Detach(std::unique_ptr<IObject> node) override;

	// ���b�Z�[�W���擾����
	void OnMessegeAccepted(Message::MessageData messageData) override;
	// �L�[����������ꂽ��ʒm����
	void OnKeyPressed(KeyType type , const DirectX::Keyboard::Keys& key) override;

private:

	// ���
	bool m_isActive;
	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectID;
	// Transform
	std::unique_ptr<Transform> m_transform;

	// �m�[�h�̐�
	int m_nodeNumber;

	// �A�^�b�`�̋���
	bool m_isAttach;

};