#pragma once


class RandomUtilities
{
public:

	// ランダム生成 
	static float RandomFloat(float min, float max);
	static int RandomInt(int min, int max);

	// コーン状のランダム生成
	static void GenerateConeEmissio
	(
		float coneAngleDeg,          // コーンの角度
		float radius,            // コーンの半径
		float coneHeight,            // コーンの高さ（スピード）
		bool emitFromShell,
		const DirectX::SimpleMath::Vector3& coneOrigin, // コーンの原点
		DirectX::SimpleMath::Vector3& outPosition,
		DirectX::SimpleMath::Vector3& outVelocity);

	// スフィア型のランダム
	static void GenerateSphereEmission(
		float sphereRadius,
		bool emitFromShell,
		const DirectX::SimpleMath::Vector3& center,
		float randomDirectionStrength,
		DirectX::SimpleMath::Vector3& outPosition,
		DirectX::SimpleMath::Vector3& outVelocity);
};