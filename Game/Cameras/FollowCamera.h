#pragma once
#include "Interface/ICamera.h"
#include "Framework/Tween/Tween.h"

class Transform;

class FollowCamera : public ICamera
{

public:
	// Transformを取得する
	Transform* GetTransform() const override { return m_transform.get(); }
	// ビュー行列を取得する
	DirectX::SimpleMath::Matrix GetViewMatrix() const override { return m_viewMatrix; }

public:
	// コンストラクタ
	FollowCamera(Transform* target,DirectX::SimpleMath::Vector3 distance);
	// デストラクタ
	~FollowCamera() = default;

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

	// 追尾するオブジェクトのTransform
	Transform* m_targetTransform;
	// 距離
	DirectX::SimpleMath::Vector3 m_distance;

};
