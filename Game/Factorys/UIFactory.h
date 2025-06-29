#pragma once
#include "Interface/IObject.h"
#include "Game/UIObjects/ResultButtonTextUI.h"
#include "Game/UIObjects/ResultTextUI.h"

class IObject;

class UIFactory
{
public:

	// ==== static UIオブジェクト ====

	// フェードオブジェクト
	static std::unique_ptr<IObject> CreateFade(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);
	

	// ==== タイトルシーン ====

	// タイトルロゴ
	static std::unique_ptr<IObject> CreateTitleLogoUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// スタートテキスト
	static std::unique_ptr<IObject> CreateStartTextUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// ==== ステージセレクトシーン ====

	// ステージセレクトのフレームUI
	static std::unique_ptr<IObject> CreateStageSelectFrameUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale,int stageIndex);

	// ステージセレクトテキストUI
	static std::unique_ptr<IObject> CreateStageSelectTextUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// ステージセレクトUI
	static std::unique_ptr<IObject> CreateStageSelectUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// ステージセレクト操作説明UI
	static std::unique_ptr<IObject> CreateStageSelectKeyGuideUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);


	// ==== プレイシーン ====

	// プレイシーン操作説明
	static std::unique_ptr<IObject> CreatePlaySceneKeyGuideUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// カウントダウン
	static std::unique_ptr<IObject> CreateCountdownUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// タイマーフレーム
	static std::unique_ptr<IObject> CreateTimerFrameUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// タイム
	static std::unique_ptr<IObject> CreateTimeUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// メータ　（高さ）
	static std::unique_ptr<IObject> CreateMeterUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// プレイヤーアイコン
	static std::unique_ptr<IObject> CreatePlayerIconUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// 高さメータ
	static std::unique_ptr<IObject> CreateHeightMeterUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);


	// ==== HP ゲージ ====

	// HP
	static std::unique_ptr<IObject> CreateHPUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// HP フレーム
	static std::unique_ptr<IObject> CreateHPFrameUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// HP ゲージ
	static std::unique_ptr<IObject> CreateHPGaugeUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);
	

	// ==== 風船　大きさゲージ ====

	// 風船HP
	static std::unique_ptr<IObject> CreateBalloonHPUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// 風船 フレーム
	static std::unique_ptr<IObject> CreateBalloonFrameUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// 風船 ゲージ
	static std::unique_ptr<IObject> CreateBalloonGaugeUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);
	

	// ==== リザルトシーン ====

	// リザルトテキスト
	static std::unique_ptr<IObject> CreateResultTextUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale,
		const ResultTextUI::TextID& textId);

	// リザルトシーンのボタン
	static std::unique_ptr<IObject> CreateResultButtonText(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale,
		const ResultButtonTextUI::TextID& textId);

	// リザルトシーンのボタンシステム
	static std::unique_ptr<IObject> CreateResultSceneButtons(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// リザルトシーンキーガイド
	static std::unique_ptr<IObject> CreateResultSceneKeyGuideUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

private:
	// 回転ベクトルをクォータニオンに変換する
	static DirectX::SimpleMath::Quaternion ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation);
};