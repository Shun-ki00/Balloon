#include "Sea.hlsli"

// テクスチャ
Texture2D tex : register(t0);
// シャドウマップテクスチャ
Texture2D ShadowMapTexture : register(t1);
// サンプラー
SamplerState sam : register(s0);
// シャドウマップ用テクスチャサンプラー
SamplerComparisonState ShadowMapSampler : register(s1);

// マッハバンド対策
static const float SHADOW_EPSILON = 0.0005f;

float random(float2 uv)
{
    return frac(sin(dot(uv, float2(12.9898f, 78.233f))) * 43758.5453f);
}

float2 random2(float2 st)
{
    st = float2(dot(st, float2(127.1f, 311.7f)),
                dot(st, float2(269.5f, 183.3f)));
    return -1.0f + 2.0f * frac(sin(st) * 43758.5453f);
}

float perlinNoise(float2 uv)
{
    // uv座標を整数部と少数部に分割
    float2 p = floor(uv);
    float2 f = frac(uv);
    
    // fの補間関数を計算
    float2 u = f * f * (3.0 - 2.0 * f);
    
    // 隣接する4つの整数座標に対してランダム値を取得する
    float2 v00 = random2(p + float2(0, 0));
    float2 v10 = random2(p + float2(1, 0));
    float2 v01 = random2(p + float2(0, 1));
    float2 v11 = random2(p + float2(1, 1));
    
    // 補間と線形補間を使用してパーリンノイズ値を計算
    return lerp(
    lerp(dot(v00, f - float2(0, 0)), dot(v10, f - float2(1, 0)), u.x),
    lerp(dot(v01, f - float2(0, 1)), dot(v11, f - float2(1, 1)), u.x),
    u.y);
}

float FractalNoise(float2 uv)
{
    float output = 0.0f;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    
    for (float i = 0; i < fnOctaves; ++i)
    {
        output += perlinNoise(uv * frequency) * amplitude;
        amplitude *= fnPersistence;
        frequency *= 2.0f;
    }
    
    return output;
}


// 波打ち関数
void waveUV(inout float2 uv)
{
    uv.x += TessellationFactor.y * flowVelocity;    // 横移動
    uv.y += cos(TessellationFactor.y) * swingSpeed; // 縦揺れ
}


// ピクセルシェーダー本体
float4 main(PS_INPUT input) : SV_TARGET
{
    float2 uv = input.uv;

// ランダムなオフセットスケール（必要に応じて調整）
    float offsetScale = 0.001f;

// 各軸ごとに異なるランダムシードを与える
    float2 offset = float2(
    random(uv),
    random(uv * TessellationFactor.y)
    ) * offsetScale;

    uv += offset;
       
    offset = perlinNoise(uv);
    uv += offset;
    
    float p = FractalNoise(uv * fnUVPower);
    uv += float2(p * fnUVPath1 * cos(TessellationFactor.y), p * fnUVPath2 * sin(TessellationFactor.y));
    
    // 波打ち関数
    waveUV(uv);
    
    // テクスチャをサンプリング
    float4 output = tex.Sample(sam, uv);
    
    output *= color;

    
    float4 lightPos = mul(input.positionWS, lightViewProjection);
    // 現在のピクセルがシャドウマップ上でどの位置にあたるか計算する
    float2 suv = lightPos.xy * float2(0.5f, -0.5f) + 0.5f;
    // 通常描画の深度値とライト空間の深度値を比較して影になるか調べる
    // ShadowMapTextureの該当する場所の深度値と現在のピクセルの深度値を比較して、影になるか調べる
    // shadow　0.0f：影がある、1.0f：影がない
    float shadow = ShadowMapTexture.SampleCmpLevelZero(
        ShadowMapSampler, suv, lightPos.z - SHADOW_EPSILON);
    
    output.rgb *= lerp(lightAmbient, float3(1.0f, 1.0f, 1.0f), shadow);
    
    output.a = 0.7f;
    
    return output;
}