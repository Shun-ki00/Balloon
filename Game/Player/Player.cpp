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
#include "Game/SteeringBehavior/SteeringBehavior.h"

#include "Game/Message/ObjectMessenger.h"
#include "Game/Visitor/CollisionVisitor.h"
#include "Game/Parameters/Parameters.h"
#include "Game/Enemy/Enemy.h"
#include "Game/Balloon/Balloon.h"
#include "Game/Player/Body.h"

// �X�e�[�g
#include "Game/States/Player/PlayerIdleState.h"
#include "Game/States/Player/PlayerRunState.h"
#include "Game/States/Player/PlayerAttackState.h"
#include "Game/States/Player/PlayerSitState.h"

#include "Game/Status/BalloonScaleController.h"
#include "Game/Status/HpController.h"


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
	m_collisionVisitor{},
	m_isActive(true),
	m_objectNumber(root->GetObjectNumber() + Object::CountUpNumber()),
	m_objectID(objectID),
	m_messageID(messageID),
	m_transform{},
	m_parent(parent),
	m_childs {},
	m_boundingSphere{},
	m_balloonObject{},
	m_velocity{},
	m_heading{},
	m_side{},
	m_acceralation{},
	m_steeringBehavior{},
	m_playerIdleState{},
	m_playerRunState{},
	m_playerAttackState{},
	m_playerSitState{},
	m_balloonScaleController{},
	m_hpController{},
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
	//m_steeringBehavior = WindBehavior::GetInstance();

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
	// �I�u�W�F�N�g���A�^�b�`����
	this->AttachObject();
	// �X�e�A�����O�r�w�C�r�A���쐬����
	this->CreateSteeringBehavior();
	// �X�e�[�g���쐬����
	this->CreateState();

	// �����蔻��̍쐬
	m_boundingSphere = std::make_unique<DirectX::BoundingSphere>();
	// ������
	m_boundingSphere->Center = DirectX::SimpleMath::Vector3::Up * 0.2f;
	m_boundingSphere->Radius = 0.3f;
	
	// HP���R���g���[��
	m_hpController = std::make_unique<HpController>();
	m_hpController->Initialize();
	// ���D�̑傫�����R���g���[��
	m_balloonScaleController = std::make_unique<BalloonScaleController>(
		m_hpController.get(),dynamic_cast<FloatForceBehavior*>( m_steeringBehavior->GetSteeringBehavior(BEHAVIOR_TYPE::FLOAT_FORCE)));
	m_balloonScaleController->Initialize();

	// ���݂̃X�e�[�g��ݒ�
	Object::SetState(m_playerIdleState.get());
	// �����蔻�������
	m_collisionVisitor->GetInstance()->StartPrepareCollision(this);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Player::Update(const float& elapsedTime)
{
	// �v���C���[���Œ��Ԃ̏ꍇ
	if (m_isFixed)
	{
		FloatBehavior* floatBehavior = dynamic_cast<FloatBehavior*>(m_steeringBehavior->GetSteeringBehavior(BEHAVIOR_TYPE::FLOATING));

		floatBehavior->On();
		DirectX::SimpleMath::Vector3 acceleration = floatBehavior->Calculate();

		// ���x�ɉ����x�����Z����
		m_velocity += acceleration * elapsedTime;
		// ���݂̈ʒu���X�V����
		m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);

		m_velocity = m_velocity * (1.0f - 2.0f * elapsedTime);

		// Transform�̍X�V�̂ݍs��
		m_transform->Update();

		// ���D�̑傫�����X�V����
		m_balloonScaleController->Update(elapsedTime);
		// HP�̍X�V����
		m_hpController->Update(elapsedTime);


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

	// ���D�̑傫�����X�V����
	m_balloonScaleController->Update(elapsedTime);
	// HP�̍X�V����
	m_hpController->Update(elapsedTime);


	// ���D�̑傫����UI�ɓn��
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::BALLOON_HP_UI,
		{ Message::MessageID::BALLOON_SCALE , 0,m_balloonScaleController->GetBalloonScale(),false});
	// HP��UI�֒ʒm
	ObjectMessenger::GetInstance()->Dispatch(
		IObject::ObjectID::HP_GAUGE_UI,
		{ Message::MessageID::HP_GAUGE, 0, m_hpController->GetHp(), false } 
	);
	// �v���C���[�̍�����UI�ɓn��
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER_ICON_UI, { Message::MessageID::PLAYER_HEIGHT , 0,m_transform->GetLocalPosition().y,false });

	float result = m_balloonScaleController->GetBalloonScale() * 6.0f - 3.0f;
	dynamic_cast<FloatForceBehavior*>(m_steeringBehavior->GetSteeringBehavior(BEHAVIOR_TYPE::FLOAT_FORCE))->SetForceStrength(result);

	// �I�u�W�F�N�g�̍X�V����
	Object::Update(elapsedTime);

	// ���Ǘ͂�������x���v�Z����
	DirectX::SimpleMath::Vector3 acceleration = m_steeringBehavior->Calculate(elapsedTime);
	// ���x�ɉ����x�����Z����
	m_velocity += acceleration * elapsedTime;
	// ���݂̈ʒu���X�V����
	m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);

	m_velocity = m_velocity * (1.0f - 2.0f * elapsedTime);

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

	// �����蔻����s��

	// �G���擾����
	auto enemys =
		ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::ENEMY);
	for (const auto& enemy : enemys)
	{	
		// �v���C���[�ƓG�̕��D�̓����蔻����s��
		for (const auto& balloon : dynamic_cast<Enemy*>(enemy)->GetBalloonObject())
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


/// <summary>
/// �����蔻�����������
/// </summary>
/// <param name="collision"></param>
void Player::PrepareCollision(ICollisionVisitor* collision)
{
	// ����v���C���[�݂̂̓����蔻��Ȃ̂ōċA�����͍s��Ȃ�
	collision->PrepareCollision(this, m_boundingSphere.get());

	for (const auto& child : m_childs)
	{
		if (child->GetObjectID() == IObject::ObjectID::BALLOON)
			dynamic_cast<Balloon*>(child.get())->PrepareCollision(collision);
	}
}

/// <summary>
/// �����蔻����s��
/// </summary>
/// <param name="collision"></param>
/// <param name="bullets"></param>
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
				auto enemy = ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::BALLOON, messageData.dataInt)->GetParent();
				if (enemy->GetParent()->GetParent()->GetObjectID() == ObjectID::BALLOON)
				{
					// �G�̃I�u�W�F�N�g���L���X�g����
					enemy->SetIsActive(false);
				}

			}
			break;
		case Message::MessageID::PLAYER_ANIMATION:

			// �ړ����[�v�A�j���[�V����
			m_transform->GetTween()->DOMoveX(20.0f, 20.0f).SetLoops(1000000, Tween::LoopType::Yoyo);
			// ��]���[�v�A�j���[�V����
			m_transform->GetTween()->DORotationY(-180.0f, 8.0f).SetLoops(1000000, Tween::LoopType::Yoyo);
			break;

		case Message::MessageID::FIXED :
			m_isFixed = messageData.dataBool;

			if (messageData.dataBool)
			{
				m_steeringBehavior->Off(BEHAVIOR_TYPE::PUSH_BACK);
				m_steeringBehavior->Off(BEHAVIOR_TYPE::FLOAT_FORCE);

				m_steeringBehavior->On(BEHAVIOR_TYPE::FLOATING);
			}
			else
			{
				m_steeringBehavior->On(BEHAVIOR_TYPE::PUSH_BACK);
				m_steeringBehavior->On(BEHAVIOR_TYPE::FLOAT_FORCE);

				m_steeringBehavior->Off(BEHAVIOR_TYPE::FLOATING);
			}
			break;

		case Message::MessageID::PLAYER_TITLE_ANIMATION:

			using namespace DirectX::SimpleMath;

			// �̂̉�]�p������
			dynamic_cast<Body*>(m_childs[0].get())->GetTransform()->GetTween()->DORotation({ 0.0f ,-10.0f ,0.0f }, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
			// �����̉�]�p������
			dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[2]->GetTransform()->SetLocalRotation(Quaternion::CreateFromAxisAngle(Vector3::UnitX, DirectX::XMConvertToRadians(20.0f)));
			// �E���̉�]�p������
			dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[4]->GetTransform()->SetLocalRotation(Quaternion::CreateFromAxisAngle(Vector3::UnitX, DirectX::XMConvertToRadians(-20.0f)));

			// ���̃A�j���[�V����
			dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[0]->GetTransform()->GetTween()->DORotation({ -5.0f ,-10.0f ,0.0f }, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
			// �E�r�̃A�j���[�V����
			dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[3]->GetTransform()->GetTween()->DORotation({ -45.0f ,0.0f ,-85.0f }, 1.0f).SetLoops(10000000,Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
			// ���r�̃A�j���[�V����
			dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[1]->GetTransform()->GetTween()->DORotation({ -100.0f ,-60.0f ,0.0f }, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
			// �����̃A�j���[�V����
			dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[2]->GetTransform()->GetTween()->DORotation({ -20.0f , 0.0f ,0.0f }, 0.3f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
			// �E���̃A�j���[�V����
			dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[4]->GetTransform()->GetTween()->DORotation({ 20.0f , 0.0f ,0.0f }, 0.3f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
	
			break;

		case Message::MessageID::PLAYER_SIT_ANIMATION:

			// ���E�̑���90�x�Ȃ���
			dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[2]->GetTransform()->SetLocalRotation(Quaternion::CreateFromAxisAngle(Vector3::UnitX, DirectX::XMConvertToRadians(-90.0f)));
			dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[4]->GetTransform()->SetLocalRotation(Quaternion::CreateFromAxisAngle(Vector3::UnitX, DirectX::XMConvertToRadians(-90.0f)));

			// ��������������
			dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[0]->GetTransform()->SetLocalRotation(
				Quaternion::CreateFromAxisAngle(Vector3::UnitX, DirectX::XMConvertToRadians(10.0f))* 
				Quaternion::CreateFromAxisAngle(Vector3::UnitY, DirectX::XMConvertToRadians(-20.0f))
			);


			// �E�r�̃A�j���[�V����
			dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[3]->GetTransform()->GetTween()->DORotation({ 0.0f ,0.0f ,-5.0f }, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
			// ���r�̃A�j���[�V����
			dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[1]->GetTransform()->GetTween()->DORotation({ 0.0f ,0.0f ,5.0f }, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);
			// ���̃A�j���[�V����
			dynamic_cast<Body*>(m_childs[0].get())->GetChilds()[0]->GetTransform()->GetTween()->DORotationY(20.0f, 1.0f).SetLoops(10000000, Tween::LoopType::Yoyo).SetEase(Tween::EasingType::EaseInOutSine);

		default:
			break;
	}
}


/// <summary>
/// �L�[�{�[�h�̒ʒm���󂯎��
/// </summary>
/// <param name="type">�L�[�^�C�v</param>
/// <param name="key">�L�[</param>
void Player::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	if (m_isFixed) return;

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
				// HP������Ȃ�L����
				if (m_hpController->GetHp() <= 0.01f) break;
				m_balloonScaleController->On();
			}
			if (type == KeyType::ON_KEY_UP)
			{
				// ������
				m_balloonScaleController->Off();
			}
			break;

		case DirectX::Keyboard::Keys::Z:

			if (!m_hpController->HpReduction(0.1f))
				break;
		
			this->ChangeState(m_playerAttackState.get());

			break;

		default:
			break;
	}
}


/// <summary>
/// �X�e�[�g���쐬����
/// </summary>
void Player::CreateState()
{
	// �X�e�[�g�̍쐬
	m_playerIdleState = std::make_unique<PlayerIdleState>();
	m_playerRunState = std::make_unique<PlayerRunState>(this);
	m_playerAttackState = std::make_unique<PlayerAttackState>(this);
	m_playerSitState = std::make_unique<PlayerSitState>(this);

	// �X�e�[�g�̏���������
	m_playerIdleState->Initialize();
	m_playerRunState->Initialize();
	m_playerAttackState->Initialize();
	m_playerSitState->Initialize();
}


/// <summary>
/// �X�e�A�����O�r�w�C�r�A���쐬����
/// </summary>
void Player::CreateSteeringBehavior()
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

	m_steeringBehavior->Off(BEHAVIOR_TYPE::FLOATING);
}

/// <summary>
/// �I�u�W�F�N�g���A�^�b�`����
/// </summary>
void Player::AttachObject()
{
	// �̂�ǉ�����
	this->Attach(PlayerFactory::CreatePlayerBody(this,
		{0.0f ,5.9f ,0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));

	// ���D��ǉ�����
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ 0.0f ,10.0f ,0.2f }, { -20.0f ,0.0f ,0.0f }, DirectX::SimpleMath::Vector3::One));
	// ���D��ǉ�����
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ 0.9f ,10.0f ,0.0f }, { -0.0f ,0.0f ,16.0f }, DirectX::SimpleMath::Vector3::One));
	// ���D��ǉ�����
	this->Attach(BalloonFactory::CreateBalloon(this, IObject::ObjectID::BALLOON,
		{ -0.9f ,10.0f ,0.0f }, { -0.0f ,0.0f ,-16.0f }, DirectX::SimpleMath::Vector3::One));


	for (int i = 0; i < 3; i++)
	{
		// ���D�̃{�f�B���擾
		m_balloonObject.push_back(dynamic_cast<Balloon*>(m_childs[i + 1].get())->GetBody());
	}

	// �I�u�W�F�N�g�̃J�E���g�����Z�b�g
	Object::ResetNumber();
}