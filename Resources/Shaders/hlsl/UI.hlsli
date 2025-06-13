
// �萔�o�b�t�@
cbuffer UIConstBuffer : register(b0)
{
    float2 windowSize : packoffset(c0);    // �E�B���h�E�T�C�Y
    float useTexture  : packoffset(c0.z);  // �e�N�X�`���g�p�t���O
    float padding0 : packoffset(c0.w);
    float4 time       : packoffset(c1);    // �^�C��
}

// ���[�����
// X : useRuleTexture
// Y : ruleProgress
// Z : ruleInverse

// ���_����
struct VS_INPUT
{
    float4 position : SV_Position; // �摜���S���W
    float3 rotate   : NORMAL;      // ��]�p �X�P�[��
    float2 size     : TEXCOORD0;   // �e�N�X�`���T�C�Y
    float4 rect     : TEXCOORD1; // �e�N�X�`���̋�`���
    float4 color    : COLOR;       // �J���[���
    float4 rule     : TEXCOORD2;   // ���[�����
};


// �W�I���g���V�F�[�_�[����
struct GS_INPUT
{
    float4 position : SV_Position; // �摜�̒��S���W
    float3 rotate   : NORMAL;      // ��]�p
    float2 size     : TEXCOORD0;   // �e�N�X�`���T�C�Y
    float4 rect     : TEXCOORD1; // �e�N�X�`���̋�`���
    float4 color    : COLOR;       // �J���[���
    float4 rule     : TEXCOORD2;   // ���[�����
};

// �s�N�Z���V�F�[�_�[����
struct PS_INPUT
{
    float4 position : SV_Position; // �s�N�Z���ʒu
    float4 color    : COLOR;       // ���_�F
    float2 uv       : TEXCOORD0;   // UV���W
    float4 rect     : TEXCOORD1; // UV���W�̋�`�͈�
    float4 rule     : TEXCOORD2;   // ���[�����
};


