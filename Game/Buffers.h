#pragma once
#include "pch.h"


// UIの共通頂点バッファ
struct UIVertexBuffer
{
	DirectX::SimpleMath::Vector4 position; // 中心座標（スクリーン空間）
	DirectX::SimpleMath::Vector3 rotate;   // rotate.xy = scale、rotate.z = rotation角
	DirectX::SimpleMath::Vector2 size;     // テクスチャ表示サイズ（スクリーン座標系）
	DirectX::SimpleMath::Vector4 rect;     // xy: UV offset, zw: UV scale
	DirectX::SimpleMath::Vector4 color;    // RGBAカラー
	DirectX::SimpleMath::Vector4 rule;     // x: useRule, y: ruleProgress, z: inverse, w: reserved
};


// UIの定数バッファ
struct UIConstBuffer
{
	DirectX::SimpleMath::Vector2 windowSize;
	float useTexture;
	float padding0;
	DirectX::SimpleMath::Vector4 time;
};

// ライトの定数バッファ用構造体
struct DirectionalLightBuffer
{
	DirectX::XMMATRIX lightViewProjection;	// ライトの投影空間へ座標変換する行列
	DirectX::XMVECTOR lightPosition;		// ライトの位置
	DirectX::XMVECTOR lightDirection;		// ライトの方向
	DirectX::XMVECTOR lightAmbient;			// ライトの環境光
};

struct PBRLitConstantBuffer
{
	DirectX::SimpleMath::Vector4 baseColor; // 基本色
	float matallic;                         // 金属度
	float smoothness;                       // 表面の滑らかさ
	float useBaseMap;                       // ベースカラーテクスチャを使用するか
	float useNormalMap;                     // 法線マップを使用するか
};

struct AmbientLightParameters
{
	DirectX::SimpleMath::Vector3 ambientLightColor;
	float ambientLightIntensity;
};

struct SkyBoxConstBuffer
{
	DirectX::SimpleMath::Matrix worldMatrix;
	DirectX::SimpleMath::Matrix viewMatrix;
	DirectX::SimpleMath::Matrix projectionMatrix;
	DirectX::SimpleMath::Vector4 dayProgress;
};

struct ParticleConstBuffer
{
	DirectX::SimpleMath::Matrix worldMatrix;
	DirectX::SimpleMath::Matrix viewMatrix;
	DirectX::SimpleMath::Matrix projectionMatrix;
	DirectX::SimpleMath::Matrix billboardMatrix;
	DirectX::SimpleMath::Vector4 time;
};


struct WaveParams
{
	// Wave1
	float active1;
	float direction1X;
	float direction1Z;
	float amplitude1;

	float waveLength1;
	float speed1;
	float qRatio1;
	float pad1; // padding (HLSL 側と一致)

	// Wave2
	float active2;
	float direction2X;
	float direction2Z;
	float amplitude2;

	float waveLength2;
	float speed2;
	float qRatio2;
	float pad2;

	// Wave3
	float active3;
	float direction3X;
	float direction3Z;
	float amplitude3;

	float waveLength3;
	float speed3;
	float qRatio3;
	float pad3;
};