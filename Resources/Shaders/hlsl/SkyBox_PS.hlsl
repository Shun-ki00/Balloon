#include "SkyBox.hlsli"

TextureCube cubeMap : register(t0);
TextureCube eveningCubeMap : register(t1);

SamplerState Sample : register(s0);

float4 main(PS_Input input) : SV_TARGET
{
    float4 color = cubeMap.Sample(Sample, normalize(input.texcoord));
    float4 color2 = eveningCubeMap.Sample(Sample, normalize(input.texcoord));
    
    float4 finalColor = lerp(color, color2, dayProgress.x);
    
    return finalColor;
}