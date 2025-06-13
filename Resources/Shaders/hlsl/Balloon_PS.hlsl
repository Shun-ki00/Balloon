#include "PBRLit.hlsli"

// ノーマルマップ
Texture2DArray BalloonColorTexture : register(t1);
// スカイマップ
TextureCube<float4> skyMap : register(t2);
// シャドウマップテクスチャ
Texture2D ShadowMapTexture : register(t3);


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

    // 最終的なピクセルカラーを返す
    return color;
}