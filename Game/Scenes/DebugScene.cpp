// ============================================
// 
// ファイル名: DebugScene.cpp
// 概要: デバッグ用のシーン
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/DebugScene.h"
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
#include "Framework/AudioManager.h"

#include "Game/UIObjects/TitleLogoUI.h"
#include "Game/Fade/Fade.h"
#include "Game/Factorys/UIFactory.h"
#include "Game/Factorys/CameraFactory.h"



DebugScene::DebugScene()
{
	m_commonResources  = CommonResources::GetInstance();
	m_parameters       = Parameters::GetInstance();
	m_steeringBehavior = WindBehavior::GetInstance();
	m_root             = Root::GetInstance();
}


DebugScene::~DebugScene()
{

}

void DebugScene::Initialize()
{
	// デバッグカメラ
	m_debugCamera = std::make_unique<DebugCamera>();
	m_debugCamera->Initialize(1280, 720);

	m_root->Initialize();

	m_root->Attach(PlayerFactory::CreatePlayer(m_root,
		DirectX::SimpleMath::Vector3::Up,DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.1f));

	m_root->Attach(EnemyFactory::CreateEnemy(m_root,
		DirectX::SimpleMath::Vector3::Backward + DirectX::SimpleMath::Vector3::Up, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.1f));
	
	m_root->Attach(EffectFactory::CreateEffectController(m_root ,{ ParametersID::BALLOON_EXPLOSION, ParametersID::PARTICLE  }));

	m_root->Attach(UIFactory::CreateHPUI(m_root, IObject::ObjectID::HP_UI,
		DirectX::SimpleMath::Vector3(1280.0f / 2.0f, 720.0f / 2.0f, 0.0f), DirectX::SimpleMath::Vector3::Zero, {0.6f , 0.6f ,0.0f}));




	// フレームの作成
	m_root->Attach(UIFactory::CreateBalloonFrameUI(
		m_root, IObject::ObjectID::BALLOON_HP_FRAME_UI,
		DirectX::SimpleMath::Vector3(1280.0f / 2.0f, 720.0f / 2.0f, 0.0f), DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.5f
	));
	// バルーンのゲージの作成
	m_root->Attach(UIFactory::CreateBalloonHPUI(m_root, IObject::ObjectID::HP_UI,
		DirectX::SimpleMath::Vector3(1280.0f / 2.0f, 720.0f / 2.0f + 130, 0.0f), DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
	// プレイヤーアイコンの作成
	m_root->Attach(UIFactory::CreatePlayerIconUI(m_root, IObject::ObjectID::PLAYER_ICON_UI,
		DirectX::SimpleMath::Vector3(1280.0f / 2.0f + 400.0f, 720.0f / 2.0f + 130, 0.0f), DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.4f));





	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Backward * 10,
		DirectX::SimpleMath::Quaternion::Identity));
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Forward * 5,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right , DirectX::XMConvertToRadians(45.0f))));
	cameras.emplace_back(CameraFactory::CreateFollowCaemra(
		ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER, 0)->GetTransform(),
		{0.0f ,8.0f ,8.0f}));

	m_root->Attach(CameraFactory::CreateCameraSystem(m_root, std::move(cameras)));



	AudioManager::GetInstance()->PlayBgm(XACT_WAVEBANK_SOUNDS_TITLESCENE, 3.0f);


	std::unique_ptr<IObject> logo = std::make_unique<Fade>(m_root, nullptr, IObject::ObjectID::NODE_BASE,
		DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::Zero);
	logo->Initialize();

	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::TITLE_LOGO_UI, 4, logo.get());

	 m_root->Attach(std::move(logo));



	//ObjectMessenger::GetInstance()->Dispatch(2, { Message::MessageID::BALLOON_EXPLOSION ,0,0.0f ,true });

	//ObjectMessenger::GetInstance()->Dispatch(3, { Message::MessageID::BALLOON_EXPLOSION ,2,5.0f ,true });


	//ObjectMessenger::GetInstance()->Dispatch(4, { Message::MessageID::FADE_OUT ,2,5.0f ,true });
	//ObjectMessenger::GetInstance()->Dispatch(2, { Message::MessageID::SMOKE ,0,0.0f ,true });

	//m_emitter = std::make_unique< ParticleEmitter>();
	//m_emitter->Initialize(ParametersID::PARTICLE);
	//m_commonResources->GetRenderer()->Attach(m_emitter.get());

	//m_emitter->Play();
}

void DebugScene::Start()
{
	
}

void DebugScene::Update()
{
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// 通知を行う
	KeyboardMessenger::GetInstance()->Dispatch();

	m_steeringBehavior->Update(elapsedTime);

	m_root->Update(elapsedTime);

	// カメラを更新
	m_debugCamera->Update();
	m_commonResources->SetViewMatrix(m_debugCamera->GetViewMatrix());
}

void DebugScene::Render()
{
	m_commonResources->GetRenderer()->Render();
}


void DebugScene::Finalize()
{

}

void DebugScene::ChangeState(IState* newState)
{
	(void)newState;
}

void DebugScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	(void)messageID;
}

