#include "Sea.hlsli"

StructuredBuffer<float4> InstanceBuffer : register(t1);


VS_OUTPUT main(VS_INPUT input, uint instanceId : SV_InstanceID)
{
    VS_OUTPUT output;

    // オフセット値を座標に加算して渡す
    float4 offset = InstanceBuffer[instanceId];
    output.position = input.position + offset;
    // UV座標をそのまま渡す
    output.uv = input.uv;

    return output;
}