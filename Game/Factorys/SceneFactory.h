#pragma once

class Root;

class SceneFactory
{
public:

	// �^�C�g���V�[���̍쐬
	static void CreateTitleScene(Root* root);

	// ���j���[�V�[���̍쐬

	// �X�e�[�W�Z���N�g�̍쐬

	// �v���C�V�[���̍쐬
	static void CreatePlayScene(Root* root);


	// �Q�[���N���A�V�[���̍쐬
	static void CreateGameClearScene(Root* root);

	// �Q�[���I�[�o�[�V�[���̍쐬
	static void CreateGameOverScene(Root* root);


};