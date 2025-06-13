#pragma once
#include "Interface/ICamera.h"
#include "Framework/Tween/Tween.h"

class Transform;

class FixedCamera : public ICamera
{

public:
	// Transformを取得する
	Transform* GetTransform() const override { return m_transform.get(); }
	// ビュー行列を取得する
	DirectX::SimpleMath::Matrix GetViewMatrix() const override { return m_viewMatrix; }

public:
	// コンストラクタ
	FixedCamera(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation);
	// デストラクタ
	~FixedCamera() = default;

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(const float& elapsedTime);
	// ビュー行列の作成
	DirectX::SimpleMath::Matrix CalculateViewMatrix();

private:

	// Transform
	std::unique_ptr<Transform> m_transform;
	// ビュー行列
	DirectX::SimpleMath::Matrix m_viewMatrix;
};
