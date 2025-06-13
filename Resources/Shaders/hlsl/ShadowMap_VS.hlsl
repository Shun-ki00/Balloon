#include "Common.hlsli"

// �V���h�E�}�b�v�̒��_�V�F�[�_���͗p
struct VS_SM_Input
{
    float4 Position : SV_POSITION;
};

float4 main(VS_SM_Input input) : SV_POSITION
{
    // �o�͗p
    float4 output;
    
    output = mul(input.Position, WorldViewProj);
    
    return output;
}