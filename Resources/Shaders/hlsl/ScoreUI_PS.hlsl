#include "UI.hlsli"

// テクスチャ
Texture2D tex : register(t0);
SamplerState sam : register(s0);

// メインのピクセルシェーダー（スコア用）
float4 main(PS_INPUT input) : SV_Target
{
    // スプライトシートの分割数（横方向）
    float spriteCountX = 10.0f; // "0123456789:" → 全11スプライト
    float spriteWidth = 1.0f / spriteCountX;

    // スコアの桁数（例：5桁）
    float digitCount = 4.0f;
    float digitIndexF = input.uv.x * digitCount;
    int digitIndex = int(digitIndexF); // 0~4
    float digitOffset = frac(digitIndexF);

    // rect から対応する数字（0~9）を取得
    float digit = input.rect[digitIndex];

    // UV座標を計算（コロン考慮なし）
    float2 uv;
    uv.x = digit / spriteCountX + (digitOffset * spriteWidth);
    uv.y = input.uv.y;

    // テクスチャから色を取得
    float4 color = tex.Sample(sam, uv);

    return color;
}
