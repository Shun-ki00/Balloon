// ============================================
// 
// ファイル名: CameraSystem.h
// 概要: CameraSystem.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/ICamera.h"
#include "Interface/IObject.h"

class Transform;
class BlendingCamera;
class CommonResources;
class Root;

class CameraSystem : public IObject
{
public:
	// オブジェクトのアクティブ設定
	void SetIsActive(const bool& isActive) { m_isActive = isActive; }
	// オブジェクトのアクティブ状態を取得
	bool GetIsActive() const { return m_isActive; }

	// オブジェクト番号を取得する
	int GetObjectNumber() const { return m_objectNumber; }

	// オブジェクトIDを取得する
	IObject::ObjectID GetObjectID() const { return m_objectID; }
	// Transformを取得する
	Transform* GetTransform() const { return m_transform.get(); }

	// 親オブジェクトを取得する
	IObject* GetParent() const { return m_parent; }

	// カメラを追加する
	void Attach(std::unique_ptr<ICamera> camera);
	// カメラを変更する
	void ChangeCamera(int index, float time);

public:

	// コンストラクタ
	CameraSystem(Root* root, IObject* parent);
	// デストラクタ
	~CameraSystem() override = default;

public:

	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 後処理を行う
	void Finalize() override;

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageData messageData) override;
	// キーが押下げられたら通知する
	void OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key) override;

private:

	// 共有リソース
	CommonResources* m_commonResources;

	// カメラ番号
	int m_cameraIndex;

	// 状態
	bool m_isActive;
	// オブジェクトID
	IObject::ObjectID m_objectID;
	// オブジェクト番号
	int m_objectNumber;
	// 親オブジェクト
	IObject* m_parent;
	// Transform
	std::unique_ptr<Transform> m_transform;

	// 現在のカメラ
	ICamera* m_currentCamera;

	// 遷移中のカメラ
	std::unique_ptr<BlendingCamera> m_blendingCamera;

	// カメラ
	std::unordered_map<int, std::unique_ptr<ICamera>> m_virtualCameras;
};