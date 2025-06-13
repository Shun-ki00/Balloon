#include "UI.hlsli"

// �e�N�X�`��
Texture2D tex : register(t0);
Texture2D ruleTex : register(t1);

// �T���v���[
SamplerState sam : register(s0);

// ���C���̃s�N�Z���V�F�[�_�[
float4 main(PS_INPUT input) : SV_Target
{  
   // �X�v���C�g�V�[�g�̕������i�������j
    float spriteCountX = 11.0f; // ����10���� (0 9�ƃR����)
    float spriteWidth = 1.0f / spriteCountX; // �e�X�v���C�g�̕�

    // �e�Z�O�����g (0 5) ���v�Z
    float segment = input.uv.x * 5.0f; // 0 5�͈̔�
    int segmentIndex = int(segment); // 0, 1, 2, 3, 4 �ɑΉ�
    float segmentOffset = frac(segment); // �e�Z�O�����g���ł̈ʒu (0 1)
    
    // rect ����l���擾
    float digit = input.rect[segmentIndex - step(2.5f, segmentIndex) ];
    // �R�����i�Z�O�����g2�j�̏ꍇ�����Œ�l��ݒ�
    digit = lerp(digit, 10.0f, step(2.0f, segmentIndex) * step(segmentIndex, 2.5f));

    // UV���W���v�Z
    float2 uv;
    uv.x = digit / spriteCountX + (segmentOffset * spriteWidth);
    uv.y = input.uv.y;

    // �X�v���C�g�̐F���擾
    float4 color = tex.Sample(sam, uv);

    return color;
}