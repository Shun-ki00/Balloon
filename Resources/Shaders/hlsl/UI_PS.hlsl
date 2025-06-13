#include "UI.hlsli"
// ���[�����
// X : useRuleTexture
// Y : ruleProgress
// Z : ruleInverse

// �e�N�X�`��
Texture2D tex : register(t0);
Texture2D ruleTex : register(t1);

// �T���v���[
SamplerState sam : register(s0);

// ���[���摜�̃A���t�@�l���擾����֐�
float GetRuleAlpha(float2 uv , float4 rule)
{
    // ���[���摜����l���T���v�����O
    float4 ruleCol = ruleTex.Sample(sam, uv);

    // �A���t�@�l����`���
    float ret = lerp(0.0f, 1.0f, smoothstep(ruleCol.r, ruleCol.r + 0.1f, rule.y));

    // ���[���̔��]��K�p
    ret = (rule.z != 0) ? 1.0f - ret : ret;

    return ret;
}

// ���C���̃s�N�Z���V�F�[�_�[
float4 main(PS_INPUT input) : SV_Target
{
     // UV���W�̌v�Z
    float2 uv = input.rect.xy + (input.uv * input.rect.zw);
   
    // �e�N�X�`���̐F���擾
    float4 col = lerp(float4(0.0f,0.0f,0.0f,1.0f), tex.Sample(sam, uv), useTexture);
    
    // ���_�F����Z
    col *= input.color;

    // ���[���摜�̃A���t�@�l��K�p
    col.a *= lerp(1.0f, GetRuleAlpha(input.uv , input.rule), input.rule.x);
    
    // �ŏI�I�ȐF��Ԃ�
    return col;
}