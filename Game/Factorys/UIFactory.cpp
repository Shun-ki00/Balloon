#include "pch.h"
#include "Interface/IObject.h"
#include "Game/Message/Message.h"
#include "Game/Factorys/UIFactory.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Message/KeyboardMessenger.h"
// オブジェクト
#include "Game/Node/Root.h"
#include "Game/Fade/Fade.h"
#include "Game/UIObjects/TitleLogoUI.h"
#include "Game/UIObjects/StartTextUI.h"
#include "Game/UIObjects/ResultButtonTextUI.h"
#include "Game/UIObjects/ResultTextUI.h"
#include "Game/UIObjects/ResultSceneKeyGuideUI.h"
#include "Game/UIObjects/ResultSceneButtons.h"
#include "Game/UIObjects/HPUI.h"
#include "Game/UIObjects/HPFrameUI.h"
#include "Game/UIObjects/HPGaugeUI.h"
#include "Game/UIObjects/BalloonHPUI.h"
#include "Game/UIObjects/BalloonFrameUI.h"
#include "Game/UIObjects/BalloonGaugeUI.h"
#include "Game/UIObjects/PLayerIconUI.h"
#include "Game/UIObjects/HeightMeterUI.h"
#include "Game/UIObjects/MeterUI.h"
#include "Game/UIObjects/PlaySceneKeysGuideUI.h"
#include "Game/UIObjects/TimeFrameUI.h"
#include "Game/UIObjects/CountdownUI.h"
#include "Game/UIObjects/TimeUI.h"


/// <summary>
/// フェードオブジェクトを作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>フェードオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateFade(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<Fade> fade = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	fade.reset(new Fade(Root::GetInstance(), parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	fade->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::FADE , fade->GetObjectNumber(), fade.get());
	// インスタンスを返す
	return std::move(fade);
}


/// <summary>
/// タイトルロゴUIオブジェクトの作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>フェードオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateTitleLogoUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<TitleLogoUI> titleLogo = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	titleLogo.reset(new TitleLogoUI(Root::GetInstance(), parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	titleLogo->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::TITLE_LOGO_UI, titleLogo->GetObjectNumber(), titleLogo.get());
	// インスタンスを返す
	return std::move(titleLogo);
}


/// <summary>
/// プレイヤーアイコンの作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>フェードオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreatePlayerIconUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<PLayerIconUI> titleLogo = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	titleLogo.reset(new PLayerIconUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	titleLogo->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::TITLE_LOGO_UI, titleLogo->GetObjectNumber(), titleLogo.get());
	// インスタンスを返す
	return std::move(titleLogo);
}

/// <summary>
/// メーターの作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>フェードオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateMeterUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<MeterUI> titleLogo = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	titleLogo.reset(new MeterUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	titleLogo->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::METER_UI, titleLogo->GetObjectNumber(), titleLogo.get());
	// インスタンスを返す
	return std::move(titleLogo);
}



/// <summary>
/// 高さメーターUIオブジェクトの作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>フェードオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateHeightMeterUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<HeightMeterUI> titleLogo = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	titleLogo.reset(new HeightMeterUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	titleLogo->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::HEIGHT_METER_UI, titleLogo->GetObjectNumber(), titleLogo.get());
	// インスタンスを返す
	return std::move(titleLogo);
}


/// <summary>
/// スタートテキストUIオブジェクトの作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>フェードオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateStartTextUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<StartTextUI> startText = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	startText.reset(new StartTextUI(Root::GetInstance(), parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	startText->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::START_TEXT_UI , startText->GetObjectNumber(), startText.get());
	// インスタンスを返す
	return std::move(startText);
}


/// <summary>
/// プレイシーン操作説明UIオブジェクトの作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>フェードオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreatePlaySceneKeyGuideUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<PlaySceneKeysGuideUI> startText = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	startText.reset(new PlaySceneKeysGuideUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	startText->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, startText->GetObjectNumber(), startText.get());
	// インスタンスを返す
	return std::move(startText);
}


/// <summary>
/// リザルトシーンのテキスト
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="rotation">初期回転</param>
/// <param name="initialScale">初期スケール</param>
/// <param name="textId">テキストID</param>
/// <returns>リザルトシーンテキストオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateResultTextUI(
	IObject* parent, const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale,
	const ResultTextUI::TextID& textId)
{
	std::unique_ptr<ResultTextUI> resultText = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	resultText.reset(new ResultTextUI(Root::GetInstance(), parent, objectID, initialPosition, rotation, initialScale, textId));
	// 初期化処理
	resultText->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, resultText->GetObjectNumber(), resultText.get());
	// インスタンスを返す
	return std::move(resultText);
}


/// <summary>
/// リザルトシーンのボタンテキスト
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="rotation">初期回転</param>
/// <param name="initialScale">初期スケール</param>
/// <param name="textId">テキストID</param>
/// <returns>リザルトシーンボタンテキストオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateResultButtonText(
	IObject* parent, const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale,
	const ResultButtonTextUI::TextID& textId)
{
	std::unique_ptr<ResultButtonTextUI> resultButtonText = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	resultButtonText.reset(new ResultButtonTextUI(Root::GetInstance(), parent, objectID, initialPosition, rotation, initialScale,textId));
	// 初期化処理
	resultButtonText->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, resultButtonText->GetObjectNumber(), resultButtonText.get());
	// インスタンスを返す
	return std::move(resultButtonText);
}

/// <summary>
/// リザルトシーンのボタンテキスト
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="rotation">初期回転</param>
/// <param name="initialScale">初期スケール</param>
/// <param name="textId">テキストID</param>
/// <returns>リザルトシーンボタンテキストオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateResultSceneButtons(
	IObject* parent, const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<ResultSceneButtons> resultButtons = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	resultButtons.reset(new ResultSceneButtons(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	resultButtons->Initialize();

	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, resultButtons->GetObjectNumber(), resultButtons.get());

	// キーボードメッセンジャーに登録
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_DOWN, DirectX::Keyboard::Keys::Up, resultButtons.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_DOWN, DirectX::Keyboard::Keys::Down, resultButtons.get());

	// インスタンスを返す
	return std::move(resultButtons);
}

/// <summary>
/// スタートテキストUIオブジェクトの作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>フェードオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateResultSceneKeyGuideUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<ResultSceneKeyGuideUI> resultSceneKeyGuide = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	resultSceneKeyGuide.reset(new ResultSceneKeyGuideUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	resultSceneKeyGuide->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// インスタンスを返す
	return std::move(resultSceneKeyGuide);
}


/// <summary>
/// HPの作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>フェードオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateHPUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<HPUI> resultSceneKeyGuide = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	resultSceneKeyGuide.reset(new HPUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	resultSceneKeyGuide->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// インスタンスを返す
	return std::move(resultSceneKeyGuide);
}


/// <summary>
/// HP　フレーム作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>フェードオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateHPFrameUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<HPFrameUI> resultSceneKeyGuide = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	resultSceneKeyGuide.reset(new HPFrameUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	resultSceneKeyGuide->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// インスタンスを返す
	return std::move(resultSceneKeyGuide);
}



/// <summary>
/// HP　ゲージ作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>フェードオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateHPGaugeUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<HPGaugeUI> resultSceneKeyGuide = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	resultSceneKeyGuide.reset(new HPGaugeUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	resultSceneKeyGuide->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// インスタンスを返す
	return std::move(resultSceneKeyGuide);
}


/// <summary>
/// 風船HP作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns> 風船HP</returns>
std::unique_ptr<IObject> UIFactory::CreateBalloonHPUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<BalloonHPUI> resultSceneKeyGuide = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	resultSceneKeyGuide.reset(new BalloonHPUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	resultSceneKeyGuide->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// インスタンスを返す
	return std::move(resultSceneKeyGuide);
}


/// <summary>
///　風船HPフレーム作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>風船HPフレーム</returns>
std::unique_ptr<IObject> UIFactory::CreateBalloonFrameUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<BalloonFrameUI> resultSceneKeyGuide = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	resultSceneKeyGuide.reset(new BalloonFrameUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	resultSceneKeyGuide->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// インスタンスを返す
	return std::move(resultSceneKeyGuide);
}



/// <summary>
/// 風船HP　ゲージ作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>風船HP　ゲージ</returns>
std::unique_ptr<IObject> UIFactory::CreateBalloonGaugeUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<BalloonGaugeUI> resultSceneKeyGuide = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	resultSceneKeyGuide.reset(new BalloonGaugeUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	resultSceneKeyGuide->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// インスタンスを返す
	return std::move(resultSceneKeyGuide);
}


/// <summary>
/// タイマーフレームオブジェクト作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>風船HP　ゲージ</returns>
std::unique_ptr<IObject> UIFactory::CreateTimerFrameUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<TimeFrameUI> resultSceneKeyGuide = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	resultSceneKeyGuide.reset(new TimeFrameUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	resultSceneKeyGuide->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// インスタンスを返す
	return std::move(resultSceneKeyGuide);
}

/// <summary>
/// カウントダウンオブジェクト作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
std::unique_ptr<IObject> UIFactory::CreateCountdownUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<CountdownUI> resultSceneKeyGuide = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	resultSceneKeyGuide.reset(new CountdownUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	resultSceneKeyGuide->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// インスタンスを返す
	return std::move(resultSceneKeyGuide);
}



/// <summary>
/// カウントダウンオブジェクト作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
std::unique_ptr<IObject> UIFactory::CreateTimeUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<TimeUI> resultSceneKeyGuide = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	resultSceneKeyGuide.reset(new TimeUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	resultSceneKeyGuide->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, resultSceneKeyGuide->GetObjectNumber(), resultSceneKeyGuide.get());
	// インスタンスを返す
	return std::move(resultSceneKeyGuide);
}


























/// <summary>
/// 回転ベクトルをクォータニオンに変換する。
/// </summary>
/// <param name="rotation">回転を表すベクトル（度数法）</param>
/// <returns>変換後のクォータニオン</returns>
DirectX::SimpleMath::Quaternion UIFactory::ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation) {
	return DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(rotation.y),
		DirectX::XMConvertToRadians(rotation.x),
		DirectX::XMConvertToRadians(rotation.z)
	);
}