// ============================================
// 
// �t�@�C����: WoodBox.cpp
// �T�v: �ؔ��I�u�W�F�N�g
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/WoodBox/WoodBox.h"
#include "Game/Object/Object.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Game/RenderableObjects/WoodBoxRenderableObject.h"
#include "Game/SteeringBehavior/FloatBehavior.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="angle"></param>
/// <param name="position"></param>
/// <param name="messageID"></param>
WoodBox::WoodBox(IObject* root, IObject* parent, IObject::ObjectID objectID,
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
	m_transform{}
{

	// ���L���\�[�X�̃C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();

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

	// �I�u�W�F�N�g�̃J�E���g�����Z�b�g
	Object::ResetNumber();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WoodBox::~WoodBox()
{

}


/// <summary>
/// ����������
/// </summary>
void WoodBox::Initialize()
{
	// �����蔻��̏������W��ݒ�
	m_boundingSphere.Center = m_transform->GetLocalPosition();
	// �����蔻��̑傫����ݒ�
	m_boundingSphere.Radius = 2.0f;

	// ����������
	PBRLitConstantBuffer buffer{
		DirectX::SimpleMath::Vector4::One,
		0.316f,
		1.0f,
		1.0f,
		1.0f
	};

	// �`��I�u�W�F�N�g�쐬
	m_renderableObject = std::make_unique<WoodBoxRenderableObject>(true,
		Resources::GetInstance()->GetModelResources()->GetModel(ModelKeyID::WoodBox));
	// ����������
	dynamic_cast<WoodBoxRenderableObject*>(m_renderableObject.get())->Initialize(buffer);

	// �`��I�u�W�F�N�g��n��
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());

	// �h��鏈��
	m_floatBehavior = std::make_unique<FloatBehavior>();
	m_floatBehavior->On();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void WoodBox::Update(const float& elapsedTime)
{
	(void)elapsedTime;

	m_floatBehavior->On();
	DirectX::SimpleMath::Vector3 acceleration = m_floatBehavior->Calculate();

	// ���x�ɉ����x�����Z����
	m_velocity += acceleration * elapsedTime;
	// ���݂̈ʒu���X�V����
	m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);

	m_velocity = m_velocity * (1.0f - 2.0f * elapsedTime);

	// Transform�̍X�V�̂ݍs��
	m_transform->Update();

	// ���[���h���W�𓖂��蔻��̍��W�ɐݒ�
	m_boundingSphere.Center = m_transform->GetWorldPosition();
	// �`��I�u�W�F�N�g�X�V����
	m_renderableObject->Update(m_commonResources->GetDeviceResources()->GetD3DDeviceContext(), m_transform->GetWorldMatrix());
}

/// <summary>
/// �I������
/// </summary>
void WoodBox::Finalize()
{

}

void WoodBox::OnMessegeAccepted(Message::MessageData messageData)
{
	(void)messageData;
}

// �ʒm����
void WoodBox::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}