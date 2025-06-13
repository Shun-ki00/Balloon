// ============================================
// 
// �t�@�C����: DebugScene.cpp
// �T�v: �f�o�b�O�p�̃V�[��
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

#include "Game/UIObjects/TitleLogoUI.h"


PlayScene::PlayScene()
{
	m_commonResources  = CommonResources::GetInstance();
	m_parameters       = Parameters::GetInstance();
	m_root             = Root::GetInstance();
}


PlayScene::~PlayScene()
{

}

void PlayScene::Initialize()
{
	// �f�o�b�O�J����
	m_debugCamera = std::make_unique<DebugCamera>();
	m_debugCamera->Initialize(1280, 720);

	m_root->Initialize();

	m_root->Attach(PlayerFactory::CreatePlayer(m_root,
		DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Up , DirectX::SimpleMath::Vector3::One * 0.1f,true));


	std::unique_ptr<IObject> logo = std::make_unique<TitleLogoUI>(m_root, nullptr, IObject::ObjectID::NODE_BASE,
		DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One);
	logo->Initialize();

	 m_root->Attach(std::move(logo));
}

void PlayScene::Start()
{
	
}

void PlayScene::Update()
{
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// �ʒm���s��
	KeyboardMessenger::GetInstance()->Dispatch();

	// �J�������X�V
	m_debugCamera->Update();
	m_commonResources->SetViewMatrix(m_debugCamera->GetViewMatrix());


	m_root->Update(elapsedTime);
}

void PlayScene::Render()
{
	m_commonResources->GetRenderer()->Render();
}


void PlayScene::Finalize()
{

}

void PlayScene::ChangeState(IState* newState)
{
	(void)newState;
}

void PlayScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	(void)messageID;
}

