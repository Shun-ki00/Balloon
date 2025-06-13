// ============================================
// 
// ファイル名: TitleScene.cpp
// 概要: タイトルのシーン
// 
// 製作者 : 清水駿希
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

// ステート
#include "Interface/IState.h"
#include "Game/States/SceneStates/FadeStates/FadeInState.h"
#include "Game/States/SceneStates/FadeStates/FadeOutState.h"
#include "Game/States/SceneStates/TitleMainState.h"

/// <summary>
/// コンストラクタ
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
	// インスタンスを取得する
	m_commonResources  = CommonResources::GetInstance();
	m_parameters       = Parameters::GetInstance();
	m_root             = Root::GetInstance();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene() {}


/// <summary>
/// 初期化処理
/// </summary>
void TitleScene::Initialize()
{
	// ルートの初期化処理
	m_root->Initialize();

	// オブジェクトの作成
	this->CreateObjects();
	// UIオブジェクトの作成
	this->CreateUiObjects();
	// カメラの作成
	this->CreateCameras();

	// ステートの作成
	this->CreateStates();
}

/// <summary>
/// スタート処理
/// </summary>
void TitleScene::Start()
{
	// タイトルロゴのアニメーションを行う
	ObjectMessenger::GetInstance()->Dispatch(1, Message::MessageID::TITLE_LOGO_ANIMATION);
	// スタートテキストのアニメーションを行う
	ObjectMessenger::GetInstance()->Dispatch(2, Message::MessageID::START_TEXT_ANIMATION);

	// ステートスタート処理
	m_currentState->PreUpdate();
}

/// <summary>
/// 更新処理する
/// </summary>
void TitleScene::Update()
{
	// 経過時間を取得する
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// シーンステートの更新処理
	m_currentState->Update(elapsedTime);

	// ルートの更新処理
	m_root->Update(elapsedTime);
}

void TitleScene::Render()
{
	// 描画処理を行う
	m_commonResources->GetRenderer()->Render();
}

/// <summary>
/// 終了処理
/// </summary>
void TitleScene::Finalize() {}

/// <summary>
/// ステートを切り替える
/// </summary>
/// <param name="newState">次のステート</param>
void TitleScene::ChangeState(IState* newState)
{
	// 終了処理
	m_currentState->PostUpdate();

	// ステートを切り替える
	m_currentState = newState;

	// スタート処理
	m_currentState->PreUpdate();
}

/// <summary>
/// メッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージデータ</param>
void TitleScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::SceneMessageID::FADE_OUT:

			break;
		case Message::SceneMessageID::FADE_OUT_CANGE_MENU_SCENE:

			// 次のシーンの準備を行う
			SceneManager::GetInstance()->PrepareScene<PlayScene>();

			// ステートを切り替える
			this->ChangeState(m_fadeOutState.get());

			break;		
		case Message::SceneMessageID::MAIN:

			// ステートを切り替える
			this->ChangeState(m_titleMainState.get());

			break;
		default:
			break;
	}
}


/// <summary>
/// オブジェクトの作成
/// </summary>
void TitleScene::CreateObjects()
{
	// プレイヤー
	m_root->Attach(PlayerFactory::CreatePlayer(m_root,
		{ 2.7f , -0.5f ,-1.5f }, {0.0f ,-45.0f, 0.0f}, DirectX::SimpleMath::Vector3::One * 0.1f, true));
}


/// <summary>
/// UIオブジェクトの作成
/// </summary>
void TitleScene::CreateUiObjects()
{
	// タイトルロゴ
	std::unique_ptr<IObject> logo = std::make_unique<TitleLogoUI>(m_root, nullptr, IObject::ObjectID::TITLE_LOGO_UI,
		DirectX::SimpleMath::Vector3{ 400.0f , -300.0f ,0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One, Message::MessageID::NONE);
	ObjectMessenger::GetInstance()->Register(1, logo.get());
	logo->Initialize();
	m_root->Attach(std::move(logo));

	// スタートテキスト
	std::unique_ptr<IObject> startText = std::make_unique<StartTextUI>(m_root, nullptr, IObject::ObjectID::START_TEXT_UI,
		DirectX::SimpleMath::Vector3{ 400.0f , 400.0f ,0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::Zero, Message::MessageID::NONE);
	ObjectMessenger::GetInstance()->Register(2, startText.get());
	startText->Initialize();
	m_root->Attach(std::move(startText));

	// フェードオブジェクト
	std::unique_ptr<IObject> fade = std::make_unique<Fade>(m_root, nullptr, IObject::ObjectID::FADE,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One, Message::MessageID::NONE);
	ObjectMessenger::GetInstance()->Register(3, fade.get());
	fade->Initialize();
	m_root->Attach(std::move(fade));
}


/// <summary>
/// カメラの作成
/// </summary>
void TitleScene::CreateCameras()
{
	// カメラの作成をする
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Backward ,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Down, DirectX::XMConvertToRadians(30.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(10.0f)))
	);

	// カメラシステムをアタッチする
	m_root->Attach(CameraFactory::CreateCameraSystem(m_root, std::move(cameras)));
}


/// <summary>
///	シーンのステートの作成
/// </summary>
void TitleScene::CreateStates()
{
	// フェードインステート作成 初期化処理
	m_fadeInState = std::make_unique<FadeInState>(3);
	m_fadeInState->Initialize();

	// タイトルシーンメインステート作成　初期化処理
	m_titleMainState = std::make_unique<TitleMainState>();
	m_titleMainState->Initialize();

	// フェードアウトステート作成　初期化処理
	m_fadeOutState = std::make_unique<FadeOutState>(3);
	m_fadeOutState->Initialize();

	// 初期ステートを設定
	m_currentState = m_fadeInState.get();
}