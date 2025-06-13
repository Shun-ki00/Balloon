
// 定数バッファ
cbuffer UIConstBuffer : register(b0)
{
    float2 windowSize : packoffset(c0);    // ウィンドウサイズ
    float useTexture  : packoffset(c0.z);  // テクスチャ使用フラグ
    float padding0 : packoffset(c0.w);
    float4 time       : packoffset(c1);    // タイム
}

// ルール情報
// X : useRuleTexture
// Y : ruleProgress
// Z : ruleInverse

// 頂点入力
struct VS_INPUT
{
    float4 position : SV_Position; // 画像中心座標
    float3 rotate   : NORMAL;      // 回転角 スケール
    float2 size     : TEXCOORD0;   // テクスチャサイズ
    float4 rect     : TEXCOORD1; // テクスチャの矩形情報
    float4 color    : COLOR;       // カラー情報
    float4 rule     : TEXCOORD2;   // ルール情報
};


// ジオメトリシェーダー入力
struct GS_INPUT
{
    float4 position : SV_Position; // 画像の中心座標
    float3 rotate   : NORMAL;      // 回転角
    float2 size     : TEXCOORD0;   // テクスチャサイズ
    float4 rect     : TEXCOORD1; // テクスチャの矩形情報
    float4 color    : COLOR;       // カラー情報
    float4 rule     : TEXCOORD2;   // ルール情報
};

// ピクセルシェーダー入力
struct PS_INPUT
{
    float4 position : SV_Position; // ピクセル位置
    float4 color    : COLOR;       // 頂点色
    float2 uv       : TEXCOORD0;   // UV座標
    float4 rect     : TEXCOORD1; // UV座標の矩形範囲
    float4 rule     : TEXCOORD2;   // ルール情報
};


