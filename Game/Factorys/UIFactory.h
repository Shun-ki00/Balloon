#pragma once
#include "Interface/IObject.h"
#include "Game/UIObjects/ResultButtonTextUI.h"
#include "Game/UIObjects/ResultTextUI.h"

class IObject;

class UIFactory
{
public:

	// フェードオブジェクト
	static std::unique_ptr<IObject> CreateFade(
		IObject* parent , const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// タイトルロゴ
	static std::unique_ptr<IObject> CreateTitleLogoUI(
		IObject* parent , const IObject::ObjectID& objectID,
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


	// スタートテキスト
	static std::unique_ptr<IObject> CreateStartTextUI(
		IObject* parent , const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// リザルトテキスト
	static std::unique_ptr<IObject> CreateResultTextUI(
		IObject* parent, const IObject::ObjectID& objectID,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale,
		const ResultTextUI::TextID& textId);

	// リザルトシーンのボタン
	static std::unique_ptr<IObject> CreateResultButtonText(
		IObject* parent , const IObject::ObjectID& objectID,
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


private:
	// 回転ベクトルをクォータニオンに変換する
	static DirectX::SimpleMath::Quaternion ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation);
};