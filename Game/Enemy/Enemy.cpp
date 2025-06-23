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

#include "Game/SteeringBehavior/WindBehavior.h"
#include "Game/SteeringBehavior/KnockbackBehavior.h"
#include "Game/SteeringBehavior/FloatBehavior.h"
#include "Game/SteeringBehavior/FloatForceBehavior.h"
#include "Game/SteeringBehavior/PushBackBehavior.h"
#include "Game/SteeringBehavior/SeekBehavior.h"

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
	const DirectX::SimpleMath::Vector3& scale,
	Message::MessageID messageID)
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
	m_messageID(messageID),
	m_parent(parent),
	m_transform{},
	m_childs {}
{

	m_collisionVisitor = CollisionVisitor::GetInstance();

	// �X�e�A�����O�r�w�C�r�A�̃C���X�^���X���擾
	m_steeringBehavior = WindBehavior::GetInstance();

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
	// ==== �X�e�A�����O�r�w�C�r�A�̏��������� ====

	// �m�b�N�o�b�N
	m_knockbackBehavior = std::make_unique<KnockbackBehavior>(this);
	// �h��鏈��
	m_floatBehavior = std::make_unique<FloatBehavior>();
	m_floatBehavior->On();

	m_floatBehavior->Off();

	m_floatForceBehavior = std::make_unique<FloatForceBehavior>();
	m_floatForceBehavior->SetForceStrength(0.0f);

	m_pushBackBehavior = std::make_unique<PushBackBehavior>(this);

	m_seekBehavior = std::make_unique<SeekBehavior>(this, dynamic_cast<Object*>( ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER,0)));

	// ==== �X�e�[�^�X�̍쐬�Ə��������� ====

	// HP���R���g���[��
	m_hpController = std::make_unique<HpController>();
	m_hpController->Initialize();
	// ���D�̑傫�����R���g���[��
	m_balloonScaleController = std::make_unique<BalloonScaleController>(m_hpController.get(), m_floatForceBehavior.get());
	m_balloonScaleController->Initialize();


	// ==== �I�u�W�F�N�g�̒ǉ� ====

	// �̂�ǉ�����
	this->Attach(EnemyFactory::CreateEnemyBody(this,
		DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));

	// ���D��ǉ�����
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		DirectX::SimpleMath::Vector3::Left * -1.0f, DirectX::SimpleMath::Vector3::Backward * 25.0f, DirectX::SimpleMath::Vector3::One));
	// ���D��ǉ�����
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		DirectX::SimpleMath::Vector3::Right * -1.0f, DirectX::SimpleMath::Vector3::Forward * 25.0f, DirectX::SimpleMath::Vector3::One));
	// ���D��ǉ�����
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
	
	// ���D�̃{�f�B���擾
	for (int i = 0; i < 3; i++)
		m_balloonObject.push_back(dynamic_cast<Balloon*>(m_childs[i + 1].get())->GetBody());

	// ==== �A�N�V�����Z���N�^�[ ====

	m_actionSelection = std::make_unique<ActionSelection>();
	m_actionSelection->Initialize(this);


	// ==== �����蔻�� ====

	// �����蔻�����������
	m_collisionVisitor->StartPrepareCollision(this);


	// ==== ���Z�b�g���� ====

	// �I�u�W�F�N�g�̃J�E���g�����Z�b�g
	Object::ResetNumber();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Enemy::Update(const float& elapsedTime)
{
	// �A�N�V���������肷��
	m_actionSelection->GetRootNode()->Tick();

	// �X�e�[�g�̍X�V����
	Object::Update(elapsedTime);

	// ==== �r�w�C�r�A�c���[�̍X�V���� ====

	m_knockbackBehavior->SetTargetObject(
		dynamic_cast<Object*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER, 0)));


	// ==== �X�e�A�����O�r�w�C�r�A�̍X�V���� ====

	// �e�X�e�A�����O���r�b�g�Ő���


	// ==== ���������̍X�V���� ====

	// ���݂̈ʒu���X�V����
	m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);

	m_velocity = m_velocity * (1.0f - 2.0f * elapsedTime);

	// Transform�̍X�V����
	m_transform->Update();

	// ==== �X�e�[�^�X�̍X�V���� ====

	// ���D�̑傫�����X�V����
	m_balloonScaleController->Update(elapsedTime);
	// HP�̍X�V����
	m_hpController->Update(elapsedTime);


	// ==== �q�I�u�W�F�N�g�̍X�V���� ====

	// �q�I�u�W�F�N�g�̍X�V����
	for (const auto& child : m_childs)
	{
		child->Update(elapsedTime);
	}


	// ==== �Փ˔���̍X�V ====

	// �����蔻����s��
	auto player = dynamic_cast<Player*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER,0));
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
/// ���b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
void Enemy::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{
		case Message::MessageID::ON_COLLISION:

			if (true)
			{
				// ������̃x�N�g���ɕω�����
				m_velocity.y = m_velocity.y * -1.0f;

				// ����̕��D��j������
				auto enemy = ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::BALLOON, messageData.dataInt)->GetParent();

				if(enemy == nullptr)
					enemy = ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::ENEMY, messageData.dataInt);

				// �G�̃I�u�W�F�N�g���L���X�g����
				enemy->SetIsActive(false);
			}

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
	collision->PrepareCollision(this, DirectX::SimpleMath::Vector3::Up * 0.2f, 0.3f);

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
