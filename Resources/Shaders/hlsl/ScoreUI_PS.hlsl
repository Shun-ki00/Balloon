#include "UI.hlsli"

// �e�N�X�`��
Texture2D tex : register(t0);
SamplerState sam : register(s0);

// ���C���̃s�N�Z���V�F�[�_�[�i�X�R�A�p�j
float4 main(PS_INPUT input) : SV_Target
{
    // �X�v���C�g�V�[�g�̕������i�������j
    float spriteCountX = 10.0f; // "0123456789:" �� �S11�X�v���C�g
    float spriteWidth = 1.0f / spriteCountX;

    // �X�R�A�̌����i��F5���j
    float digitCount = 4.0f;
    float digitIndexF = input.uv.x * digitCount;
    int digitIndex = int(digitIndexF); // 0~4
    float digitOffset = frac(digitIndexF);

    // rect ����Ή����鐔���i0~9�j���擾
    float digit = input.rect[digitIndex];

    // UV���W���v�Z�i�R�����l���Ȃ��j
    float2 uv;
    uv.x = digit / spriteCountX + (digitOffset * spriteWidth);
    uv.y = input.uv.y;

    // �e�N�X�`������F���擾
    float4 color = tex.Sample(sam, uv);

    return color;
}
