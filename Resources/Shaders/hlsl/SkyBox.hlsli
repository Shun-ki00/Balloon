

// ワールド・ビュー・射影行列を格納する定数バッファ
cbuffer SkyBoxConstBuffer : register(b0)
{
    matrix matWorld;
    matrix matView;
    matrix matProj;
    float4 dayProgress;
};

// 頂点シェーダ入力用
struct VS_Input
{
    float3 positionOS : SV_Position;
};

// ピクセルシェーダ入力用
struct PS_Input
{
    float4 positionCS : SV_POSITION;
    float3 texcoord : TEXCOORD;
};