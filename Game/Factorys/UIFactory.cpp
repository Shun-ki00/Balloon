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
/// フェードオブジェクトの作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期位置</param>
/// <param name="initialRotation">初期回転</param>
/// <param name="initialScale">初期スケール</param>
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
	ObjectMessenger::GetInstance()->Register(objectID, fade->GetObjectNumber(), fade.get());
	// インスタンスを返す
	return std::move(fade);
}


/// <summary>
/// タイトルロゴUIの作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="initialRotation">初期回転角</param>
/// <param name="initialScale">初期スケール</param>
/// <returns>タイトルロゴUI</returns>
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
	ObjectMessenger::GetInstance()->Register(objectID, titleLogo->GetObjectNumber(), titleLogo.get());
	// インスタンスを返す
	return std::move(titleLogo);
}


/// <summary>
/// スタートテキストUIオブジェクトの作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>スタートテキストUI</returns>
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
	ObjectMessenger::GetInstance()->Register(objectID, startText->GetObjectNumber(), startText.get());
	// インスタンスを返す
	return std::move(startText);
}

// ===== プレイシーン =====


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
	std::unique_ptr<PlaySceneKeysGuideUI> playSceneKeysGuide = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	playSceneKeysGuide.reset(new PlaySceneKeysGuideUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	playSceneKeysGuide->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, playSceneKeysGuide->GetObjectNumber(), playSceneKeysGuide.get());
	// インスタンスを返す
	return std::move(playSceneKeysGuide);
}


/// <summary>
/// カウントダウンUIオブジェクト作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="initialRotation">初期回転角</param>
/// <param name="initialScale">初期スケール</param>
/// <returns>カウントダウンUIオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateCountdownUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<CountdownUI> countdown = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	countdown.reset(new CountdownUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	countdown->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, countdown->GetObjectNumber(), countdown.get());
	// インスタンスを返す
	return std::move(countdown);
}


/// <summary>
/// タイマーフレームUIオブジェクト作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="initialRotation">初期回転角</param>
/// <param name="initialScale">初期スケール</param>
/// <returns>タイマーフレームUIオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateTimerFrameUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<TimeFrameUI> timeFrame = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	timeFrame.reset(new TimeFrameUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	timeFrame->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, timeFrame->GetObjectNumber(), timeFrame.get());
	// インスタンスを返す
	return std::move(timeFrame);
}


/// <summary>
/// タイムUIオブジェクト作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="initialRotation">初期回転角</param>
/// <param name="initialScale">初期スケール</param>
/// <returns>タイムUIオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateTimeUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<TimeUI> time = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	time.reset(new TimeUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	time->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, time->GetObjectNumber(), time.get());
	// インスタンスを返す
	return std::move(time);
}


/// <summary>
/// メーターUIオブジェクト作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="initialRotation">初期回転角</param>
/// <param name="initialScale">初期スケール</param>
/// <returns>メーターUIオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateMeterUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<MeterUI> meter = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	meter.reset(new MeterUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	meter->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, meter->GetObjectNumber(), meter.get());
	// インスタンスを返す
	return std::move(meter);
}


/// <summary>
/// プレイヤーアイコンUIオブジェクト作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="initialRotation">初期回転角</param>
/// <param name="initialScale">初期スケール</param>
/// <returns>プレイヤーアイコンUIオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreatePlayerIconUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<PLayerIconUI> playerIcon = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	playerIcon.reset(new PLayerIconUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	playerIcon->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, playerIcon->GetObjectNumber(), playerIcon.get());
	// インスタンスを返す
	return std::move(playerIcon);
}


/// <summary>
/// 高さメーターUIオブジェクトの作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="initialRotation">初期回転角</param>
/// <param name="initialScale">初期スケール</param>
/// <returns>高さメーターUIオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateHeightMeterUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<HeightMeterUI> heightMeter = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	heightMeter.reset(new HeightMeterUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	heightMeter->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, heightMeter->GetObjectNumber(), heightMeter.get());
	// インスタンスを返す
	return std::move(heightMeter);
}



// ==== HP ゲージ ====

/// <summary>
/// HPUIの作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="initialRotation">初期回転角</param>
/// <param name="initialScale">初期スケール</param>
/// <returns>HPUIオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateHPUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<HPUI> hp = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	hp.reset(new HPUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	hp->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, hp->GetObjectNumber(), hp.get());
	// インスタンスを返す
	return std::move(hp);
}


/// <summary>
/// HP フレームUIオブジェクト作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="initialRotation">初期回転角</param>
/// <param name="initialScale">初期スケール</param>
/// <returns>HP フレームオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateHPFrameUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<HPFrameUI> hpFrame = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	hpFrame.reset(new HPFrameUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	hpFrame->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, hpFrame->GetObjectNumber(), hpFrame.get());
	// インスタンスを返す
	return std::move(hpFrame);
}


/// <summary>
/// HP ゲージUIオブジェクト作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="initialRotation">初期回転角</param>
/// <param name="initialScale">初期スケール</param>
/// <returns>HP ゲージUIオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateHPGaugeUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<HPGaugeUI> hpGauge = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	hpGauge.reset(new HPGaugeUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	hpGauge->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, hpGauge->GetObjectNumber(), hpGauge.get());
	// インスタンスを返す
	return std::move(hpGauge);
}



// ==== 風船　大きさゲージ ====

/// <summary>
/// 風船HPUIオブジェクト作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>風船HPUIオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateBalloonHPUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<BalloonHPUI> balloonHp = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	balloonHp.reset(new BalloonHPUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	balloonHp->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, balloonHp->GetObjectNumber(), balloonHp.get());
	// インスタンスを返す
	return std::move(balloonHp);
}


/// <summary>
///　風船HPフレームUIオブジェクト作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>風船HPフレームUIオブジェクト</returns>
std::unique_ptr<IObject> UIFactory::CreateBalloonFrameUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<BalloonFrameUI> balloonFrame = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	balloonFrame.reset(new BalloonFrameUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	balloonFrame->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, balloonFrame->GetObjectNumber(), balloonFrame.get());
	// インスタンスを返す
	return std::move(balloonFrame);
}


/// <summary>
/// 風船HP ゲージUIオブジェクト作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <returns>風船HP ゲージUIオブジェクト作成</returns>
std::unique_ptr<IObject> UIFactory::CreateBalloonGaugeUI(
	IObject* parent,
	const IObject::ObjectID& objectID,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	std::unique_ptr<BalloonGaugeUI> balloonGauge = nullptr;

	// 回転をクォータニオンに変換
	DirectX::SimpleMath::Quaternion rotation =
		UIFactory::ConvertToYawPitchRoll(initialRotation);

	// インスタンス生成
	balloonGauge.reset(new BalloonGaugeUI(parent, objectID, initialPosition, rotation, initialScale));
	// 初期化処理
	balloonGauge->Initialize();
	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(objectID, balloonGauge->GetObjectNumber(), balloonGauge.get());
	// インスタンスを返す
	return std::move(balloonGauge);
}


// ==== リザルトシーン ====

/// <summary>
/// リザルトシーンのテキストUIオブジェクト作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="initialRotation">初期回転角</param>
/// <param name="initialScale">初期スケール</param>
/// <param name="textId">テキストID</param>
/// <returns>リザルトシーンのテキストUIオブジェクト</returns>
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
	resultButtonText.reset(new ResultButtonTextUI(Root::GetInstance(), parent, objectID, initialPosition, rotation, initialScale, textId));
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
/// リザルトシーン操作説明UIオブジェクト作成
/// </summary>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="initialPosition">初期座標</param>
/// <param name="initialRotation">初期回転角</param>
/// <param name="initialScale">初期スケール</param>
/// <returns>リザルトシーン操作説明UIオブジェクト</returns>
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