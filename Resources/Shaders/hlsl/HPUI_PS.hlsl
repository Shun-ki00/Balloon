#include "UI.hlsli"

// �e�N�X�`��
Texture2D tex : register(t0);
SamplerState sam : register(s0);

// ���C���̃s�N�Z���V�F�[�_�[�i�X�R�A�p�j
float4 main(PS_INPUT input) : SV_Target
{
    // UV���W
    float2 uv = input.uv;
    
    // �g�̐ݒ�
    float waveFreq = 20.0f; // �������̔g�ׂ̍���
    float waveSpeed = 9.0f; // �A�j���[�V�������x
    float waveAmp = 0.2f; // �U���̍ő�l�i�c�̗h�ꕝ�j

    // �g�̏c�h��iuv.y �ɉ��Z�j
    float wave = sin(uv.x * waveFreq + time.x * waveSpeed) * waveAmp * (1.0f - input.rect.x);

    // uv.y �ɔg�����Z�i���ۂɒ��_ or �s�N�Z����ό`�j
    float2 wavyUV = uv;
    wavyUV.y += wave;
   
    // �e�N�X�`���̐F���擾
    float4 col = lerp(float4(0.0f, 0.0f, 0.0f, 1.0f), tex.Sample(sam, wavyUV), useTexture);
    
    float mask = step(uv.x, input.rect.x); 
    col.a *= mask; 
    
    // �ŏI�I�ȐF��Ԃ�
    return col;
}
