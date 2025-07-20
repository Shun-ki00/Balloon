// ============================================
// 
// �t�@�C����: Enemy.h
// �T�v: Enemy.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IComposite.h"
#include "Game/Object/Object.h"
#include "Interface/ICollision.h"
#include "Game/Status/HpController.h"
#include "Game/Status/BalloonScaleController.h"
#include "Game/Parameters/ParameterBuffers.h"

class Transform;
class PlayerRenderableObject;
class CollisionVisitor;

class EnemyIdleState;
class EnemyRunState;
class EnemyAttackState;
class EnemyWanderState;
class EnemyChaseState;

class BalloonScaleController;
class HpController;

class ActionSelection;
class SteeringBehavior;

class Enemy : public Object , public ICollision ,public IComposite
{
public:
	// �I�u�W�F�N�g�̃A�N�e�B�u�ݒ�
	void SetIsActive(const bool& isActive) { m_isActive = isActive; }
	// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾
	bool GetIsActive() const { return m_isActive; }

	// HP���擾����
	float GetHp() const { return m_hpController->GetHp(); }
	// ���D�̑傫�����擾����
	float GetBalloonScale() const { return m_balloonScaleController->GetBalloonScale(); }

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
	std::vector<IObject*> GetChilds() const override;


	// �Œ�ݒ�
	void SetIsFixed(const bool& isFixed) { m_isFixed = isFixed; }

	// ���x���擾����
	DirectX::SimpleMath::Vector3& GetVelocity() override { return m_velocity; }
	// ���x��ݒ肷��
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) override { m_velocity = velocity; }
	// �����x���擾����
	DirectX::SimpleMath::Vector3& GetAcceralation() override { return m_acceralation; }
	// �����x��ݒ肷��
	void SetAcceralation(const DirectX::SimpleMath::Vector3& accelaration) override { m_acceralation = accelaration; }

	// �R���X�g���N�^
	Enemy(IObject* root, IObject* parent,const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale, const float& balloonIndex,
		const FloatBehaviorParams& floatBehavior ,const KnockbackBehaviorParams& knockbackBehavior ,const SeekBehaviorParams& seekBehavior);
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

	// �I�u�W�F�N�g��ǉ�����
	void AttachObject();
	// �X�e�[�g���쐬����
	void CreateState();
	// �X�e�A�����O�r�w�C�r�A���쐬����
	void CreateSteeringBehavior();

	// ���D�폜����
	void BalloonLost(const int& balloonObjectNumber, const int& playerObjectNumber);

private:

	// �r�W�^�[
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
	

	// Transform
	std::unique_ptr<Transform> m_transform;
	// �����蔻��
	std::unique_ptr<DirectX::BoundingSphere> m_boundingSphere;

	// �A�N�V�����Z���N�^�[
	std::unique_ptr<ActionSelection> m_actionSelection;

	// === �X�e�A�����O�r�w�C�r�A ===

	std::unique_ptr<SteeringBehavior> m_steeringBehavior;

	FloatBehaviorParams m_floatBehaviorParams;
	KnockbackBehaviorParams m_knockbackBehaviorParams;
	SeekBehaviorParams m_seekBehaviorParams;

	// === �X�e�[�g ===

	// �A�C�h���X�e�[�g
	std::unique_ptr<EnemyIdleState> m_enemyIdleState;
	// �����X�e�[�g
	std::unique_ptr<EnemyRunState> m_enemyRunState;
	// �A�^�b�N�X�e�[�g
	std::unique_ptr<EnemyAttackState> m_enemyAttackState;
	// �p�j�X�e�[�g
	std::unique_ptr<EnemyWanderState> m_enemyWanderState;
	// �ǂ�������X�e�[�g
	std::unique_ptr<EnemyChaseState> m_enemyChaseState;


	// �v���C���[�̑��x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ����
	DirectX::SimpleMath::Vector3 m_heading;
	// ����
	DirectX::SimpleMath::Vector3 m_side;
	// �v���C���[�̉����x
	DirectX::SimpleMath::Vector3 m_acceralation;

	// ���D�̐�
	float m_balloonIndex;

	bool m_isFixed;

	// ���D�̑傫�����R���g���[��
	std::unique_ptr<BalloonScaleController> m_balloonScaleController;
	// HP���R���g���[��
	std::unique_ptr<HpController> m_hpController;

};