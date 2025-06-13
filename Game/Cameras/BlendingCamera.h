#pragma once
#include "Interface/ICamera.h"
#include "Framework/Tween/Tween.h"

class Transform;

class BlendingCamera : public ICamera
{

public:
	// Transformを取得する
	Transform* GetTransform() const override { return m_transform.get(); }
	// ビュー行列を取得する
	DirectX::SimpleMath::Matrix GetViewMatrix() const override { return m_viewMatrix; }

	// 遷移を開始する
	void StartBlending(Transform* currentCamera, Transform* nextCamera, float t , Tween::EasingType easingType);
	// 遷移中かどうか取得する
	bool GetisBlending() const { return m_isBlending; }

public:
	// コンストラクタ
	BlendingCamera();
	// デストラクタ
	~BlendingCamera() = default;

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(const float& elapsedTime);
	// ビュー行列の作成
	DirectX::SimpleMath::Matrix CalculateViewMatrix();

private:

	// 遷移中かどうか
	bool m_isBlending;

	// 遷移時間
	float m_blendingTime;

	// イージング
	Tween::EasingType m_easingType;

	// Transform
	std::unique_ptr<Transform> m_transform;

	// 遷移するカメラのTransform
	Transform* m_nextCaemraTransform;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_viewMatrix;


	// 現在の時間
	float m_elapsed;
	// 開始カメラ座標
	DirectX::SimpleMath::Vector3 m_startPosition;
	// 開始カメラターゲット座標
	DirectX::SimpleMath::Vector3 m_startTargetPosition;
};
