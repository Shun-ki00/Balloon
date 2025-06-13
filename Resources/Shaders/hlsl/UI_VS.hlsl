#include "UI.hlsli"

// ���_�V�F�[�_�[
GS_INPUT main(VS_INPUT input)
{
    GS_INPUT output = (GS_INPUT)0;
    
    // ���_�ʒu��2D�X�N���[����Ԃɕϊ�
    output.position = float4(input.position.xy, 0.0f, 1.0f);
    
    // ���_�J���[��ݒ�
    output.color = input.color;
    
    // X��������]�p�x�Ƃ��ė��p
    output.rotate = input.rotate;
    
    // �e�N�X�`���T�C�Y��ݒ�
    output.size = input.size;
    
    // ��`����n��
    output.rect = input.rect;

    // ���[���摜�ݒ����n��
    output.rule = input.rule;

    return output;
}