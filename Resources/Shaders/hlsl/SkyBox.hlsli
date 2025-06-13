

// ���[���h�E�r���[�E�ˉe�s����i�[����萔�o�b�t�@
cbuffer SkyBoxConstBuffer : register(b0)
{
    matrix matWorld;
    matrix matView;
    matrix matProj;
    float4 dayProgress;
};

// ���_�V�F�[�_���͗p
struct VS_Input
{
    float3 positionOS : SV_Position;
};

// �s�N�Z���V�F�[�_���͗p
struct PS_Input
{
    float4 positionCS : SV_POSITION;
    float3 texcoord : TEXCOORD;
};