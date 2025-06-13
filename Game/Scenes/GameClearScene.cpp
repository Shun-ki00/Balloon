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
#include "Game/Scenes/GameClearScene.h"
#include "Game/Node/Root.h"
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/EffectFactory.h"
#include "Game/Parameters/Parameters.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Scenes/PlayScene.h"


#include "Game/Factorys/SceneFactory.h"

#include "Game/Scenes/TitleScene.h"
#include "Game/Scenes/GameOverScene.h"

// �X�e�[�g
#include "Interface/IState.h"
#include "Game/States/SceneStates/FadeStates/FadeInState.h"
#include "Game/States/SceneStates/FadeStates/FadeOutState.h"
#include "Game/States/SceneStates/TitleMainState.h"

// �t�F�[�h�I�u�W�F�N�g�ԍ�
const int GameClearScene::FADE_OBJECT_NUMBER = 5;

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameClearScene::GameClearScene()
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
GameClearScene::~GameClearScene() {}


/// <summary>
/// ����������
/// </summary>
void GameClearScene::Initialize()
{
	// ���[�g�̏���������
	m_root->Initialize();

	// �I�u�W�F�N�g�̍쐬
	SceneFactory::CreateGameClearScene(m_root);

	// �X�e�[�g�̍쐬
	this->CreateStates();
}

/// <summary>
/// �X�^�[�g����
/// </summary>
void GameClearScene::Start()
{
	// �X�e�[�g�X�^�[�g����
	m_currentState->PreUpdate();
}

/// <summary>
/// �X�V��������
/// </summary>
void GameClearScene::Update()
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

void GameClearScene::Render()
{
	// �`�揈�����s��
	m_commonResources->GetRenderer()->Render();
}

/// <summary>
/// �I������
/// </summary>
void GameClearScene::Finalize() {}

/// <summary>
/// �X�e�[�g��؂�ւ���
/// </summary>
/// <param name="newState">���̃X�e�[�g</param>
void GameClearScene::ChangeState(IState* newState)
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
void GameClearScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::SceneMessageID::FADE_OUT:

			break;
		case Message::SceneMessageID::FADE_OUT_CANGE_MENU_SCENE:

			// ���̃V�[���̏������s��
			SceneManager::GetInstance()->PrepareScene<GameOverScene>();

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
void GameClearScene::CreateStates()
{
	// �t�F�[�h�C���X�e�[�g�쐬 ����������
	m_fadeInState = std::make_unique<FadeInState>(FADE_OBJECT_NUMBER);
	m_fadeInState->Initialize();

	// �^�C�g���V�[�����C���X�e�[�g�쐬�@����������
	m_titleMainState = std::make_unique<TitleMainState>();
	m_titleMainState->Initialize();

	// �t�F�[�h�A�E�g�X�e�[�g�쐬�@����������
	m_fadeOutState = std::make_unique<FadeOutState>(FADE_OBJECT_NUMBER);
	m_fadeOutState->Initialize();

	// �����X�e�[�g��ݒ�
	m_currentState = m_fadeInState.get();
}