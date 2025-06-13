#pragma once
#include "Interface/IComposite.h"
#include "Game/Object/Object.h"
#include "Interface/ICollision.h"

class Transform;
class PlayerRenderableObject;
class CollisionVisitor;

class ISteeringBehavior;
class KnockbackBehavior;
class PushBackBehavior;
class FloatBehavior;
class FloatForceBehavior;
class SeekBehavior;

class Enemy : public Object , public ICollision ,public IComposite
{
public:
	// �I�u�W�F�N�g�̃A�N�e�B�u�ݒ�
	void SetIsActive(const bool& isActive) { m_isActive = isActive; }
	// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾
	bool GetIsActive() const { return m_isActive; }

	// �I�u�W�F�N�g�ԍ����擾����
	int GetObjectNumber() const  override { return m_objectNumber; }

	std::vector<IObject*> GetBalloonObject() { return m_balloonObject; }

	// �G��HP���擾����
	float GetHp() const { return m_hp; }

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
	Enemy(IObject* root, IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale,
		Message::MessageID messageID);
	// �f�X�g���N�^
	~Enemy() override;

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

	// �I�u�W�F�N�g���A�^�b�`����
	void Attach(std::unique_ptr<IObject> object) override;

	// �I�u�W�F�N�g���폜����
	void Detach(std::unique_ptr<IObject> object) override;

	// �Փ˔������������
	void PrepareCollision(ICollisionVisitor* collision) override;

	// �Փ˔��肷��
	void DetectCollision(ICollisionVisitor* collision, IObject* object) override;

private:
	CollisionVisitor* m_collisionVisitor;

	// �A�N�e�B�u���
	bool m_isActive;
	// �I�u�W�F�N�g�ԍ�
	int m_objectNumber;
	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectID;
	// �e�I�u�W�F�N�g
	IObject* m_parent;

	// �q�I�u�W�F�N�g
	std::vector<std::unique_ptr<IObject>> m_childs;

	// ���D�I�u�W�F�N�g
	std::vector<IObject*> m_balloonObject;
	// ���b�Z�[�WID
	Message::MessageID m_messageID;
	// Transform
	std::unique_ptr<Transform> m_transform;
	// �����蔻��
	DirectX::BoundingSphere m_boundingSphere;

	// �X�e�A�����O�r�w�C�r�A
	ISteeringBehavior* m_steeringBehavior;
	// �m�b�N�o�b�N
	std::unique_ptr<KnockbackBehavior> m_knockbackBehavior;
	// �h���
	std::unique_ptr<FloatBehavior> m_floatBehavior;

	std::unique_ptr<FloatForceBehavior> m_floatForceBehavior;

	std::unique_ptr<PushBackBehavior> m_pushBackBehavior;

	std::unique_ptr<SeekBehavior> m_seekBehavior;

	// �v���C���[�̑��x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ����
	DirectX::SimpleMath::Vector3 m_heading;
	// ����
	DirectX::SimpleMath::Vector3 m_side;
	// �v���C���[�̉����x
	DirectX::SimpleMath::Vector3 m_acceralation;

	float m_balloonIndex;

	// Hp
	float m_hp;

};