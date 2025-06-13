#include "UI.hlsli"

// テクスチャ
Texture2D tex : register(t0);
SamplerState sam : register(s0);

// メインのピクセルシェーダー（スコア用）
float4 main(PS_INPUT input) : SV_Target
{
    // UV座標
    float2 uv = input.uv;
    
    // 波の設定
    float waveFreq = 20.0f; // 横方向の波の細かさ
    float waveSpeed = 9.0f; // アニメーション速度
    float waveAmp = 0.2f; // 振幅の最大値（縦の揺れ幅）

    // 波の縦揺れ（uv.y に加算）
    float wave = sin(uv.x * waveFreq + time.x * waveSpeed) * waveAmp * (1.0f - input.rect.x);

    // uv.y に波を加算（実際に頂点 or ピクセルを変形）
    float2 wavyUV = uv;
    wavyUV.y += wave;
   
    // テクスチャの色を取得
    float4 col = lerp(float4(0.0f, 0.0f, 0.0f, 1.0f), tex.Sample(sam, wavyUV), useTexture);
    
    float mask = step(uv.x, input.rect.x); 
    col.a *= mask; 
    
    // 最終的な色を返す
    return col;
}
