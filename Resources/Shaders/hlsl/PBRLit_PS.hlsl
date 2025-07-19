#include "PBRLit.hlsli"

// �m�[�}���}�b�v
Texture2D<float4> normalMap : register(t1);
// �L���[�u�}�b�v
TextureCube<float4> cubeMap : register(t2);
// �V���h�E�}�b�v�e�N�X�`��
Texture2D ShadowMapTexture : register(t3);

// �V���h�E�}�b�v�p�e�N�X�`���T���v���[
SamplerComparisonState ShadowMapSampler : register(s1);

// �}�b�n�o���h�΍�
//#define SHADOW_EPSILON 0.0005f
static const float SHADOW_EPSILON = 0.0005f;


float4 main(PS_Input input) : SV_TARGET
{
    // �x�[�X�J���[���g�p����ꍇ�T���v�����O���s��
    float4 baseColor = lerp(c_baseColor,Texture.Sample(Sampler,input.uv),t_useBaseMap);
    
     // �m�[�}���}�b�v���T���v�����O
    float3 normalMapSample = normalMap.Sample(Sampler, input.uv).rgb;
    
    normalMapSample = normalMapSample * 2.0 - 1.0;
    // TBN�s��̍쐬
    float3x3 TBN = float3x3(input.tangentWS, input.binormalWS, input.normalWS);
    
    // �m�[�}���}�b�v���g�p����ꍇ�ڐ���Ԃ̖@�������[���h��Ԃɕϊ�
    float3 normalWS = lerp(input.normalWS, normalize(mul(normalMapSample, TBN)), t_useNormalMap);
   
    // �����x�N�g�����v�Z
    float3 viewDir = normalize(EyePosition - input.positionWS);
    
    // ���ʔ��ˌ��̐F���T���v�����O
    float3 refVec = reflect(viewDir, normalWS);
    refVec.y *= -1;
    float3 indirectSpecular = cubeMap.SampleLevel(Sampler, refVec, f_smoothness * 12).rgb;
    
    // �f�B���N�V���i�����C�g�̏��iDirectXTK �̕W�����C�g�j
    float3 lightDir = LightDirection[0];      // ���C�g�̕���
    float3 lightColor = LightDiffuseColor[0]; // ���C�g�̐F
    
    float4 lightPos = mul(float4(input.positionWS, 1.0f), lightViewProjection);
        // ���݂̃s�N�Z�����V���h�E�}�b�v��łǂ̈ʒu�ɂ����邩�v�Z����
    float2 uv = lightPos.xy * float2(0.5f, -0.5f) + 0.5f;
    // �ʏ�`��̐[�x�l�ƃ��C�g��Ԃ̐[�x�l���r���ĉe�ɂȂ邩���ׂ�
    // ShadowMapTexture�̊Y������ꏊ�̐[�x�l�ƌ��݂̃s�N�Z���̐[�x�l���r���āA�e�ɂȂ邩���ׂ�
    // shadow�@0.0f�F�e������A1.0f�F�e���Ȃ�
    float shadow = ShadowMapTexture.SampleCmpLevelZero(
        ShadowMapSampler, uv, lightPos.z - SHADOW_EPSILON);

     // PBR��BRDF���v�Z
    float4 color = BRDF(
        baseColor.rgb,   // �x�[�X�J���[
        f_matallic,      // ���^���b�N
        f_smoothness,    // �e��
        normalWS,        // �@���x�N�g��
        viewDir,         // �����x�N�g��
        lightDir,        // ���C�g�̕���
        lightColor,      // ���C�g�̐F
        indirectSpecular // �����ɂ��Ԑڋ��ʔ���
    );
    
     // �V���h�E�K�p
    //color.rgb *= lerp(lightAmbient, float3(1.0f, 1.0f, 1.0f), shadow);
    
    // �A���t�@�l��ݒ�
    color.a = baseColor.a;

    // �ŏI�I�ȃs�N�Z���J���[��Ԃ�
    return color;
}