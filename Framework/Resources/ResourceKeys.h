#pragma once
#include <iostream>
#include <unordered_map>
 

// �e�N�X�`��ID
enum class TextureKeyID : int
{
    Logo,
    Rule,
    FadeMain,
    ClearText,
    FailedText,
    Player,
    Enemy,
    Sea,
    Particle,
    ReadyGo,
    Numbers,
    Numbers1,
    MenuButton,
    MenuButtonFrame,
    MenuButtonFrame2,
    KeyGuide,
    StartText,
    PlayerIcon,
    PlaySceneKeysGuide,
    TimeFrame,
    ScoreFrame,
    BalloonGageFrame,
    BalloonGage,
    HeightMeter,
    HPGage,
    HPGageFrame,
    CloudFrame,
    StageSelectTexts,
    StageSelectKeyGuide,
    ResultText,
    ResultSceneKeyGuide,
    ResultButtonText,
    BalloonExplosion,
    WoodBox,

    Meat,
    Wood,
    Rock,
    Cloud,
    WoodBoxNormal,

    CubeMap,
    EveningCubeMap,
    Balloon,
};
// ���f��ID
enum class ModelKeyID : int
{
    Head,
    EHead,
    Body,
    LeftArm,
    RightArm,
    LeftFoot,
    RightFoot,
    BalloonBody,
    BalloonRope,
    Box,
    Cloud,
    Sphere,
    Torus,
    WoodBox,
};

// �s�N�Z���V�F�[�_�[ID
enum class PS_ID : int
{
    PBRLit_PS,
    Balloon_PS,
    ShadowMap_PS,
    SkyBox_PS,
    Sea_PS,
    UI_PS,
    NumberUI_PS,
    ScoreUI_PS,
    HPUI_PS,
    Particle_PS,
};


// ���_�V�F�[�_�[ID
enum class VS_ID : int
{
    PBRLit_VS,
    ShadowMap_VS,
    SkyBox_VS,
    Sea_VS,
    UI_VS,
    Particle_VS,
};

// �W�I���g���V�F�[�_�[ID
enum class GS_ID : int
{
    UI_GS,
    Particle_GS,
};

// �n���V�F�[�_�[ID
enum class HS_ID : int
{
    Sea_HS,
};

// �h���C���V�F�[�_�[ID
enum class DS_ID : int
{
    Sea_DS,
};
