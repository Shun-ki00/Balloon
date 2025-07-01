// ============================================
// 
// �t�@�C����: ResultSceneButtons.h
// �T�v: ResultSceneButtons.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Game/UIObject/UIObject.h"
#include "Interface/IComposite.h"

class Transform;
class CommonResources;
class UIRenderableObject;

class ResultSceneButtons : public UIObject , public IComposite
{
public:

	// �I�u�W�F�N�g�̃A�N�e�B�u�ݒ�
	void SetIsActive(const bool& isActive) override { m_isActive = isActive; }
	// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾
	bool GetIsActive() const override { return m_isActive; }

	// �I�u�W�F�N�g�ԍ����擾����
	int GetObjectNumber() const  override { return m_objectNumber; }

	// �I�u�W�F�N�gID���擾����
	IObject::ObjectID GetObjectID() const override { return m_objectID; }
	// Transform���擾����
	Transform* GetTransform() const override { return m_transform.get(); }

	// �e�I�u�W�F�N�g���擾����
	IObject* GetParent() const override { return m_parent; }

	// �I�u�W�F�N�g���A�^�b�`����
	void Attach(std::unique_ptr<IObject> object) override;
	// �I�u�W�F�N�g���폜����
	void Detach(std::unique_ptr<IObject> object) override;
	// �q�I�u�W�F�N�g���擾����
	std::vector<IObject*> GetChilds() const override { return {}; }

public:

	// �R���X�g���N�^
	ResultSceneButtons(IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale);

	// �f�X�g���N�^
	~ResultSceneButtons() override = default;

	// ����������
	void Initialize() override;
	// ���b�Z�[�W���擾����
	void OnMessegeAccepted(Message::MessageData messageData) override;
	// �L�[����������ꂽ��ʒm����
	void OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key) override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// �㏈�����s��
	void Finalize() override;

private:

	// ���������� �V���O���g���E���L���\�[�X ����������

	CommonResources* m_commonResources;


	// ���������� ���ʂ̃v���p�e�B ����������

	// �A�N�e�B�u���
	bool m_isActive; 
	// �I�u�W�F�N�g�ԍ�
	int m_objectNumber;   
	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectID;   
	// �e�I�u�W�F�N�g
	IObject* m_parent;             
	// �q�I�u�W�F�N�g�i�{�^���j
	std::vector<std::unique_ptr<IObject>> m_childs;
	// Transform
	std::unique_ptr<Transform> m_transform; 


	// ���������� ���̃N���X���L ����������

	 // ���݂̃{�^��
	int m_buttonIndex;                          
};