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

}

void DebugScene::Start()
{
	
}

void DebugScene::Update()
{
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	m_root->Update(elapsedTime);

	// カメラを更新
	m_debugCamera->Update();
	m_commonResources->SetViewMatrix(m_debugCamera->GetViewMatrix());
	m_commonResources->SetCameraTransform(m_debugCamera->GetTransform());
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

