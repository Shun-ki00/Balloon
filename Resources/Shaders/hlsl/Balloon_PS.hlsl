#include "PBRLit.hlsli"

// �m�[�}���}�b�v
Texture2DArray BalloonColorTexture : register(t1);
// �X�J�C�}�b�v
TextureCube<float4> skyMap : register(t2);
// �V���h�E�}�b�v�e�N�X�`��
Texture2D ShadowMapTexture : register(t3);


float4 main(PS_Input input) : SV_TARGET
{
    // �x�[�X�J���[���g�p���邩����p�̒萔�𕗑D�̃e�N�X�`���ԍ��Ɏg�p
    float4 baseColor = BalloonColorTexture.Sample(Sampler, float3(input.uv, t_useBaseMap));
     
    // �m�[�}���}�b�v���g�p���Ȃ� 
    float3 normalWS = input.normalWS;
   
    // �����x�N�g�����v�Z
    float3 viewDir = normalize(EyePosition - input.positionWS);
    
    // ���ʔ��ˌ��̐F���T���v�����O
    float3 refVec = reflect(viewDir, normalWS);
    refVec.y *= -1;
    float3 indirectSpecular = skyMap.SampleLevel(Sampler, refVec, f_smoothness * 12).rgb;
    
    // �f�B���N�V���i�����C�g�̏��iDirectXTK �̕W�����C�g�j
    float3 lightDir = LightDirection[0]; // ���C�g�̕���
    float3 lightColor = LightDiffuseColor[0]; // ���C�g�̐F

    
     // PBR��BRDF���v�Z
    float4 color = BRDF(
        baseColor.rgb, // �x�[�X�J���[
        f_matallic, // ���^���b�N
        f_smoothness, // �e��
        normalWS, // �@���x�N�g��
        viewDir, // �����x�N�g��
        lightDir, // ���C�g�̕���
        lightColor, // ���C�g�̐F
        indirectSpecular // �����ɂ��Ԑڋ��ʔ���
    );

    // �ŏI�I�ȃs�N�Z���J���[��Ԃ�
    return color;
}