// ============================================
// 
// �t�@�C����: PlayerSitState.h
// �T�v: PlayerSitState.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class Player;

class PlayerSitState : public IState
{
public:
	// �R���X�g���N�^
	PlayerSitState(Player* player);
	// �f�X�g���N�^
	~PlayerSitState() = default;
	// ����������
	void Initialize() override;
	// ���O�X�V����
	void PreUpdate() override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// ����X�V����
	void PostUpdate() override;
	// �㏈�����s��
	void Finalize() override;

private:

	// �v���C���[�I�u�W�F�N�g
	Player* m_player;
};