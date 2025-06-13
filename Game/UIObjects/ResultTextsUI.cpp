// ============================================
// 
// �t�@�C����: ResultTextUI.cpp
// �T�v: ���U���g�V�[���e�L�X�gUI�I�u�W�F�N�g
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/ResultTextUI.h"
#include "Framework/CommonResources.h"
// ���\�[�X
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
// �����_�����O�I�u�W�F�N�g
#include "Game/RenderableObjects/UIRenderableObject .h"
// �t�@�N�g���[
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/EnemyFactory.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="root">���[�g�I�u�W�F�N�g</param>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
/// <param name="messageID">���b�Z�[�WID</param>
ResultTextUI::ResultTextUI(IObject* root, IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale,
	ResultTextUI::TextID textId)
	:
	// ���N���X
	UIObject(),
	m_isActive(true),
	m_objectNumber(root->GetObjectNumber() + UIObject::GetNumber()),
	m_objectID(objectID),
	m_textId(textId),
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
}

/// <summary>
/// ����������
/// </summary>
void ResultTextUI::Initialize()
{
	// �e�N�X�`���T�C�Y���擾����
	float width = 0.0f, height = 0.0f;
	Resources::GetInstance()->GetTextureResources()->GetTextureSize(TextureKeyID::ResultText, width, height);

	// �V�[�g�͏c��2���Ȃ̂ō������Ɋ���
	height /= 2.0f;
	
	// ����1��
	float uvScaleX = 1.0f / 1.0f; 
	// �c��2��
	float uvScaleY = 1.0f / 2.0f;

	// ����1���Ȃ̂ŃI�t�Z�b�g�͏��0
	float uvOffsetX = 0.0f;                      
	float uvOffsetY = 0.0f;           

	// �e�L�X�gID�����Ƃ�Y���̃I�t�Z�b�g�l�����߂�
	switch (m_textId)
	{
		case ResultTextUI::TextID::CLEAR:
			uvOffsetY = uvScaleY * 0;
			break;
		case ResultTextUI::TextID::FAILED:
			uvOffsetY = uvScaleY * 1;
			break;
		default:
			break;
	}
	
	// �������_�o�b�t�@�f�[�^
	UIVertexBuffer vertexBuffer =
	{
		{m_transform->GetLocalPosition().x , m_transform->GetLocalPosition().y ,
		m_transform->GetLocalPosition().z ,0.0f}, 
		{m_transform->GetLocalScale().x ,m_transform->GetLocalScale().y , 0.0f},						 
		{width , height},							  
		{uvOffsetX ,uvOffsetY , uvScaleX ,uvScaleY }, 
		{1.0f ,1.0f ,1.0f ,1.0f },					  
		{0.0f ,0.0f ,1.0f ,0.0f}					  
	};

	// �`��I�u�W�F�N�g�쐬
	m_renderableObject = std::make_unique<UIRenderableObject>();
	// ������
	m_renderableObject->Initialize(vertexBuffer, TextureKeyID::ResultText, TextureKeyID::Rule,PS_ID::UI_PS);

	// �`��Ǘ��҂ɓn��
	m_commonResources->GetRenderer()->Attach(this, m_renderableObject.get());
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void ResultTextUI::Update(const float& elapsedTime)
{
	// Transform�̍X�V����
	m_transform->Update();
	// �`��I�u�W�F�N�g�X�V����
	m_renderableObject->Update(
		m_commonResources->GetDeviceResources()->GetD3DDeviceContext(),
		m_transform->GetWorldMatrix());
}

/// <summary>
/// �I������
/// </summary>
void ResultTextUI::Finalize() {}


/// <summary>
/// ���b�Z���W���[��ʒm����
/// </summary>
/// <param name="messageData">���b�Z�[�W�f�[�^</param>
void ResultTextUI::OnMessegeAccepted(Message::MessageData messageData)
{
	UNREFERENCED_PARAMETER(messageData);
}

/// <summary>
/// �L�[�{�[�h�̃��b�Z�[�W��ʒm����
/// </summary>
/// <param name="type">�L�[�^�C�v</param>
/// <param name="key">�L�[</param>
void ResultTextUI::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(key);
}



