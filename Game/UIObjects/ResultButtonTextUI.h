#pragma once
#include "Game/UIObject/UIObject.h"

class Transform;
class CommonResources;
class UIRenderableObject;

class ResultButtonTextUI : public UIObject
{
public:

	enum class TextID
	{
		STAGE_SELECT = 0,
		REPLAY,
		NEXT_STAGE,
	};


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

	// �`��I�u�W�F�N�g���擾����
	UIRenderableObject* GetUIRenderableObject() const { return m_renderableObject.get(); }

	// �{�^���A�N�e�B�u�ݒ�
	void SetButtonActive(const bool& isButton);

public:

	// �R���X�g���N�^
	ResultButtonTextUI(IObject* root, IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale,
		ResultButtonTextUI::TextID textId);

	// �f�X�g���N�^
	~ResultButtonTextUI() override = default;

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

	// �X�e�[�W�Z���N�g�e�N�X�`���̉��̃T�C�Y
	static const int STAGE_SELECT_WIDTH;
	static const int REPLAY_WIDTH;
	static const int NEXT_STAGE_WIDTH;
	
	static const int TEXTURE_HEIGHT;

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

	// �e�L�X�gID
	TextID m_textId;

	// Transform
	std::unique_ptr<Transform> m_transform;
	// �`��I�u�W�F�N�g
	std::unique_ptr<UIRenderableObject> m_renderableObject;

	bool m_isButton;

};