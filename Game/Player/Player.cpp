// ============================================
// 
// �t�@�C����: Player.cpp
// �T�v: �v���C���[�I�u�W�F�N�g
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/Player/Player.h"
#include "Game/Object/Object.h"
#include "Game/Node/Root.h"

#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Framework/Resources/ModelResources.h"
#include "Game/RenderableObjects/PlayerRenderableObject.h"

#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/BalloonFactory.h"

#include "Game/Buffers.h"

#include "Game/SteeringBehavior/WindBehavior.h"
#include "Game/SteeringBehavior/KnockbackBehavior.h"
#include "Game/SteeringBehavior/FloatBehavior.h"
#include "Game/SteeringBehavior/FloatForceBehavior.h"
#include "Game/SteeringBehavior/PushBackBehavior.h"

#include "Game/Message/ObjectMessenger.h"
#include "Game/Visitor/CollisionVisitor.h"
#include "Game/Parameters/Parameters.h"
#include "Game/Enemy/Enemy.h"
#include "Game/Balloon/Balloon.h"

// �X�e�[�g
#include "Game/States/Player/PlayerIdleState.h"
#include "Game/States/Player/PlayerRunState.h"
#include "Game/States/Player/PlayerAttackState.h"
#include "Game/States/Player/PlayerSitState.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="angle"></param>
/// <param name="position"></param>
/// <param name="messageID"></param>
Player::Player(IObject* root, IObject* parent, IObject::ObjectID objectID,
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

	// �X�e�A�����O�r�w�C�r�A�̃C���X�^���X���擾
	m_steeringBehavior = WindBehavior::GetInstance();

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{

}


/// <summary>
/// ����������
/// </summary>
void Player::Initialize()
{
	// �����蔻��̏������W��ݒ�
	m_boundingSphere.Center = m_transform->GetLocalPosition();
	// �����蔻��̑傫����ݒ�
	m_boundingSphere.Radius = 2.0f;

	// �X�e�[�g�̍쐬
	m_playerIdleState   = std::make_unique<PlayerIdleState>();
	m_playerRunState    = std::make_unique<PlayerRunState>(this);
	m_playerAttackState = std::make_unique<PlayerAttackState>(this);
	m_playerSitState    = std::make_unique<PlayerSitState>(this);
	

	// ���݂̃X�e�[�g��ݒ�
	Object::SetState(m_playerSitState.get());

	// �m�b�N�o�b�N
	m_knockbackBehavior = std::make_unique<KnockbackBehavior>(this);
	// �h��鏈��
	m_floatBehavior = std::make_unique<FloatBehavior>();
	m_floatBehavior->On();

	m_floatBehavior->Off();

	m_floatForceBehavior = std::make_unique<FloatForceBehavior>();
	m_floatForceBehavior->SetForceStrength(0.0f);

	m_pushBackBehavior = std::make_unique<PushBackBehavior>(this);

	m_isBalloon = false;
	m_isFixed = false;
	m_balloonScale = 0.0f;

	// �̂�ǉ�����
	this->Attach(PlayerFactory::CreatePlayerBody(this,
		DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));

	// ���D��ǉ�����
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
	// ���D��ǉ�����
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		DirectX::SimpleMath::Vector3::Right * -1.0f , DirectX::SimpleMath::Vector3::Forward * 25.0f , DirectX::SimpleMath::Vector3::One));
	// ���D��ǉ�����
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		DirectX::SimpleMath::Vector3::Left * -1.0f, DirectX::SimpleMath::Vector3::Backward * 25.0f, DirectX::SimpleMath::Vector3::One));


	for (int i = 0; i < 3; i++)
	{
		// ���D�̃{�f�B���擾
		m_balloonObject.push_back(dynamic_cast<Balloon*>(m_childs[i + 1].get())->GetBody());
	}

	// �X�e�[�g�̏���������
	m_playerIdleState->Initialize();
	m_playerRunState->Initialize();
	m_playerAttackState->Initialize();
	m_playerSitState->Initialize();

	// �I�u�W�F�N�g�̃J�E���g�����Z�b�g
	Object::ResetNumber();

	m_collisionVisitor->GetInstance()->StartPrepareCollision(this);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Player::Update(const float& elapsedTime)
{
	// �Œ�ݒ�̏ꍇ
	if (m_isFixed)
	{
		m_floatBehavior->On();
		DirectX::SimpleMath::Vector3 acceleration = m_floatBehavior->Calculate();

		// ���x�ɉ����x�����Z����
		m_velocity += acceleration * elapsedTime;
		// ���݂̈ʒu���X�V����
		m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);

		m_velocity = m_velocity * (1.0f - 2.0f * elapsedTime);

		// Transform�̍X�V�̂ݍs��
		m_transform->Update();

		// �q�I�u�W�F�N�g�̍X�V����
		for (const auto& child : m_childs)
		{
			child->Update(elapsedTime);
		}

		return;
	}

	m_knockbackBehavior->SetTargetObject(
		dynamic_cast<Object*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::ENEMY,1)));

	if (m_isBalloon)
	{
		m_balloonScale += 2.0f * elapsedTime;

		if (m_balloonScale >= 1.0f)
			m_balloonScale = 1.0f;

		m_floatForceBehavior->SetForceStrength(m_balloonScale * 3.0f);
	}
	else
	{
		m_balloonScale -= 2.0f * elapsedTime;

		if (m_balloonScale <= -1.0f)
			m_balloonScale = -1.0f;

		m_floatForceBehavior->SetForceStrength(m_balloonScale * 3.0f);
	}

	Object::Update(elapsedTime);

	// ���Ǘ͂�������x���v�Z����
	//DirectX::SimpleMath::Vector3 acceleration = 
	//	m_steeringBehavior->Calculate() + m_knockbackBehavior->Calculate() + 
	//	m_floatBehavior->Calculate() + m_floatForceBehavior->Calculate() + m_pushBackBehavior->Calculate();

	//// ���x�ɉ����x�����Z����
	//m_velocity += acceleration * elapsedTime;
	//// ���݂̈ʒu���X�V����
	//m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);

	//m_velocity = m_velocity * (1.0f - 2.0f * elapsedTime);

	// Transform�̍X�V����
	m_transform->Update();
	// ���[���h���W�𓖂��蔻��̍��W�ɐݒ�
	m_boundingSphere.Center = m_transform->GetWorldPosition();

	// �q�I�u�W�F�N�g�̍X�V����
	for (const auto& child : m_childs)
	{
		child->Update(elapsedTime);
	}

	// �����蔻����s��
	for (int i = 0; i < Parameters::GetInstance()->GetParameter(ParametersID::ENEMY, ParameterKeysI::Number); i++)
	{
		auto enemy = dynamic_cast<Enemy*>(ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::ENEMY, i + 1));

		for (const auto& balloon : enemy->GetBalloonObject())
		{
			m_collisionVisitor->DetectCollision(this, balloon);
		}
	}
}

/// <summary>
/// �I������
/// </summary>
void Player::Finalize()
{

}

/// <summary>
/// �p�[�c��ǉ�����
/// </summary>
/// <param name="object"></param>
void Player::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// �p�[�c���폜����
/// </summary>
/// <param name="turretPart"></param>
void Player::Detach(std::unique_ptr<IObject> object)
{

}

/// <summary>
/// �q�I�u�W�F�N�g���擾����
/// </summary>
/// <returns>�q�I�u�W�F�N�g</returns>
std::vector<IObject*> Player::GetChilds() const
{
	std::vector<IObject*> result;
	result.reserve(m_childs.size());
	for (const auto& child : m_childs)
	{
		result.push_back(child.get());
	}
	return result;
}



void Player::PrepareCollision(ICollisionVisitor* collision)
{
	// ����v���C���[�݂̂̓����蔻��Ȃ̂ōċA�����͍s��Ȃ�
	collision->PrepareCollision(this, DirectX::SimpleMath::Vector3::Up * 0.2f  , 0.3f);

	for (const auto& child : m_childs)
	{
		if (child->GetObjectID() == IObject::ObjectID::BALLOON)
			dynamic_cast<Balloon*>(child.get())->PrepareCollision(collision);
	}
}

void Player::DetectCollision(ICollisionVisitor* collision, IObject* bullets)
{
	// ������s��
	collision->DetectCollision(this, bullets);
}


/// <summary>
/// ���b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
void Player::OnMessegeAccepted(Message::MessageData messageData)
{
	switch (messageData.messageId)
	{

		case Message::MessageID::PLAYER_IDLING:
			this->ChangeState(m_playerIdleState.get());
			break;
		case Message::MessageID::PLAYER_ATTCK:
			break;

		case Message::MessageID::ON_COLLISION:
			
			if (Object::GetState() == m_playerAttackState.get())
			{
				// ������̃x�N�g���ɕω�����
				m_velocity.y = m_velocity.y * -1.0f;

				// ����̕��D��j������
				auto enemy = ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::ENEMY, messageData.dataInt);
				if (enemy->GetParent()->GetParent()->GetObjectID() == ObjectID::ENEMY)
				{
					// �G�̃I�u�W�F�N�g���L���X�g����
					enemy->SetIsActive(false);
				}

			}
			break;

		default:
			break;
	}
}


// �ʒm����
void Player::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	switch (key)
	{
		case DirectX::Keyboard::Keys::Up:

			if (type == KeyType::ON_KEY_DOWN)
			{
				if(Object::GetState() != m_playerRunState.get())
				Object::ChangeState(m_playerRunState.get());
				m_playerRunState->SetIsForward(true);
			}
			if (type == KeyType::ON_KEY_UP)
			{
				if (Object::GetState() == m_playerRunState.get())
					Object::ChangeState(m_playerIdleState.get());
			}
				

			break;
		case DirectX::Keyboard::Keys::Down:

			if (type == KeyType::ON_KEY_DOWN)
			{
				if (Object::GetState() != m_playerRunState.get())
					Object::ChangeState(m_playerRunState.get());
				m_playerRunState->SetIsBackward(true);
			}
			if (type == KeyType::ON_KEY_UP)
			{
				if (Object::GetState() == m_playerRunState.get())
					Object::ChangeState(m_playerIdleState.get());
			}

			break;
		case DirectX::Keyboard::Keys::Left:

			// �v���C���[�ɉ�]�p��^����
			m_transform->SetLocalRotation(
				DirectX::SimpleMath::Quaternion::Concatenate(
					m_transform->GetLocalRotation(),
					DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
						DirectX::SimpleMath::Vector3::Up,
						DirectX::XMConvertToRadians(2.0f))
				)
			);

			break;
		case DirectX::Keyboard::Keys::Right:

			// �v���C���[�ɉ�]�p��^����
			m_transform->SetLocalRotation(
				DirectX::SimpleMath::Quaternion::Concatenate(
					m_transform->GetLocalRotation(),
					DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
						DirectX::SimpleMath::Vector3::Up,
						DirectX::XMConvertToRadians(-2.0f))
				)
			);
			break;


		case DirectX::Keyboard::Keys::Space:

			if (type == KeyType::ON_KEY_DOWN)
			{
				m_isBalloon = true;

				if (m_balloonScale <= 0.0f)
					m_balloonScale = 0.0f;
			}
			if (type == KeyType::ON_KEY_UP)
			{
				m_isBalloon = false;
			}
			break;

		case DirectX::Keyboard::Keys::Z:

			this->ChangeState(m_playerAttackState.get());

			break;

		default:
			break;
	}



}