#pragma once
#include "Game/Object/Object.h"
#include "Interface/ILeaf.h"
#include "Game/Buffers/ConstantBuffer.h"


class Transform;
class IRenderableObject;
class CommonResources;


class AmbientLight : public Object , ILeaf
{
public:

	// �萔�o�b�t�@���擾����
	ID3D11Buffer* GetBuffer() const { return m_constantBuffer->GetBuffer(); }

	// �I�u�W�F�N�g�̃A�N�e�B�u�ݒ�
	void SetIsActive(const bool& isActive) { m_isActive = isActive; }
	// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾
	bool GetIsActive() const { return m_isActive; }

	// �I�u�W�F�N�g�ԍ����擾����
	int GetObjectNumber() const  override { return 0; }

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

private:
	//	�R���X�g���N�^
	AmbientLight();
	//	�f�X�g���N�^
	~AmbientLight() override = default;
public:
	AmbientLight(const AmbientLight&) = delete;             // �R�s�[�֎~
	AmbientLight& operator=(const AmbientLight&) = delete;  // �R�s�[����֎~
	AmbientLight(const AmbientLight&&) = delete;            // ���[�u�֎~
	AmbientLight& operator=(const AmbientLight&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static AmbientLight* GetInstance()
	{
		static AmbientLight instance;
		return &instance;
	}

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

	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �R���e�L�X�g
	ID3D11DeviceContext1* m_context;

	// �A�N�e�B�u���
	bool m_isActive;
	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectID;
	// �e�I�u�W�F�N�g
	IObject* m_parent;

	// Transform
	std::unique_ptr<Transform> m_transform;

	AmbientLightParameters m_ambientLightData;
	// �萔�o�b�t�@
	std::unique_ptr<ConstantBuffer<AmbientLightParameters>> m_constantBuffer;


	// �v���C���[�̑��x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ����
	DirectX::SimpleMath::Vector3 m_heading;
	// ����
	DirectX::SimpleMath::Vector3 m_side;
	// �v���C���[�̉����x
	DirectX::SimpleMath::Vector3 m_acceralation;
};