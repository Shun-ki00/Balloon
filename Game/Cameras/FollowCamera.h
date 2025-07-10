#pragma once
#include "Interface/ICamera.h"
#include "Framework/Tween/Tween.h"

class Transform;
class Object;

class FollowCamera : public ICamera
{

private:

	// ズームするために必要なターゲットの速度
	static const float SPEED_TO_ZOOM_THRESHOLD;
	// ズーム距離の補間速度
	static const float ZOOM_INTERPOLATION_SPEED;
	// ズーム倍率
	static const float ZOOM_RATIO;

	// バネの剛性
	static const float SPRING_STIFFNESS;
	// 減衰係数
	static const float SPRING_DAMPING;

public:
	// Transformを取得する
	Transform* GetTransform() const override { return m_transform.get(); }
	// ビュー行列を取得する
	DirectX::SimpleMath::Matrix GetViewMatrix() const override { return m_viewMatrix; }

public:
	// コンストラクタ
	FollowCamera(Object* target,DirectX::SimpleMath::Vector3 distance);
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

	// 追尾するオブジェクト
	Object* m_target;
	// オフセット値
	DirectX::SimpleMath::Vector3 m_distance;
	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// ズーム状態の補間係数
	float m_zoomBlend;
};
