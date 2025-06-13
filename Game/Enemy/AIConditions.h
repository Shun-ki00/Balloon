#pragma once

class Object;
class Player;

class AIConditions
{
public:
	// �Ώۂ̃I�u�W�F�N�g��ݒ肷��
	void SetTargetObject(Player* enemy) { m_player = enemy; }

	// AIConditions�N���X�̃C���X�^���X���擾����
	static AIConditions* GetInstance();
	// AIConditions�̃N���X�̃C���X�^���X��j������
	static void DestroyInstance();
	// �R���X�g���N�^
	AIConditions();
	// �f�X�g���N�^
	~AIConditions();

	// �v���C���[����ɂ��邩�ǂ���
	bool IsAbovePlayer(Object* enemy, float heightOffset = 0.5f);
	// �v���C���[��艺�ɂ��邩�ǂ���
	bool IsBelowPlayer(Object* enemy, float heightOffset = 0.5f);
	// �v���C���[�̎�����ɂ��邩�ǂ���
	bool IsPlayerVisible(Object* enemy);
	// �v���C���[�̈��͈͓��ɂ��邩�ǂ���
	bool IsPlayerInRange(Object* enemy,DirectX::SimpleMath::Vector3 offset , float range);

private:

	// AIConditions
	static std::unique_ptr<AIConditions> s_aiConditions;

	// �Ώۂ̃I�u�W�F�N�g
	Player* m_player;

};