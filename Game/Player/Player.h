// ============================================
// 
// �t�@�C����: Player.h
// �T�v: Player.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IComposite.h"
#include "Interface/ICollision.h"
#include "Game/Object/Object.h"

class Transform;
class PlayerRenderableObject;
class PlayerIdleState;
class PlayerRunState;
class PlayerAttackState;
class PlayerSitState;

class ISteeringBehavior;
class SteeringBehavior;

class BalloonScaleController;
class HpController;

class CollisionVisitor;

class Player : public Object ,public ICollision , public IComposite
{
public:
	// �I�u�W�F�N�g�̃A�N�e�B�u�ݒ�
	void SetIsActive(const bool& isActive) { m_isActive = isActive; }
	// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾
	bool GetIsActive() const { return m_isActive; }

	// �I�u�W�F�N�g�ԍ����擾����
	int GetObjectNumber() const  override { return m_objectNumber; }

	std::vector<IObject*> GetBalloonObject() { return m_balloonObject; }

	// �I�u�W�F�N�gID���擾����
	IObject::ObjectID GetObjectID() const override { return m_objectID; }
	// Transform���擾����
	Transform* GetTransform() const override { return m_transform.get(); }

	// �e�I�u�W�F�N�g���擾����
	IObject* GetParent() const override { return m_parent; }
	// �q�I�u�W�F�N�g���擾����
	std::vector<IObject*> GetChilds() const;
	
	// ���x���擾����
	DirectX::SimpleMath::Vector3& GetVelocity() override { return m_velocity; }
	// ���x��ݒ肷��
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) override { m_velocity = velocity; }
	// �����x���擾����
	DirectX::SimpleMath::Vector3& GetAcceralation() override { return m_acceralation; }
	// �����x��ݒ肷��
	void SetAcceralation(const DirectX::SimpleMath::Vector3& accelaration) override { m_acceralation = accelaration; }

	// �v���C���[�̌Œ�ݒ�
	void SetIsFixed(const bool& isFixed) { m_isFixed = isFixed; }

	// �R���X�g���N�^
	Player(IObject* root, IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale,
		Message::MessageID messageID);
	// �f�X�g���N�^
	~Player() override;

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

	// �Փ˔���̏���
	void PrepareCollision(ICollisionVisitor* collision) override;
	// �Փ˔��肷��t
	void DetectCollision(ICollisionVisitor* collision, IObject* bullets) override;

private:

	// �I�u�W�F�N�g��ǉ�����
	void AttachObject();

	// �X�e�[�g���쐬����
	void CreateState();

	// �X�e�A�����O�r�w�C�r�A���쐬����
	void CreateSteeringBehavior();

private:

	// === ���ʂȂ��� ===

	// �r�W�^�[
	CollisionVisitor* m_collisionVisitor;

	// �A�N�e�B�u���
	bool m_isActive;
	// �I�u�W�F�N�g�ԍ�
	int m_objectNumber;
	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectID;
	// ���b�Z�[�WID
	Message::MessageID m_messageID;
	// Transform
	std::unique_ptr<Transform> m_transform;
	// �e�I�u�W�F�N�g
	IObject* m_parent;
	// �q�I�u�W�F�N�g
	std::vector<std::unique_ptr<IObject>> m_childs;
	// �����蔻��
	std::unique_ptr<DirectX::BoundingSphere> m_boundingSphere;

	// ���D�I�u�W�F�N�g
	std::vector<IObject*> m_balloonObject;

	// === �������� ===

	// �v���C���[�̑��x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ����
	DirectX::SimpleMath::Vector3 m_heading;
	// ����
	DirectX::SimpleMath::Vector3 m_side;
	// �v���C���[�̉����x
	DirectX::SimpleMath::Vector3 m_acceralation;


	// === �X�e�A�����O�r�w�C�r�A ===

	std::unique_ptr<SteeringBehavior> m_steeringBehavior;
	
	// === �X�e�[�g ===

	// �A�C�h���X�e�[�g
	std::unique_ptr<PlayerIdleState> m_playerIdleState;
	// �����X�e�[�g
	std::unique_ptr<PlayerRunState> m_playerRunState;
	// �A�^�b�N�X�e�[�g
	std::unique_ptr<PlayerAttackState> m_playerAttackState;
	// ����X�e�[�g
	std::unique_ptr<PlayerSitState> m_playerSitState;


	// �Œ�ݒ�
	bool m_isFixed;

	// ���D�̑傫�����R���g���[��
	std::unique_ptr<BalloonScaleController> m_balloonScaleController;
	// HP���R���g���[��
	std::unique_ptr<HpController> m_hpController;

};