// ============================================
// 
// �t�@�C����: GameClearScene.cpp
// �T�v: �Q�[���N���A�V�[��
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
#include "Game/Scenes/StageSelectScene.h"
#include "Game/Scenes/PlayScene.h"
#include "Interface/IState.h"
#include "Game/States/SceneStates/FadeStates/FadeInState.h"
#include "Game/States/SceneStates/FadeStates/FadeOutState.h"
#include "Game/States/SceneStates/GameClearMainState.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
GameClearScene::GameClearScene()
	:
	m_parameters{},
	m_commonResources{},
	m_currentState{},
	m_fadeInState{},
	m_gameClearMainState{},
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

	// BGM���Đ�����
	AudioManager::GetInstance()->PlayBgm(XACT_WAVEBANK_SOUNDS::XACT_WAVEBANK_SOUNDS_GAMECLEARSCENE, 1.0f);

	// �X�e�[�g�X�^�[�g����
	m_currentState->PreUpdate();
	// �v���C���[�̓�����ύX
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER, { Message::MessageID::PLAYER_CLEAR_ANIMATION });
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

/// <summary>
/// �`�揈��
/// </summary>
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
			this->ChangeState(m_gameClearMainState.get());
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
	m_fadeInState = std::make_unique<FadeInState>(0);
	m_fadeInState->Initialize();

	// �^�C�g���V�[�����C���X�e�[�g�쐬�@����������
	m_gameClearMainState = std::make_unique<GameClearMainState>();
	m_gameClearMainState->Initialize();

	// �t�F�[�h�A�E�g�X�e�[�g�쐬�@����������
	m_fadeOutState = std::make_unique<FadeOutState>(Message::MessageData{ Message::MessageID::FADE_OUT,0,1.0f ,false });
	m_fadeOutState->Initialize();

	// �����X�e�[�g��ݒ�
	m_currentState = m_fadeInState.get();
}