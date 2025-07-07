#include "pch.h"
#include "Game/Factorys/SceneFactory.h"
#include "Game/GameConfig/GameConfig.h"
#include "Game/Factorys/UIFactory.h"
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/BalloonFactory.h"
#include "Game/Factorys/EnemyFactory.h"
#include "Game/Factorys/CameraFactory.h"
#include "Game/Factorys/EffectFactory.h"
#include "Game/Factorys/WoodBoxFactory.h"
#include "Game/Node/Root.h"
#include "Game/Parameters/ParameterBuffers.h"
#include "Game/Message/ObjectMessenger.h"

#include <iostream>
#include <fstream>


/// <summary>
/// �^�C�g���V�[���̃I�u�W�F�N�g���쐬
/// </summary>
/// <param name="root">���[�g�I�u�W�F�N�g</param>
void SceneFactory::CreateTitleScene(Root* root)
{
	nlohmann::json data = GameConfig::GetInstance()->GetParameters("Title");

	PlayerParams player;
	data.get_to(player);

	std::vector<UIParams> uis;
	data.at("UI").get_to(uis);

	// �v���C���[ �i�Œ�j0
	root->Attach(PlayerFactory::CreatePlayer(root,
		player.position, player.rotation, player.scale, true));

	// �J�����̍쐬������
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Backward,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Down, DirectX::XMConvertToRadians(30.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(10.0f)))
	);
	// �J�����V�X�e�����A�^�b�`���� 1
	root->Attach(CameraFactory::CreateCameraSystem(root, std::move(cameras)));

	if (uis.size() >= 3)
	{
		// �^�C�g�����S
		root->Attach(UIFactory::CreateTitleLogoUI(
			root, IObject::ObjectID::TITLE_LOGO_UI,
			uis[0].position,
			uis[0].rotation,
			uis[0].scale));

		// �X�^�[�g�e�L�X�g
		root->Attach(UIFactory::CreateStartTextUI(
			root, IObject::ObjectID::START_TEXT_UI,
			uis[1].position,
			uis[1].rotation,
			uis[1].scale));

		// �t�F�[�h
		root->Attach(UIFactory::CreateFade(
			root, IObject::ObjectID::FADE,
			uis[2].position,
			uis[2].rotation,
			uis[2].scale));
	}

}

/// <summary>
/// �X�e�[�W�Z���N�g�V�[���I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="root">���[�g�I�u�W�F�N�g</param>
void SceneFactory::CreateStageSelectScene(Root* root)
{

	nlohmann::json data = GameConfig::GetInstance()->GetParameters("StageSelect");

	std::vector<UIParams> uis;
	data.at("UI").get_to(uis);


	// �J�����̍쐬������
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		{ 0.0, -0.4f, 5.0 },
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Down, DirectX::XMConvertToRadians(-10.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, DirectX::XMConvertToRadians(-30.0f)))
	);
	// �J�����V�X�e�����A�^�b�`���� 1
	root->Attach(CameraFactory::CreateCameraSystem(root, std::move(cameras)));

	root->Attach(UIFactory::CreateStageSelectUI(
		root, IObject::ObjectID::STAGE_SELECT_UI,
		uis[0].position,
		uis[0].rotation,
		uis[0].scale
	));

	root->Attach(UIFactory::CreateStageSelectTextUI(
		root, IObject::ObjectID::STAGE_SELECT_TEXT_UI,
		uis[1].position,
		uis[1].rotation, 
		uis[1].scale
	));

	root->Attach(UIFactory::CreateStageSelectKeyGuideUI(
		root, IObject::ObjectID::STAGE_SELECT_KEYS_GUIDE_UI,
		uis[2].position,
		uis[2].rotation,
		uis[2].scale
	));


	// �t�F�[�h
	root->Attach(UIFactory::CreateFade(
		root, IObject::ObjectID::FADE,
		uis[3].position,
		uis[3].rotation,
		uis[3].scale
	));

}


/// <summary>
/// �v���C�V�[���I�u�W�F�N�g�쐬
/// </summary>
/// <param name="root">���[�g�I�u�W�F�N�g</param>
void SceneFactory::CreatePlayScene(Root* root)
{
	nlohmann::json SceneData = GameConfig::GetInstance()->GetParameters("SceneLinkParams");
	const SceneLinkParams& stageNumber = SceneData.get<SceneLinkParams>();

	auto key = "Play" + std::to_string(stageNumber.stageNumber);

	nlohmann::json data = GameConfig::GetInstance()->GetParameters(key);
	

	// �v���C���[ �i�Œ�j0
	const auto& player = data.get<PlayerParams>();
	root->Attach(PlayerFactory::CreatePlayer(
		root,
		player.position,
		player.rotation,
		player.scale,
		player.fixed));

	// �J�����̍쐬������
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFollowCaemra(
		ObjectMessenger::GetInstance()->FindObject(IObject::ObjectID::PLAYER,1000)->GetTransform(), {0.0f , 8.0f , -8.0f}));
	// �J�����V�X�e�����A�^�b�`���� 1
	root->Attach(CameraFactory::CreateCameraSystem(root, std::move(cameras)));


	// �G�@����
	const auto& enemies = data.at("Enemy").get<std::vector<EnemyParams>>();
	for (const auto& enemy : enemies)
	{
		root->Attach(EnemyFactory::CreateEnemy(
			root,
			enemy.position,
			enemy.rotation,
			enemy.scale,enemy.fixed));
	}


	// �J�E���g�_�E��UI
	const auto& uis = data.at("UI").get<std::vector<UIParams>>();
	root->Attach(UIFactory::CreateCountdownUI(
		root, IObject::ObjectID::COUNTDOWN_UI,
		uis[0].position,
		uis[0].rotation,
		uis[0].scale));

	// �^�C�}�[UI
	root->Attach(UIFactory::CreateTimerFrameUI(
		root, IObject::ObjectID::TIME_FRAME_UI,
		uis[1].position,
		uis[1].rotation,
		uis[1].scale));

	// �^�C���i���o�[UI
	root->Attach(UIFactory::CreateTimeUI(
		root, IObject::ObjectID::TIME_NUMBER_UI,
		uis[2].position,
		uis[2].rotation,
		uis[2].scale));

	// �v���C���[�̍���UI
	root->Attach(UIFactory::CreateHeightMeterUI(
		root, IObject::ObjectID::HEIGHT_METER_UI,
		uis[3].position,
		uis[3].rotation,
		uis[3].scale));

	// �L�[�������UI
	root->Attach(UIFactory::CreatePlaySceneKeyGuideUI(
		root, IObject::ObjectID::HEIGHT_METER_UI,
		uis[4].position,
		uis[4].rotation,
		uis[4].scale));

	// ���D�̑傫���Q�[�W�t���[��UI
	root->Attach(UIFactory::CreateBalloonFrameUI(
		root, IObject::ObjectID::BALLOON_HP_FRAME_UI,
		uis[5].position,
		uis[5].rotation,
		uis[5].scale));

	// ���D�̑傫���Q�[�WUI
	root->Attach(UIFactory::CreateBalloonHPUI(
		root, IObject::ObjectID::BALLOON_HP_UI,
		uis[6].position,
		uis[6].rotation,
		uis[6].scale));

	// �̗̓Q�[�WUI
	root->Attach(UIFactory::CreateHPUI(
		root, IObject::ObjectID::HP_UI,
		uis[7].position,
		uis[7].rotation,
		uis[7].scale));

	// �t�F�[�h
	root->Attach(UIFactory::CreateFade(root, IObject::ObjectID::FADE,
		DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Vector3::One));

}


/// <summary>
/// �Q�[���N���A�V�[���̃I�u�W�F�N�g���쐬
/// </summary>
/// <param name="root">���[�g�I�u�W�F�N�g</param>
void SceneFactory::CreateGameClearScene(Root* root)
{
	nlohmann::json data = GameConfig::GetInstance()->GetParameters("Clear");

	PlayerParams player;
	data.get_to(player);

	std::vector<UIParams> uis;
	data.at("UI").get_to(uis);


	// �v���C���[ 0 
	root->Attach(PlayerFactory::CreatePlayer(root,
		player.position, player.rotation, player.scale, true));

	// �J�����̍쐬������
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Backward,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Down, DirectX::XMConvertToRadians(30.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(10.0f)))
	);

	// �J�����V�X�e�����A�^�b�`���� 1
	root->Attach(CameraFactory::CreateCameraSystem(root, std::move(cameras)));


	// �{�^��UI�i2�j
	root->Attach(UIFactory::CreateResultSceneButtons(
		root,
		IObject::ObjectID::RESULT_BUTTON_SYSTEM,
		uis[0].position,
		uis[0].rotation,
		uis[0].scale
	));

	// �L�[�K�C�hUI�i3�j
	root->Attach(UIFactory::CreateResultSceneKeyGuideUI(
		root,
		IObject::ObjectID::RESULT_SCENE_KEYS_GUIDE_UI,
		uis[1].position,
		uis[1].rotation,
		uis[1].scale
	));

	// �N���A�e�L�X�g�i4�j
	root->Attach(UIFactory::CreateResultTextUI(
		root,
		IObject::ObjectID::RESULT_TEXT_UI,
		uis[2].position,
		uis[2].rotation,
		uis[2].scale,
		ResultTextUI::TextID::CLEAR
	));

	// �t�F�[�hUI�i5�j
	root->Attach(UIFactory::CreateFade(
		root,
		IObject::ObjectID::FADE,
		uis[3].position,
		uis[3].rotation,
		uis[3].scale
	));
}


/// <summary>
/// �Q�[���I�[�o�[�V�[���̃I�u�W�F�N�g���쐬
/// </summary>
/// <param name="root">���[�g�I�u�W�F�N�g</param>
void SceneFactory::CreateGameOverScene(Root* root)
{
	nlohmann::json data = GameConfig::GetInstance()->GetParameters("GameOver");

	PlayerParams player;
	data.get_to(player);

	WoodBoxParams woodBox;
	data.get_to(woodBox);

	std::vector<UIParams> uis;
	data.at("UI").get_to(uis);

	// �v���C���[ 0
	root->Attach(PlayerFactory::CreatePlayer(root,
		player.position, player.rotation, player.scale, true));

	// �ؔ� 1
	root->Attach(WoodBoxFactory::CreateWoodBox(root,
		woodBox.position, woodBox.rotation, woodBox.scale));


	// �J�����̍쐬������
	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Right * 2.0f + DirectX::SimpleMath::Vector3::Backward * -1.0f + DirectX::SimpleMath::Vector3::Down * 19.0f,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Down, DirectX::XMConvertToRadians(30.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right, DirectX::XMConvertToRadians(5.0f)))
	);

	// �J�����V�X�e�����A�^�b�`���� 2
	root->Attach(CameraFactory::CreateCameraSystem(root, std::move(cameras)));

	// �{�^��UI 3
	root->Attach(UIFactory::CreateResultSceneButtons(
		root, IObject::ObjectID::RESULT_BUTTON_SYSTEM,
		uis[0].position,
		uis[0].rotation,
		uis[0].scale));

	// �L�[�K�C�hUI 4
	root->Attach(UIFactory::CreateResultSceneKeyGuideUI(
		root, IObject::ObjectID::RESULT_SCENE_KEYS_GUIDE_UI,
		uis[1].position,
		uis[1].rotation,
		uis[1].scale));

	// �N���A�e�L�X�g 5
	root->Attach(UIFactory::CreateResultTextUI(
		root, IObject::ObjectID::RESULT_TEXT_UI,
		uis[2].position,
		uis[2].rotation,
		uis[2].scale,
		ResultTextUI::TextID::FAILED));

	// �t�F�[�h�I�u�W�F�N�g 6
	root->Attach(UIFactory::CreateFade(
		root, IObject::ObjectID::FADE,
		uis[3].position,
		uis[3].rotation,
		uis[3].scale));
}