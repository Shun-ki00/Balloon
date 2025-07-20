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
#include "Interface/ICamera.h"
#include "Game/Node/Root.h"
#include "Game/Parameters/Parameters.h"
#include "Game/Message/ObjectMessenger.h"
#include "Interface/IObject.h"
#include "Game/Message/Message.h"
#include "Game/Factorys/SceneFactory.h"
#include "Game/Scenes/StageSelectScene.h"
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
	m_root{},
	m_currentState{},
	m_fadeInState{},
	m_titleMainState{},
	m_fadeOutState{}
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
	SceneFactory::CreateTitleScene(m_root);

	// �X�e�[�g�̍쐬
	this->CreateStates();
}

/// <summary>
/// �X�^�[�g����
/// </summary>
void TitleScene::Start()
{
	// BGM���Đ�����
	AudioManager::GetInstance()->PlayBgm(XACT_WAVEBANK_SOUNDS::XACT_WAVEBANK_SOUNDS_TITLESCENE,1.0f);

	// �^�C�g�����S�̃A�j���[�V�������s��
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::TITLE_LOGO_UI, { Message::MessageID::TITLE_LOGO_ANIMATION });
	// �X�^�[�g�e�L�X�g�̃A�j���[�V�������s��
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::START_TEXT_UI, { Message::MessageID::START_TEXT_ANIMATION });
	// �v���C���[�̓�����ύX
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER, { Message::MessageID::PLAYER_TITLE_ANIMATION });

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

/// <summary>
/// �`�揈��
/// </summary>
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
		case Message::SceneMessageID::FADE_OUT_CANGE_MENU_SCENE:
			// ���̃V�[���̏������s��
			SceneManager::GetInstance()->PrepareScene<StageSelectScene>();
			// �X�e�[�g��؂�ւ���
			this->ChangeState(m_fadeOutState.get());
			break;		
		case Message::SceneMessageID::FADE_OUT_EXIT_GAME:
			// �X�e�[�g��؂�ւ���
			this->ChangeState(m_gameExitFadeOutState.get());
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
///	�V�[���̃X�e�[�g�̍쐬
/// </summary>
void TitleScene::CreateStates()
{
	// �t�F�[�h�C���X�e�[�g�쐬 ����������
	m_fadeInState = std::make_unique<FadeInState>(0);
	m_fadeInState->Initialize();

	// �^�C�g���V�[�����C���X�e�[�g�쐬�@����������
	m_titleMainState = std::make_unique<TitleMainState>();
	m_titleMainState->Initialize();

	// �t�F�[�h�A�E�g�X�e�[�g�쐬�@����������
	m_fadeOutState = std::make_unique<FadeOutState>(Message::MessageData{Message::MessageID::FADE_OUT,0,1.0f ,false});
	m_fadeOutState->Initialize();

	// �Q�[���I���t�F�[�h�A�E�g�X�e�[�g�쐬�@����������
	m_gameExitFadeOutState = std::make_unique<FadeOutState>(Message::MessageData{ Message::MessageID::FADE_OUT_EXIT_GAME,0,1.0f ,false });
	m_gameExitFadeOutState->Initialize();

	// �����X�e�[�g��ݒ�
	m_currentState = m_fadeInState.get();
}