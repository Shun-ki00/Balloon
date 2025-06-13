// ============================================
// 
// �t�@�C����: LeftFoot.h
// �T�v: LeftFoot.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Game/Object/Object.h"
#include "Interface/ILeaf.h"

class Transform;
class IRenderableObject;
class CommonResources;

class LeftFoot : public Object , ILeaf
{
public:
	// �I�u�W�F�N�g�̃A�N�e�B�u�ݒ�
	void SetIsActive(const bool& isActive) { m_isActive = isActive; }
	// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾
	bool GetIsActive() const { return m_isActive; }

	// �I�u�W�F�N�g�ԍ����擾����
	int GetObjectNumber() const  override { return m_objectNumber; }

	// �I�u�W�F�N�gID���擾����
	IObject::ObjectID GetObjectID() const override { return m_objectID; }
	// Transform���擾����
	Transform* GetTransform() const override { return m_transform.get(); }

	// �e�I�u�W�F�N�g���擾����
	IObject* GetParent() const override { return m_parent; }

	// ���x���擾����
	DirectX::SimpleMath::Vector3& GetVelocity() override { return m_velocity; }
	// ���x��ݒ肷��
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) override { m_velocity = velocity; }
	// �����x���擾����
	DirectX::SimpleMath::Vector3& GetAcceralation() override { return m_acceralation; }
	// �����x��ݒ肷��
	void SetAcceralation(const DirectX::SimpleMath::Vector3& accelaration) override { m_acceralation = accelaration; }

	// �R���X�g���N�^
	LeftFoot(IObject* root, IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale,
		Message::MessageID messageID);
	// �f�X�g���N�^
	~LeftFoot() override;

	// ����������
	void Initialize();
	// ���b�Z�[�W���擾����
	void OnMessegeAccepted(Message::MessageData messageData) override;
	// �L�[����������ꂽ��ʒm����
	void OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key) override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// �㏈�����s��
	void Finalize() override;
	
private:

	// ���L���\�[�X
	CommonResources* m_commonResources;

	// �A�N�e�B�u���
	bool m_isActive;
	// �I�u�W�F�N�g�ԍ�
	int m_objectNumber;
	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectID;
	// �e�I�u�W�F�N�g
	IObject* m_parent;

	// ���b�Z�[�WID
	Message::MessageID m_messageID;
	// Transform
	std::unique_ptr<Transform> m_transform;
	// �`��I�u�W�F�N�g
	std::unique_ptr<IRenderableObject> m_renderableObject;
	// �����蔻��
	DirectX::BoundingSphere m_boundingSphere;

	// �v���C���[�̑��x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ����
	DirectX::SimpleMath::Vector3 m_heading;
	// ����
	DirectX::SimpleMath::Vector3 m_side;
	// �v���C���[�̉����x
	DirectX::SimpleMath::Vector3 m_acceralation;
};