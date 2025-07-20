// ============================================
// 
// �t�@�C����: PlayScene.cpp
// �T�v: �v���C�V�[��
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/PlayScene.h"
#include "Interface/IObject.h"
#include "Interface/IScene.h"
#include "Game/Cameras/DebugCamera.h"
#include "Game/Node/Root.h"
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/EnemyFactory.h"
#include "Game/Message/KeyboardMessenger.h"
#include "Game/Parameters/Parameters.h"
#include "Game/SteeringBehavior/WindBehavior.h"
#include "Game/AmbientLight/AmbientLight.h"
#include "Game/Particle/ParticleEmitter.h"
#include "Game/Factorys/EffectFactory.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/States/SceneStates/FadeStates/FadeInState.h"
#include "Game/States/SceneStates/FadeStates/FadeOutState.h"
#include "Game/States/SceneStates/PlayMainState.h"
#include "Game/States/SceneStates/CountdownState.h"
#include "Game/Scenes/GameClearScene.h"
#include "Game/Scenes/GameOverScene.h"
#include "Game/Factorys/SceneFactory.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayScene::PlayScene()
	:
	m_parameters{},
	m_commonResources{},
	m_root{},
	m_debugCamera{},
	m_currentState{},
	m_fadeInState{},
	m_countdownState{},
	m_playMainState{},
	m_fadeOutState{}
{
	m_commonResources  = CommonResources::GetInstance();
	m_parameters       = Parameters::GetInstance();
	m_root             = Root::GetInstance();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayScene::~PlayScene()
{

}

/// <summary>
/// ����������
/// </summary>
void PlayScene::Initialize()
{
	// �f�o�b�O�J����
	m_debugCamera = std::make_unique<DebugCamera>();
	m_debugCamera->Initialize(1280, 720);

	m_root->Initialize();

	// �I�u�W�F�N�g���쐬����
	SceneFactory::CreatePlayScene(m_root);

	// �V�[���̃X�e�[�g�쐬
	this->CreateState();
}

/// <summary>
/// �J�n����
/// </summary>
void PlayScene::Start()
{
	// BGM���Đ�����
	AudioManager::GetInstance()->PlayBgm(XACT_WAVEBANK_SOUNDS::XACT_WAVEBANK_SOUNDS_PLAYSCENE, 1.0f);

	m_currentState->PreUpdate();

	// �A�j���[�V�����J�n
	ObjectMessenger::GetInstance()->Dispatch(IObject::ObjectID::PLAYER_ICON_UI, { Message::MessageID::PLAY_PLAYER_ICON_ANIMATION });
}

/// <summary>
/// �X�V����
/// </summary>
void PlayScene::Update()
{
	const float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// �ʒm���s��
	KeyboardMessenger::GetInstance()->Dispatch();

	m_currentState->Update(elapsedTime);

	// �J�������X�V
	m_debugCamera->Update();
	m_commonResources->SetViewMatrix(m_debugCamera->GetViewMatrix());
	m_commonResources->SetCameraTransform(m_debugCamera->GetTransform());

	m_root->Update(elapsedTime);
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayScene::Render()
{
	m_commonResources->GetRenderer()->Render();
}

/// <summary>
/// �I������
/// </summary>
void PlayScene::Finalize()
{

}

/// <summary>
/// �X�e�[�g��ύX
/// </summary>
/// <param name="newState">���̃X�e�[�g</param>
void PlayScene::ChangeState(IState* newState)
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
void PlayScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::SceneMessageID::FADE_OUT:
			break;
		case Message::SceneMessageID::FADE_OUT_CANGE_GAME_CLEAR_SCENE:
			// �X�e�[�g��؂�ւ���
			this->ChangeState(m_fadeOutState.get());
			// ���̃V�[���̏������s��
			SceneManager::GetInstance()->PrepareScene<GameClearScene>();
			break;
		case Message::SceneMessageID::FADE_OUT_CANGE_GAME_OVER_SCENE:
			// �X�e�[�g��؂�ւ���
			this->ChangeState(m_fadeOutState.get());
			// ���̃V�[���̏������s��
			SceneManager::GetInstance()->PrepareScene<GameOverScene>();
			break;
		case Message::SceneMessageID::MAIN:
			// �X�e�[�g��؂�ւ���
			this->ChangeState(m_countdownState.get());
			break;
		case Message::SceneMessageID::PLAY_MAIN_STATE:
			this->ChangeState(m_playMainState.get());
			break;
		default:
			break;
	}
}

/// <summary>
/// �V�[���̃X�e�[�g�쐬
/// </summary>
void PlayScene::CreateState()
{
	// �t�F�[�h�C���X�e�[�g�쐬 ����������
	m_fadeInState = std::make_unique<FadeInState>(0);
	m_fadeInState->Initialize();

	// �J�E���g�_�E���X�e�[�g
	m_countdownState = std::make_unique<CountdownState>();
	m_countdownState->Initialize();

	// �v���C�V�[�����C���X�e�[�g�쐬�@����������
	m_playMainState = std::make_unique<PlayMainState>();
	m_playMainState->Initialize();

	// �t�F�[�h�A�E�g�X�e�[�g�쐬�@����������
	m_fadeOutState = std::make_unique<FadeOutState>(Message::MessageData{ Message::MessageID::FADE_OUT,0,1.0f ,false });
	m_fadeOutState->Initialize();

	// �����X�e�[�g��ݒ�
	m_currentState = m_fadeInState.get();
}

