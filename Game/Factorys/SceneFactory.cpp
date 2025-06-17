#include "pch.h"
#include "Game/Factorys/SceneFactory.h"
#include "Game/Factorys/UIFactory.h"
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/BalloonFactory.h"
#include "Game/Factorys/EnemyFactory.h"
#include "Game/Factorys/CameraFactory.h"
#include "Game/Factorys/EffectFactory.h"
#include "Game/Factorys/WoodBoxFactory.h"
#include "Game/Node/Root.h"


/// <summary>
/// �^�C�g���V�[���̃I�u�W�F�N�g���쐬
/// </summary>
/// <param name="root">���[�g�I�u�W�F�N�g</param>
void SceneFactory::CreateTitleScene(Root* root)
{
	// �v���C���[ �i�Œ�j0
	root->Attach(PlayerFactory::CreatePlayer(root,
		{ 2.7f , -0.5f ,-1.5f }, { 0.0f ,-45.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f, true));

	// �J�����̍쐬������
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Backward,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Down, DirectX::XMConvertToRadians(30.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(10.0f)))
	);

	// �J�����V�X�e�����A�^�b�`���� 1
	root->Attach(CameraFactory::CreateCameraSystem(root, std::move(cameras)));

	// �^�C�g�����S 2
	root->Attach(UIFactory::CreateTitleLogoUI(
		root, IObject::ObjectID::TITLE_LOGO_UI,
		DirectX::SimpleMath::Vector3{ 400.0f , -300.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One));

	// �X�^�[�g�e�L�X�g 3
	root->Attach(UIFactory::CreateStartTextUI(
		root, IObject::ObjectID::START_TEXT_UI,
		DirectX::SimpleMath::Vector3{ 400.0f , 400.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::Zero));

	// �t�F�[�h�I�u�W�F�N�g 4
	root->Attach(UIFactory::CreateFade(
		root, IObject::ObjectID::FADE,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One));
}

/// <summary>
/// �X�e�[�W�Z���N�g�V�[���I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="root">���[�g�I�u�W�F�N�g</param>
void SceneFactory::CreateStageSelectScene(Root* root)
{

	// �X�e�[�W�i���o�[

	// �X�e�[�W�Z���N�g�w�i

	// �X�e�[�W�Z���N�g�������


}



/// <summary>
/// �v���C�V�[���I�u�W�F�N�g�쐬
/// </summary>
/// <param name="root">���[�g�I�u�W�F�N�g</param>
void SceneFactory::CreatePlayScene(Root* root)
{

	// �v���C���[ �i�Œ�j0
	root->Attach(PlayerFactory::CreatePlayer(root,
		DirectX::SimpleMath::Vector3::Zero, { 0.0f ,0.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f, false));

	// �G�@����
	root->Attach(EnemyFactory::CreateEnemy(root,
		{ 2.7f , -0.5f ,-1.5f }, { 0.0f ,0.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f));
	root->Attach(EnemyFactory::CreateEnemy(root,
		{ 2.7f , -0.5f ,-2.5f }, { 0.0f ,0.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f));
	root->Attach(EnemyFactory::CreateEnemy(root,
		{ 2.7f , -4.5f ,-1.5f }, { 0.0f ,0.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f));
	root->Attach(EnemyFactory::CreateEnemy(root,
		{ 2.7f , 3.5f ,-1.5f }, { 0.0f ,0.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f));

	// �J�E���g�_�E��UI
	root->Attach(UIFactory::CreateCountdownUI(root, IObject::ObjectID::COUNTDOWN_UI,
		{ 1280.0f + 300.0f  , 720.0f / 2.0f,1.0f }, DirectX::SimpleMath::Vector3::Zero, {1.0f ,1.0f ,0.0f}));
	// �^�C�}�[UI
	root->Attach(UIFactory::CreateTimerFrameUI(root, IObject::ObjectID::TIME_FRAME_UI,
		{ 1180.0f , 100.0f ,0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.5f));
	// �^�C���i���o�[UI
	root->Attach(UIFactory::CreateTimeUI(root, IObject::ObjectID::TIME_NUMBER_UI,
		{ 1180.0f , 100.0f ,0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.35f));
	// �v���C���[�̍���UI
	root->Attach(UIFactory::CreateHeightMeterUI(root, IObject::ObjectID::HEIGHT_METER_UI,
		{ 1280.0f - 70.0f , 720.0f / 2.0f ,0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.5f));
	// �L�[�������UI
	root->Attach(UIFactory::CreatePlaySceneKeyGuideUI(root, IObject::ObjectID::HEIGHT_METER_UI,
		{ 400.0f , 720.0f - 35.0f ,0.0f }, DirectX::SimpleMath::Vector3::Zero, {2.0f , 2.0f,0.0f}));

	// ���D�̑傫���Q�[�W�t���[��UI
	root->Attach(UIFactory::CreateBalloonFrameUI(root, IObject::ObjectID::BALLOON_HP_FRAME_UI,
		DirectX::SimpleMath::Vector3(100.0f, 100.0f, 0.0f), DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.3f));
	// ���D�̑傫���Q�[�WUI
	root->Attach(UIFactory::CreateBalloonHPUI(root, IObject::ObjectID::BALLOON_HP_UI,
		{ 100.0f , 141.0f  ,0.0f }, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.6f));

	// �̗̓Q�[�WUI
	root->Attach(UIFactory::CreateHPUI(root, IObject::ObjectID::HP_UI,
		{ 260.0f , 120.0f ,0.0f }, DirectX::SimpleMath::Vector3::Zero, {0.4f , 0.35f, 0.0f}));

	// �t�F�[�h
	//root->Attach(UIFactory::CreateFade(root, IObject::ObjectID::FADE,
	//	DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Vector3::One));

}



/// <summary>
/// �Q�[���N���A�V�[���̃I�u�W�F�N�g���쐬
/// </summary>
/// <param name="root">���[�g�I�u�W�F�N�g</param>
void SceneFactory::CreateGameClearScene(Root* root)
{
	// �v���C���[ 0 
	root->Attach(PlayerFactory::CreatePlayer(root,
		{ 2.7f , -0.5f ,-1.5f }, { 0.0f ,-45.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f, true));

	// �J�����̍쐬������
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Backward,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Down, DirectX::XMConvertToRadians(30.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(10.0f)))
	);

	// �J�����V�X�e�����A�^�b�`���� 1
	root->Attach(CameraFactory::CreateCameraSystem(root, std::move(cameras)));


	// �{�^��UI 2
	root->Attach(UIFactory::CreateResultSceneButtons(
		root, IObject::ObjectID::RESULT_SCENE_KEYS_GUIDE_UI,
		{ 1280.0f / 2.0f - 200.0f , 300.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One * 0.7f));

	// �L�[�K�C�hUI 3
	root->Attach(UIFactory::CreateResultSceneKeyGuideUI(
		root, IObject::ObjectID::RESULT_SCENE_KEYS_GUIDE_UI,
		{ 1280.0f / 2.0f - 50.0f , 720.0f - 50.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One * 0.7f));

	// �N���A�e�L�X�g 4
	root->Attach(UIFactory::CreateResultTextUI(
		root, IObject::ObjectID::RESULT_TEXT_UI,
		{ 1280.0f / 2.0f - 200.0f , 150.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One * 0.7f,
		ResultTextUI::TextID::CLEAR));

	// �t�F�[�h�I�u�W�F�N�g 5
	root->Attach(UIFactory::CreateFade(
		root, IObject::ObjectID::FADE,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One));
}


/// <summary>
/// �Q�[���I�[�o�[�V�[���̃I�u�W�F�N�g���쐬
/// </summary>
/// <param name="root">���[�g�I�u�W�F�N�g</param>
void SceneFactory::CreateGameOverScene(Root* root)
{
	// �v���C���[ 0
	root->Attach(PlayerFactory::CreatePlayer(root,
		{ 4.7f , -20.0f ,-3.5f }, { 0.0f ,0.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.1f, true));

	// �ؔ� 1
	root->Attach(WoodBoxFactory::CreateWoodBox(root,
		{ 4.7f , -20.9f ,-3.5f }, { 0.0f ,0.0f, 0.0f }, DirectX::SimpleMath::Vector3::One * 0.002f));


	// �J�����̍쐬������
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Backward + DirectX::SimpleMath::Vector3::Down * 18.0f,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Down, DirectX::XMConvertToRadians(30.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(5.0f)))
	);

	// �J�����V�X�e�����A�^�b�`���� 2
	root->Attach(CameraFactory::CreateCameraSystem(root, std::move(cameras)));

	// �{�^��UI 3
	root->Attach(UIFactory::CreateResultSceneButtons(
		root, IObject::ObjectID::RESULT_SCENE_KEYS_GUIDE_UI,
		{ 1280.0f / 2.0f - 200.0f , 300.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One * 0.7f));

	// �L�[�K�C�hUI 4
	root->Attach(UIFactory::CreateResultSceneKeyGuideUI(
		root, IObject::ObjectID::RESULT_SCENE_KEYS_GUIDE_UI,
		{ 1280.0f / 2.0f - 50.0f , 720.0f - 50.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One * 0.7f));

	// �N���A�e�L�X�g 5
	root->Attach(UIFactory::CreateResultTextUI(
		root, IObject::ObjectID::RESULT_TEXT_UI,
		{ 1280.0f / 2.0f - 200.0f , 150.0f ,0.0f },
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One * 0.7f,
		ResultTextUI::TextID::FAILED));

	// �t�F�[�h�I�u�W�F�N�g 6
	root->Attach(UIFactory::CreateFade(
		root, IObject::ObjectID::FADE,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Vector3::One));
}