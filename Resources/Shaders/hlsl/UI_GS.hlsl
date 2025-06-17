#include "UI.hlsli"

// �萔
static const uint VERTEX_COUNT = 4;

// ���_�I�t�Z�b�g
static const float4 VERTEX_OFFSET[VERTEX_COUNT] =
{
    float4(-0.5f,  0.5f, 0.0f, 1.0f), // ����
    float4( 0.5f,  0.5f, 0.0f, 1.0f), // �E��
    float4(-0.5f, -0.5f, 0.0f, 1.0f), // ����
    float4(0.5f , -0.5f, 0.0f, 1.0f)  // �E��
};

// �ˉe�ϊ��s��
matrix GetProjection(float2 screenSize)
{
    return matrix(
        4.0f / screenSize.x, 0.0f, 0.0f, 0.0f,
        0.0f, -4.0f / screenSize.y, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 1.0f
    );
}

// ��]�s��
matrix GetRotateMatrix(float angle)
{
    return matrix(
        cos(angle), -sin(angle), 0.0f, 0.0f,
        sin(angle), cos(angle), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

// �W�I���g���V�F�[�_�[
[maxvertexcount(VERTEX_COUNT)]
void main(
    point GS_INPUT input[1],
    inout TriangleStream<PS_INPUT> output
)
{
    // �s��v�Z
    matrix rot = GetRotateMatrix(input[0].rotate.z);
    matrix proj = GetProjection(windowSize);
    
    // ��]��XY�����X�P�[���Ɏg�p
    float2 scale = float2(input[0].rotate.x, input[0].rotate.y);

    for (uint i = 0; i < VERTEX_COUNT; i++)
    {
        PS_INPUT element = (PS_INPUT) 0;

        float2 size = scale * input[0].size.xy;
        float4 offset = VERTEX_OFFSET[i] * float4(size.x, size.y, 0.0f, 1.0f);

    // ���S����ɉ�]�i�␳�Ȃ��ł��̂܂܉񂷁j
        offset = mul(offset, rot);

    // �ˉe�ϊ��K�p
        float4 p = input[0].position + offset;
        p = mul(p, proj);
        element.position = p;

    // UV
        element.uv.x = 1 - (i + 1) % 2;
        element.uv.y = i >= 2 ? 0 : 1;

        element.color = input[0].color;
        element.rect = input[0].rect;
        element.rule = input[0].rule;

        output.Append(element);
    }

    output.RestartStrip();
}