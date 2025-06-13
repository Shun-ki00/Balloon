#pragma once
#include "Interface/ICamera.h"
#include "Interface/IObject.h"

class Transform;
class BlendingCamera;
class CommonResources;
class Root;

class CameraSystem : public IObject
{
public:
	// �I�u�W�F�N�g�̃A�N�e�B�u�ݒ�
	void SetIsActive(const bool& isActive) { m_isActive = isActive; }
	// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾
	bool GetIsActive() const { return m_isActive; }

	// �I�u�W�F�N�g�ԍ����擾����
	int GetObjectNumber() const { return m_objectNumber; }

	// �I�u�W�F�N�gID���擾����
	IObject::ObjectID GetObjectID() const { return m_objectID; }
	// Transform���擾����
	Transform* GetTransform() const { return m_transform.get(); }

	// �e�I�u�W�F�N�g���擾����
	IObject* GetParent() const { return m_parent; }

	// �J������ǉ�����
	void Attach(std::unique_ptr<ICamera> camera);
	// �J������ύX����
	void ChangeCamera(int index, float time);

public:

	// �R���X�g���N�^
	CameraSystem(Root* root, IObject* parent);
	// �f�X�g���N�^
	~CameraSystem() override = default;

public:

	// ����������
	void Initialize() override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// �㏈�����s��
	void Finalize() override;

	// ���b�Z�[�W���擾����
	void OnMessegeAccepted(Message::MessageData messageData) override;
	// �L�[����������ꂽ��ʒm����
	void OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key) override;

private:

	// ���L���\�[�X
	CommonResources* m_commonResources;

	// �J�����ԍ�
	int m_cameraIndex;

	// ���
	bool m_isActive;
	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectID;
	// �I�u�W�F�N�g�ԍ�
	int m_objectNumber;
	// �e�I�u�W�F�N�g
	IObject* m_parent;
	// Transform
	std::unique_ptr<Transform> m_transform;

	// ���݂̃J����
	ICamera* m_currentCamera;

	// �J�ڒ��̃J����
	std::unique_ptr<BlendingCamera> m_blendingCamera;

	// �J����
	std::unordered_map<int, std::unique_ptr<ICamera>> m_virtualCameras;
};