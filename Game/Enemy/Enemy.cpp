#include "pch.h"
#include "Game/Enemy/Enemy.h"
#include "Game/Object/Object.h"
#include "Interface/IComposite.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Game/Buffers.h"
#include "Game/Factorys/EnemyFactory.h"
#include "Game/Factorys/BalloonFactory.h"
#include "Game/Balloon/Balloon.h"
#include "Game/Visitor/CollisionVisitor.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Player/Player.h"

#include "Interface/ISteeringBehavior.h"
#include "Game/SteeringBehavior/WindBehavior.h"
#include "Game/SteeringBehavior/KnockbackBehavior.h"
#include "Game/SteeringBehavior/FloatBehavior.h"
#include "Game/SteeringBehavior/FloatForceBehavior.h"
#include "Game/SteeringBehavior/PushBackBehavior.h"
#include "Game/SteeringBehavior/SeekBehavior.h"
#include "Game/SteeringBehavior/SteeringBehavior.h"

#include "Game/States/Enemy/EnemyIdleState.h"
#include "Game/States/Enemy/EnemyRunState.h"
#include "Game/States/Enemy/EnemyAttackState.h"
#include "Game/States/Enemy/EnemyWanderState.h"
#include "Game/States/Enemy/EnemyChaseState.h"

#include "Game/Status/BalloonScaleController.h"
#include "Game/Status/HpController.h"

#include "Game/Enemy/ActionSelection.h"
#include "Game/BehaviorTree/SelectorNode.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="angle"></param>
/// <param name="position"></param>
/// <param name="messageID"></param>
Enemy::Enemy(IObject* root, IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale, const float& balloonIndex)
	:
	// ���N���X
	Object(
		0.0f,
		0.0f,
		0.0f,
		0.0f
	),
	m_isActive(true),
	m_objectNumber(root->GetObjectNumber() + Object::CountUpNumber()),
	m_objectID(objectID),
	m_balloonIndex(balloonIndex),
	m_parent(parent),
	m_transform{},
	m_childs {},
	m_isFixed{}
{

	m_collisionVisitor = CollisionVisitor::GetInstance();

	// Transform���쐬
	m_transform = std::make_unique<Transform>();
	
	// �������W�ݒ�
	m_transform->SetLocalPosition(position);
	// ������]�ݒ�
	m_transform->SetLocalRotation(rotation);
	// �����X�P�[���ݒ�
	m_transform->SetLocalScale(scale);

	// �e������ꍇ�e��ݒ�
	if (parent != nullptr)
		m_transform->SetParent(parent->GetTransform());
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{

}


/// <summary>
/// ����������
/// </summary>
void Enemy::Initialize()
{
	
	// �I�u�W�F�N�g��ǉ�����
	this->AttachObject();
	// �X�e�A�����O�r�w�C�r�A���쐬����
	this->CreateSteeringBehavior();
	// �X�e�[�g���쐬����
	this->CreateState();

	// ==== �X�e�[�^�X�̍쐬�Ə��������� ====

	// HP���R���g���[��
	m_hpController = std::make_unique<HpController>();
	m_hpController->Initialize();
	// ���D�̑傫�����R���g���[��
	m_balloonScaleController = std::make_unique<BalloonScaleController>(
		m_hpController.get(),dynamic_cast<FloatForceBehavior*>( m_steeringBehavior->GetSteeringBehavior(BEHAVIOR_TYPE::FLOAT_FORCE)));
	m_balloonScaleController->Initialize();


	// ==== �A�N�V�����Z���N�^�[ ====

	m_actionSelection = std::make_unique<ActionSelection>();
	m_actionSelection->Initialize(this);


	// ==== �����蔻�� ====

	// �����蔻��̍쐬
	m_boundingSphere = std::make_unique<DirectX::BoundingSphere>();
	// ������
	m_boundingSphere->Center = DirectX::SimpleMath::Vector3::Up * 0.2f;
	m_boundingSphere->Radius = 0.3f;

	// �����蔻�����������
	m_collisionVisitor->StartPrepareCollision(this);

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Enemy::Update(const float& elapsedTime)
{
	// �v���C���[���Œ��Ԃ̏ꍇ
	if (m_isFixed)
	{
		// �p�j��Ԃɂ���
		this->ChangeState(m_enemyWanderState.get());

		// ���D�̑傫�����X�V����
		m_balloonScaleController->Update(elapsedTime);
		// HP�̍X�V����
		m_hpController->Update(elapsedTime);

		float result = m_balloonScaleController->GetBalloonScale() * 6.0f - 3.0f;
		dynamic_cast<FloatForceBehavior*>(m_steeringBehavior->GetSteeringBehavior(BEHAVIOR_TYPE::FLOAT_FORCE))->SetForceStrength(result);

		// Transform�̍X�V����
		m_transform->Update();

		// ���D�̑傫����ݒ肷��
		for (const auto& balloon : m_balloonObject)
		{
			balloon->GetParent()->OnMessegeAccepted({ Message::MessageID::BALLOON_SCALE ,0,m_balloonScaleController->GetBalloonScale(),false });
		}

		// �q�I�u�W�F�N�g�̍X�V����
		for (const auto& child : m_childs)
		{
			child->Update(elapsedTime);
		}

		return;
	}
	// �A�N�V���������肷��
	//m_actionSelection->GetRootNode()->Tick();

	// �I�u�W�F�N�g�̍X�V����
	//Object::Update(elapsedTime);

	// ==== �X�e�[�^�X�̍X�V���� ====

	// ���D�̑傫�����X�V����
	m_balloonScaleController->Update(elapsedTime);
	// HP�̍X�V����
	m_hpController->Update(elapsedTime);

	float result = m_balloonScaleController->GetBalloonScale() * 6.0f - 3.0f;
	dynamic_cast<FloatForceBehavior*>(m_steeringBehavior->GetSteeringBehavior(BEHAVIOR_TYPE::FLOAT_FORCE))->SetForceStrength(result);

	
	// ���Ǘ͂�������x���v�Z����
	DirectX::SimpleMath::Vector3 acceleration = m_steeringBehavior->Calculate(elapsedTime);
	// ���x�ɉ����x�����Z����
	m_velocity += acceleration * elapsedTime;
	// ���݂̈ʒu���X�V����
	m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);

	m_velocity = m_velocity * (1.0f - 2.0f * elapsedTime);

	// Transform�̍X�V����
	m_transform->Update();


	// ==== �q�I�u�W�F�N�g�̍X�V���� ====

	// �q�I�u�W�F�N�g�̍X�V����
	for (const auto& child : m_childs)
	{
		child->Update(elapsedTime);
	}

	// ���D�̑傫����ݒ肷��
	for (const auto& balloon : m_balloonObject)
	{
		balloon->GetParent()->OnMessegeAccepted({ Message::MessageID::BALLOON_SCALE ,0,m_balloonScaleController->GetBalloonScale(),false });
	}


	// ==== �Փ˔���̍X�V ====

	// �����蔻����s��
	auto player = dynamic_cast<Player*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER)[0]);
	for (const auto& balloon : player->GetBalloonObject())
	{
		m_collisionVisitor->DetectCollision(this, balloon);
	}
}

/// <summary>
/// �I������
/// </summary>
void Enemy::Finalize()
{

}

/// <summary>
/// �p�[�c��ǉ�����
/// </summary>
/// <param name="object"></param>
void Enemy::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// �p�[�c���폜����
/// </summary>
/// <param name="turretPart"></param>
void Enemy::Detach(std::unique_ptr<IObject> object)
{

}

/// <summary>
/// �q�I�u�W�F�N�g���擾����
/// </summary>
/// <returns>�q�I�u�W�F�N�g</returns>
std::vector<IObject*> Enemy::GetChilds() const
{
	std::vector<IObject*> result;
	result.reserve(m_childs.size());
	for (const auto& child : m_childs)
	{
		result.push_back(child.get());
	}
	return result;
}

/// <summary>
/// ���b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
void Enemy::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		// ���D�폜����
		case Message::MessageID::BALLOON_LOST:
			this->BalloonLost(messageData.dataInt, static_cast<int>(messageData.dataFloat));
			break;
			// �Փ˂������̏���
		case Message::MessageID::ON_COLLISION:
			if (Object::GetState() == m_enemyAttackState.get())
			ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER, messageData.dataFloat,
				{ Message::MessageID::BALLOON_LOST,messageData.dataInt,messageData.dataFloat,false });
			break;
			// Y���ŋt�x�N�g���ɂ���
		case Message::MessageID::INVERT_Y_VECTOR:
			m_velocity.y = m_velocity.y * -1.0f;
			break;
		case Message::MessageID::ENEMY_ON_BALLOON_SCALE:
			// HP������Ȃ�L����
			if (m_hpController->GetHp() <= 0.01f) break;
			m_balloonScaleController->On();
			break;

		case Message::MessageID::ENEMY_OFF_BALLOON_SCALE:
			m_balloonScaleController->Off();
			break;

		case Message::MessageID::ENEMY_IDLING:
			Object::ChangeState(m_enemyIdleState.get());
			break;
		case Message::MessageID::ENEMY_WANDER:
			if (Object::GetState() != m_enemyAttackState.get())
			Object::ChangeState(m_enemyWanderState.get());
			break;
		case Message::MessageID::ENEMY_CHASE:
			if (Object::GetState() != m_enemyAttackState.get())
			Object::ChangeState(m_enemyChaseState.get());
		case Message::MessageID::ENEMY_ATTACK:
			if(Object::GetState() != m_enemyAttackState.get())
			Object::ChangeState(m_enemyAttackState.get());
			break;

		case Message::MessageID::FIXED:
			m_isFixed = messageData.dataBool;
			break;
		default:
			break;
	}
}

/// <summary>
/// �L�[�{�[�h�̒ʒm���󂯎��
/// </summary>
/// <param name="type">�L�[�{�[�h�^�C�v</param>
/// <param name="key">�L�[</param>
void Enemy::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}

/// <summary>
/// �Փ˔������������
/// </summary>
/// <param name="collision">�����蔻�菈��</param>
void Enemy::PrepareCollision(ICollisionVisitor* collision)
{
	collision->PrepareCollision(this,m_boundingSphere.get());

	for (const auto& child : m_childs)
	{
		if (child->GetObjectID() == IObject::ObjectID::BALLOON)
			dynamic_cast<Balloon*>(child.get())->PrepareCollision(collision);
	}

}

/// <summary>
/// �Փ˔��肷��
/// </summary>
/// <param name="collision">�����蔻�菈��</param>
/// <param name="object">�Ώۂ̃I�u�W�F�N�g</param>
void Enemy::DetectCollision(ICollisionVisitor* collision, IObject* object)
{
	// ������s��
	collision->DetectCollision(this, object);
}

/// <summary>
/// ���D�폜����
/// </summary>
/// <param name="balloonObjectNumber">���D�̔ԍ�</param>
/// <param name="playerObjectNumber">�v���C���[�̔ԍ�</param>
void Enemy::BalloonLost(const int& balloonObjectNumber, const int& playerObjectNumber)
{
	// ���D�̃I�u�W�F�N�gID�����Ƃɔ�A�N�e�B�u�ɂ���
	for (const auto& balloon : m_balloonObject)
	{
		// �ԍ��ƕ��D���A�N�e�B�u��ԂłȂ��ꍇ�X�L�b�v
		if (balloon->GetObjectNumber() != balloonObjectNumber ||
			!balloon->GetIsActive()) continue;

		// ��A�N�e�B�u�ɂ���
		balloon->GetParent()->SetIsActive(false);
		// ���D�̐������炷
		m_balloonIndex--;
		// ���������I�u�W�F�N�g
		ObjectMessenger::GetInstance()->Dispatch(
			IObject::ObjectID::PLAYER, { Message::MessageID::INVERT_Y_VECTOR });
		break;
	}
}


/// <summary>
/// �X�e�[�g���쐬����
/// </summary>
void Enemy::CreateState()
{
	// �X�e�[�g�̍쐬
	m_enemyIdleState = std::make_unique<EnemyIdleState>();
	m_enemyRunState = std::make_unique<EnemyRunState>(this);
	m_enemyAttackState = std::make_unique<EnemyAttackState>(this);
	m_enemyWanderState = std::make_unique<EnemyWanderState>(this);
	m_enemyChaseState = std::make_unique<EnemyChaseState>(
		dynamic_cast<Object*>(this), dynamic_cast<Object*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER)[0]),
		m_steeringBehavior.get(), dynamic_cast<SeekBehavior*>(m_steeringBehavior->GetSteeringBehavior(BEHAVIOR_TYPE::SEEK))
	);

	// �X�e�[�g�̏���������
	m_enemyIdleState->Initialize();
	m_enemyRunState->Initialize();
	m_enemyAttackState->Initialize();
	m_enemyWanderState->Initialize();
	m_enemyChaseState->Initialize();

	// �����X�e�[�g�ɃA�C�h����Ԃ�ݒ�
	Object::SetState(m_enemyIdleState.get());
}


/// <summary>
/// �X�e�A�����O�r�w�C�r�A���쐬����
/// </summary>
void Enemy::CreateSteeringBehavior()
{
	// �X�e�A�����O�r�w�C�r�A�̒ǉ�
	m_steeringBehavior = std::make_unique<SteeringBehavior>();
	m_steeringBehavior->Initialize();

	// �m�b�N�o�b�N�r�w�C�r�A
	std::unique_ptr<KnockbackBehavior> knockback = std::make_unique<KnockbackBehavior>(this);
	m_steeringBehavior->Attach(BEHAVIOR_TYPE::KNOCK_BACK, std::move(knockback));

	// �h���r�w�C�r�A
	std::unique_ptr<FloatBehavior> floatBehavior = std::make_unique<FloatBehavior>();
	m_steeringBehavior->Attach(BEHAVIOR_TYPE::FLOATING, std::move(floatBehavior));

	// �͂�������r�w�C�r�A
	std::unique_ptr<FloatForceBehavior> floatForce = std::make_unique<FloatForceBehavior>();
	floatForce->SetForceStrength(0.0f);
	floatForce->SetForceDirection(DirectX::SimpleMath::Vector3::Up);
	m_steeringBehavior->Attach(BEHAVIOR_TYPE::FLOAT_FORCE, std::move(floatForce));

	// �X�e�[�W���ɉ����߂��r�w�C�r�A
	std::unique_ptr<PushBackBehavior> pushBack = std::make_unique<PushBackBehavior>(this);
	m_steeringBehavior->Attach(BEHAVIOR_TYPE::PUSH_BACK, std::move(pushBack));

	std::unique_ptr<SeekBehavior> seekBehavior = std::make_unique<SeekBehavior>(this, dynamic_cast<Object*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER)[0]));
	
	m_steeringBehavior->Attach(BEHAVIOR_TYPE::SEEK, std::move(seekBehavior));


	m_steeringBehavior->Off(BEHAVIOR_TYPE::FLOATING);
}

/// <summary>
/// �I�u�W�F�N�g���A�^�b�`����
/// </summary>
void Enemy::AttachObject()
{
	// �̂�ǉ�����
	this->Attach(EnemyFactory::CreateEnemyBody(this,
		{ 0.0f ,5.9f ,0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));

	// ���D��ǉ�����
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ 0.0f ,10.0f ,0.2f }, { -20.0f ,0.0f ,0.0f }, DirectX::SimpleMath::Vector3::One));
	// ���D��ǉ�����
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ 0.9f ,10.0f ,0.0f }, { -0.0f ,0.0f ,16.0f }, DirectX::SimpleMath::Vector3::One));
	// ���D��ǉ�����
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ -0.9f ,10.0f ,0.0f }, { -0.0f ,0.0f ,-16.0f }, DirectX::SimpleMath::Vector3::One));

	// ���D�̃{�f�B���擾
	for (int i = 0; i < 3; i++)
		m_balloonObject.push_back(dynamic_cast<Balloon*>(m_childs[i + 1].get())->GetBody());

	// �I�u�W�F�N�g�̃J�E���g�����Z�b�g
	Object::ResetNumber();
}