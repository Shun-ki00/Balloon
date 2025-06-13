// ============================================
// 
// �t�@�C����: TitleScene.cpp
// �T�v: �^�C�g���̃V�[��
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/TitleScene.h"
#include "Game/Node/Root.h"
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/EffectFactory.h"
#include "Game/Parameters/Parameters.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Scenes/PlayScene.h"

#include "Game/UIObjects/TitleLogoUI.h"
#include "Game/UIObjects/StartTextUI.h"
#include "Game/Fade/Fade.h"

#include "Interface/ICamera.h"
#include "Game/Factorys/CameraFactory.h"

// �X�e�[�g
#include "Interface/IState.h"
#include "Game/States/SceneStates/FadeStates/FadeInState.h"
#include "Game/States/SceneStates/FadeStates/FadeOutState.h"
#include "Game/States/SceneStates/TitleMainState.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
	:
	m_parameters{},
	m_commonResources{},
	m_currentState{},
	m_fadeInState{},
	m_titleMainState{},
	m_fadeOutState{},
	m_root{}
{
	// �C���X�^���X���擾����
	m_commonResources  = CommonResources::GetInstance();
	m_parameters       = Parameters::GetInstance();
	m_root             = Root::GetInstance();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene() {}


/// <summary>
/// ����������
/// </summary>
void TitleScene::Initialize()
{
	// ���[�g�̏���������
	m_root->Initialize();

	// �I�u�W�F�N�g�̍쐬
	this->CreateObjects();
	// UI�I�u�W�F�N�g�̍쐬
	this->CreateUiObjects();
	// �J�����̍쐬
	this->CreateCameras();

	// �X�e�[�g�̍쐬
	this->CreateStates();
}

/// <summary>
/// �X�^�[�g����
/// </summary>
void TitleScene::Start()
{
	// �^�C�g�����S�̃A�j���[�V�������s��
	ObjectMessenger::GetInstance()->Dispatch(1, Message::MessageID::TITLE_LOGO_ANIMATION);
	// �X�^�[�g�e�L�X�g�̃A�j���[�V�������s��
	ObjectMessenger::GetInstance()->Dispatch(2, Message::MessageID::START_TEXT_ANIMATION);

	// �X�e�[�g�X�^�[�g����
	m_currentState->PreUpdate();
}

/// <summary>
/// �X�V��������
/// </summary>
void TitleScene::Update()
{
	// �o�ߎ��Ԃ��擾����
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// �V�[���X�e�[�g�̍X�V����
	m_currentState->Update(elapsedTime);

	// ���[�g�̍X�V����
	m_root->Update(elapsedTime);
}

void TitleScene::Render()
{
	// �`�揈�����s��
	m_commonResources->GetRenderer()->Render();
}

/// <summary>
/// �I������
/// </summary>
void TitleScene::Finalize() {}

/// <summary>
/// �X�e�[�g��؂�ւ���
/// </summary>
/// <param name="newState">���̃X�e�[�g</param>
void TitleScene::ChangeState(IState* newState)
{
	// �I������
	m_currentState->PostUpdate();

	// �X�e�[�g��؂�ւ���
	m_currentState = newState;

	// �X�^�[�g����
	m_currentState->PreUpdate();
}

/// <summary>
/// ���b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�W�f�[�^</param>
void TitleScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::SceneMessageID::FADE_OUT:

			break;
		case Message::SceneMessageID::FADE_OUT_CANGE_MENU_SCENE:

			// ���̃V�[���̏������s��
			SceneManager::GetInstance()->PrepareScene<PlayScene>();

			// �X�e�[�g��؂�ւ���
			this->ChangeState(m_fadeOutState.get());

			break;		
		case Message::SceneMessageID::MAIN:

			// �X�e�[�g��؂�ւ���
			this->ChangeState(m_titleMainState.get());

			break;
		default:
			break;
	}
}


/// <summary>
/// �I�u�W�F�N�g�̍쐬
/// </summary>
void TitleScene::CreateObjects()
{
	// �v���C���[
	m_root->Attach(PlayerFactory::CreatePlayer(m_root,
		{ 2.7f , -0.5f ,-1.5f }, {0.0f ,-45.0f, 0.0f}, DirectX::SimpleMath::Vector3::One * 0.1f, true));
}


/// <summary>
/// UI�I�u�W�F�N�g�̍쐬
/// </summary>
void TitleScene::CreateUiObjects()
{
	// �^�C�g�����S
	std::unique_ptr<IObject> logo = std::make_unique<TitleLogoUI>(m_root, nullptr, IObject::ObjectID::TITLE_LOGO_UI,
		DirectX::SimpleMath::Vector3{ 400.0f , -300.0f ,0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One, Message::MessageID::NONE);
	ObjectMessenger::GetInstance()->Register(1, logo.get());
	logo->Initialize();
	m_root->Attach(std::move(logo));

	// �X�^�[�g�e�L�X�g
	std::unique_ptr<IObject> startText = std::make_unique<StartTextUI>(m_root, nullptr, IObject::ObjectID::START_TEXT_UI,
		DirectX::SimpleMath::Vector3{ 400.0f , 400.0f ,0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::Zero, Message::MessageID::NONE);
	ObjectMessenger::GetInstance()->Register(2, startText.get());
	startText->Initialize();
	m_root->Attach(std::move(startText));

	// �t�F�[�h�I�u�W�F�N�g
	std::unique_ptr<IObject> fade = std::make_unique<Fade>(m_root, nullptr, IObject::ObjectID::FADE,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One, Message::MessageID::NONE);
	ObjectMessenger::GetInstance()->Register(3, fade.get());
	fade->Initialize();
	m_root->Attach(std::move(fade));
}


/// <summary>
/// �J�����̍쐬
/// </summary>
void TitleScene::CreateCameras()
{
	// �J�����̍쐬������
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Backward ,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Down, DirectX::XMConvertToRadians(30.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(10.0f)))
	);

	// �J�����V�X�e�����A�^�b�`����
	m_root->Attach(CameraFactory::CreateCameraSystem(m_root, std::move(cameras)));
}


/// <summary>
///	�V�[���̃X�e�[�g�̍쐬
/// </summary>
void TitleScene::CreateStates()
{
	// �t�F�[�h�C���X�e�[�g�쐬 ����������
	m_fadeInState = std::make_unique<FadeInState>(3);
	m_fadeInState->Initialize();

	// �^�C�g���V�[�����C���X�e�[�g�쐬�@����������
	m_titleMainState = std::make_unique<TitleMainState>();
	m_titleMainState->Initialize();

	// �t�F�[�h�A�E�g�X�e�[�g�쐬�@����������
	m_fadeOutState = std::make_unique<FadeOutState>(3);
	m_fadeOutState->Initialize();

	// �����X�e�[�g��ݒ�
	m_currentState = m_fadeInState.get();
}