#include "UI.hlsli"

// テクスチャ
Texture2D tex : register(t0);
Texture2D ruleTex : register(t1);

// サンプラー
SamplerState sam : register(s0);

// メインのピクセルシェーダー
float4 main(PS_INPUT input) : SV_Target
{  
   // スプライトシートの分割数（横方向）
    float spriteCountX = 11.0f; // 横に10分割 (0 9とコロン)
    float spriteWidth = 1.0f / spriteCountX; // 各スプライトの幅

    // 各セグメント (0 5) を計算
    float segment = input.uv.x * 5.0f; // 0 5の範囲
    int segmentIndex = int(segment); // 0, 1, 2, 3, 4 に対応
    float segmentOffset = frac(segment); // 各セグメント内での位置 (0 1)
    
    // rect から値を取得
    float digit = input.rect[segmentIndex - step(2.5f, segmentIndex) ];
    // コロン（セグメント2）の場合だけ固定値を設定
    digit = lerp(digit, 10.0f, step(2.0f, segmentIndex) * step(segmentIndex, 2.5f));

    // UV座標を計算
    float2 uv;
    uv.x = digit / spriteCountX + (segmentOffset * spriteWidth);
    uv.y = input.uv.y;

    // スプライトの色を取得
    float4 color = tex.Sample(sam, uv);

    return color;
}