#include "PBRLit.hlsli"

// ノーマルマップ
Texture2DArray BalloonColorTexture : register(t1);
// スカイマップ
TextureCube<float4> skyMap : register(t2);
// シャドウマップテクスチャ
Texture2D ShadowMapTexture : register(t3);

// シャドウマップ用テクスチャサンプラー
SamplerComparisonState ShadowMapSampler : register(s1);

// マッハバンド対策
//#define SHADOW_EPSILON 0.0005f
static const float SHADOW_EPSILON = 0.0005f;

float4 main(PS_Input input) : SV_TARGET
{
    // ベースカラーを使用するか判定用の定数を風船のテクスチャ番号に使用
    float4 baseColor = BalloonColorTexture.Sample(Sampler, float3(input.uv, t_useBaseMap));
     
    // ノーマルマップを使用しない 
    float3 normalWS = input.normalWS;
   
    // 視線ベクトルを計算
    float3 viewDir = normalize(EyePosition - input.positionWS);
    
    // 鏡面反射光の色をサンプリング
    float3 refVec = reflect(viewDir, normalWS);
    refVec.y *= -1;
    float3 indirectSpecular = skyMap.SampleLevel(Sampler, refVec, f_smoothness * 12).rgb;
    
    // ディレクショナルライトの情報（DirectXTK の標準ライト）
    float3 lightDir = LightDirection[0]; // ライトの方向
    float3 lightColor = LightDiffuseColor[0]; // ライトの色
    
    float4 lightPos = mul(float4(input.positionWS, 1.0f), lightViewProjection);
        // 現在のピクセルがシャドウマップ上でどの位置にあたるか計算する
    float2 uv = lightPos.xy * float2(0.5f, -0.5f) + 0.5f;
    // 通常描画の深度値とライト空間の深度値を比較して影になるか調べる
    // ShadowMapTextureの該当する場所の深度値と現在のピクセルの深度値を比較して、影になるか調べる
    // shadow　0.0f：影がある、1.0f：影がない
    float shadow = ShadowMapTexture.SampleCmpLevelZero(
        ShadowMapSampler, uv, lightPos.z - SHADOW_EPSILON);

    
     // PBRのBRDFを計算
    float4 color = BRDF(
        baseColor.rgb, // ベースカラー
        f_matallic, // メタリック
        f_smoothness, // 粗さ
        normalWS, // 法線ベクトル
        viewDir, // 視線ベクトル
        lightDir, // ライトの方向
        lightColor, // ライトの色
        indirectSpecular // 環境光による間接鏡面反射
    );
    
    // シャドウ適用
    color.rgb *= lerp(lightAmbient, float3(1.0f, 1.0f, 1.0f), shadow);

    // 最終的なピクセルカラーを返す
    return color;
}