// ============================================
// 
// ファイル名: StageSelectUI.cpp
// 概要: プレイヤーアイコンUIオブジェクト
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/UIObjects/StageSelectUI.h"
#include "Framework/CommonResources.h"
// リソース
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Game/Factorys/UIFactory.h"
#include "Framework/Tween/TweenManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="root">ルートオブジェクト</param>
/// <param name="parent">親オブジェクト</param>
/// <param name="objectID">オブジェクトID</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
/// <param name="messageID">メッセージID</param>
StageSelectUI::StageSelectUI(IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale)
	:
	// 基底クラス
	UIObject(),
	m_commonResources{},
	m_isActive(true),
	m_objectNumber(Root::GetInstance()->GetObjectNumber() + UIObject::GetNumber()),
	m_objectID(objectID),
	m_parent(parent),
	m_transform{},
	m_stageIndex{},
	m_isCoolTime{},
	m_currentTime{}
{
	// 共有リソースのインスタンスを取得する
	m_commonResources = CommonResources::GetInstance();

	// Transformを作成
	m_transform = std::make_unique<Transform>();

	// 初期座標設定
	m_transform->SetLocalPosition(position);
	// 初期回転設定
	m_transform->SetLocalRotation(rotation);
	// 初期スケール設定
	m_transform->SetLocalScale(scale);

	// 親がいる場合親を設定
	if (parent != nullptr)
		m_transform->SetParent(parent->GetTransform());
}

/// <summary>
/// 初期化処理
/// </summary>
void StageSelectUI::Initialize()
{
	// ステージセレクトフレームを三つ用意
	for (int i = 0; i < 3; i++)
	{
		this->Attach(UIFactory::CreateStageSelectFrameUI(
			this, IObject::ObjectID::STAGE_SELECT_FRAME_UI,
			DirectX::SimpleMath::Vector3::Right * ((i * 600.0f) - 600.0f),
			DirectX::SimpleMath::Vector3::Zero,
			DirectX::SimpleMath::Vector3::One,i
		));
	}

	m_childs[m_stageIndex]->GetTransform()->SetLocalScale(DirectX::SimpleMath::Vector3::One * 1.2f);

	m_isCoolTime = true;
	m_currentTime = 0.5f;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void StageSelectUI::Update(const float& elapsedTime)
{
	// クールタイム更新
	if (m_isCoolTime)
	{
		m_currentTime -= elapsedTime;
		if (m_currentTime <= 0.0f)
		{
			m_isCoolTime = false;
			m_currentTime = 0.5f;
		}
			
	}

	// Transformの更新処理
	m_transform->Update();

	// 子オブジェクトの更新処理
	for (const auto& child : m_childs)
	{
		child->Update(elapsedTime);
	}
}

/// <summary>
/// 終了処理
/// </summary>
void StageSelectUI::Finalize() {}


/// <summary>
/// オブジェクトをアタッチする
/// </summary>
/// <param name="object">追加オブジェクト</param>
void StageSelectUI::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// オブジェクトを削除する
/// </summary>
/// <param name="object">削除するオブジェクト</param>
void StageSelectUI::Detach(std::unique_ptr<IObject> object)
{

}


/// <summary>
/// メッセンジャーを通知する
/// </summary>
/// <param name="messageData">メッセージデータ</param>
void StageSelectUI::OnMessegeAccepted(Message::MessageData messageData)
{
	UNREFERENCED_PARAMETER(messageData);
}

/// <summary>
/// キーボードのメッセージを通知する
/// </summary>
/// <param name="type">キータイプ</param>
/// <param name="key">キー</param>
void StageSelectUI::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	if (m_isCoolTime) return;

	switch (key)
	{
		case DirectX::Keyboard::Keys::Left:

			m_isCoolTime = true;

			// すべてのTweenを止める
			TweenManager::GetInstance()->Stop();

			// 現在のフレームを小さくする
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOMoveZ(0.0f, 0.4f);
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One ,0.4f).SetEase(Tween::EasingType::EaseInBack);

			m_stageIndex--;
			if (m_stageIndex < 0)
				m_stageIndex = 2;

			// 次のフレームを大きくする
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One * 1.2f, 0.4f).SetEase(Tween::EasingType::EaseInOutQuart);
			// 次のフレームが大きくなったら回転するアニメーションスタート
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOMoveZ(10.0f, 0.4f).SetDelay(0.4f).OnComplete([this] {
				m_childs[m_stageIndex]->GetTransform()->GetTween()->DOMoveZ(-10.0f, 0.4f).SetLoops(100000,Tween::LoopType::Yoyo);
				});


			break;

		case DirectX::Keyboard::Keys::Right:

			m_isCoolTime = true;

			// すべてのTweenを止める
			TweenManager::GetInstance()->Stop();

			// 現在のフレームを小さくする
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One, 0.4f).SetEase(Tween::EasingType::EaseInBack);
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOMoveZ(0.0f, 0.4f);

			m_stageIndex++;
			if (m_stageIndex > 2)
				m_stageIndex = 0;

			// 次のフレームを大きくする
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One * 1.2f, 0.4f).SetEase(Tween::EasingType::EaseInOutQuart);
			// 次のフレームが大きくなったら回転するアニメーションスタート
			m_childs[m_stageIndex]->GetTransform()->GetTween()->DOMoveZ(10.0f, 0.4f).SetDelay(0.4f).OnComplete([this] {
				m_childs[m_stageIndex]->GetTransform()->GetTween()->DOMoveZ(-10.0f, 0.4f).SetLoops(100000, Tween::LoopType::Yoyo);
				});
			break;
		default:
			break;
	}
}

