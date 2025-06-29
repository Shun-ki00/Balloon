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
#include "Game/Scenes/GameOverScene.h"
#include "Game/Node/Root.h"
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/EffectFactory.h"
#include "Game/Parameters/Parameters.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Scenes/PlayScene.h"

#include "Game/Scenes/TitleScene.h"

#include "Game/Factorys/SceneFactory.h"


// �X�e�[�g
#include "Interface/IState.h"
#include "Game/States/SceneStates/FadeStates/FadeInState.h"
#include "Game/States/SceneStates/FadeStates/FadeOutState.h"
#include "Game/States/SceneStates/TitleMainState.h"

// �t�F�[�h�I�u�W�F�N�g�ԍ�
const int GameOverScene::FADE_OBJECT_NUMBER = 6;


/// <summary>
/// �R���X�g���N�^
/// </summary>
GameOverScene::GameOverScene()
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
GameOverScene::~GameOverScene() {}


/// <summary>
/// ����������
/// </summary>
void GameOverScene::Initialize()
{
	// ���[�g�̏���������
	m_root->Initialize();

	// �I�u�W�F�N�g�̍쐬
	SceneFactory::CreateGameOverScene(m_root);

	// �X�e�[�g�̍쐬
	this->CreateStates();
}

/// <summary>
/// �X�^�[�g����
/// </summary>
void GameOverScene::Start()
{
	// �X�e�[�g�X�^�[�g����
	m_currentState->PreUpdate();

	// �X�J�C�{�b�N�X��ύX
	m_commonResources->GetSkyBox()->SetDayProgress(1.0f);
}

/// <summary>
/// �X�V��������
/// </summary>
void GameOverScene::Update()
{
	// �o�ߎ��Ԃ��擾����
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// �L�[�{�[�h���b�Z���W���[
	KeyboardMessenger::GetInstance()->Dispatch();

	// �V�[���X�e�[�g�̍X�V����
	m_currentState->Update(elapsedTime);

	// ���[�g�̍X�V����
	m_root->Update(elapsedTime);
}

void GameOverScene::Render()
{
	// �`�揈�����s��
	m_commonResources->GetRenderer()->Render();
}

/// <summary>
/// �I������
/// </summary>
void GameOverScene::Finalize() 
{
	// �X�J�C�{�b�N�X��ύX
	m_commonResources->GetSkyBox()->SetDayProgress(0.0f);
}

/// <summary>
/// �X�e�[�g��؂�ւ���
/// </summary>
/// <param name="newState">���̃X�e�[�g</param>
void GameOverScene::ChangeState(IState* newState)
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
void GameOverScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::SceneMessageID::FADE_OUT:

			break;
		case Message::SceneMessageID::FADE_OUT_CANGE_MENU_SCENE:

			// ���̃V�[���̏������s��
			SceneManager::GetInstance()->PrepareScene<TitleScene>();

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
///	�V�[���̃X�e�[�g�̍쐬
/// </summary>
void GameOverScene::CreateStates()
{
	// �t�F�[�h�C���X�e�[�g�쐬 ����������
	m_fadeInState = std::make_unique<FadeInState>(FADE_OBJECT_NUMBER);
	m_fadeInState->Initialize();

	// �^�C�g���V�[�����C���X�e�[�g�쐬�@����������
	m_titleMainState = std::make_unique<TitleMainState>();
	m_titleMainState->Initialize();

	// �t�F�[�h�A�E�g�X�e�[�g�쐬�@����������
	m_fadeOutState = std::make_unique<FadeOutState>(Message::MessageData{ Message::MessageID::FADE_OUT_EXIT_GAME,0,1.0f ,false });
	m_fadeOutState->Initialize();

	// �����X�e�[�g��ݒ�
	m_currentState = m_fadeInState.get();
}