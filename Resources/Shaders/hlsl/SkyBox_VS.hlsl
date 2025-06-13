#include "SkyBox.hlsli"


PS_Input main(VS_Input input)
{
    // �o�͍\���̂�������
    PS_Input output = (PS_Input) 0;
    
    // �I�u�W�F�N�g��� (OS) ���烏�[���h��� (WS) �֕ϊ�
    float4 position = mul(float4(input.positionOS, 1.0f), matWorld);
    
     // �r���[�s��̕��s�ړ��������[���ɂ���
    matrix SetMatView = matView;
    SetMatView._41 = 0;
    SetMatView._42 = 0;
    SetMatView._43 = 0;
    
    // ���[���h��Ԃ���r���[��Ԃ֕ϊ�
    position = mul(position, SetMatView);
    // �r���[��Ԃ���N���b�v��� (CS) �֕ϊ�
    position = mul(position, matProj);
    
    // �[�x�l���ő剻���ď�ɉ��ɕ`��
    position.z = position.w;
    
    // �o�͕ϐ��ɍ��W�ƃe�N�X�`�����W���i�[
    output.positionCS = position;
    output.texcoord = input.positionOS.xyz;
    
    // �s�N�Z���V�F�[�_�[�ɓn��
    return output;
}