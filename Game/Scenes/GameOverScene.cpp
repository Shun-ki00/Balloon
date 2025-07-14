// ============================================
// 
// �t�@�C����: GameOverScene.cpp
// �T�v: �Q�[���I�[�o�[�V�[��
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
#include "Game/Scenes/StageSelectScene.h"
#include "Game/Factorys/SceneFactory.h"
#include "Game/AmbientLight/AmbientLight.h"
#include "Interface/IState.h"
#include "Game/States/SceneStates/FadeStates/FadeInState.h"
#include "Game/States/SceneStates/FadeStates/FadeOutState.h"
#include "Game/States/SceneStates/GameOverMainState.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameOverScene::GameOverScene()
	:
	m_parameters{},
	m_commonResources{},
	m_currentState{},
	m_fadeInState{},
	m_gameOverMainState{},
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
	// �I�u�W�F�N�g�̐F��ύX
	AmbientLight::GetInstance()->SettColor({ 1.0f, 0.45f, 0.25f });
	// �C�̐F��ύX
	m_commonResources->GetSea()->SetColor({ 0.6f, 0.4f, 0.3f,1.0f });

	// �v���C���[�̓�����ύX
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER, { Message::MessageID::PLAYER_SIT_ANIMATION });
	  
	 
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

/// <summary>
/// �`�揈��
/// </summary>
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
	// ���C�g�̐F��ύX
	AmbientLight::GetInstance()->SettColor({ 0.78f, 0.89f, 0.95f });
	// �C�̐F��ύX
	m_commonResources->GetSea()->SetColor(DirectX::SimpleMath::Vector4::One);
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
		case Message::SceneMessageID::FADE_OUT_CANGE_SELECT_SCEEN:
			// �X�e�[�g��؂�ւ���
			this->ChangeState(m_fadeOutState.get());
			// ���̃V�[���̏������s��
			SceneManager::GetInstance()->PrepareScene<StageSelectScene>();
			break;		
		case Message::SceneMessageID::FADE_OUT_CANGE_PLAY_SCENE:
			// �X�e�[�g��؂�ւ���
			this->ChangeState(m_fadeOutState.get());
			// ���̃V�[���̏������s��
			SceneManager::GetInstance()->PrepareScene<PlayScene>();
			break;
		case Message::SceneMessageID::MAIN:
			// �X�e�[�g��؂�ւ���
			this->ChangeState(m_gameOverMainState.get());
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
	m_fadeInState = std::make_unique<FadeInState>(0);
	m_fadeInState->Initialize();

	// �^�C�g���V�[�����C���X�e�[�g�쐬�@����������
	m_gameOverMainState = std::make_unique<GameOverMainState>();
	m_gameOverMainState->Initialize();

	// �t�F�[�h�A�E�g�X�e�[�g�쐬�@����������
	m_fadeOutState = std::make_unique<FadeOutState>(Message::MessageData{ Message::MessageID::FADE_OUT,0,1.0f ,false });
	m_fadeOutState->Initialize();

	// �����X�e�[�g��ݒ�
	m_currentState = m_fadeInState.get();
}