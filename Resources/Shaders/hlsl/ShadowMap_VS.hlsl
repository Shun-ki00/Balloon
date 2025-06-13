#include "Common.hlsli"

// シャドウマップの頂点シェーダ入力用
struct VS_SM_Input
{
    float4 Position : SV_POSITION;
};

float4 main(VS_SM_Input input) : SV_POSITION
{
    // 出力用
    float4 output;
    
    output = mul(input.Position, WorldViewProj);
    
    return output;
}