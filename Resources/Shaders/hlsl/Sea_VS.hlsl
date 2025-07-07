#include "Sea.hlsli"

StructuredBuffer<float4> InstanceBuffer : register(t1);


VS_OUTPUT main(VS_INPUT input, uint instanceId : SV_InstanceID)
{
    VS_OUTPUT output;

    // �I�t�Z�b�g�l�����W�ɉ��Z���ēn��
    float4 offset = InstanceBuffer[instanceId];
    output.position = input.position + offset;
    // UV���W�����̂܂ܓn��
    output.uv = input.uv;

    return output;
}