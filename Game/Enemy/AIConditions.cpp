#include "pch.h"
#include "Game/Enemy/AIConditions.h"
#include "Game/Player/Player.h"
#include "Game/Object/Object.h"

// AIConditions
std::unique_ptr<AIConditions> AIConditions::s_aiConditions = nullptr;

// AIConditions�N���X�̃C���X�^���X���擾����
AIConditions* AIConditions::GetInstance()
{
	if (s_aiConditions == nullptr)
	{
		// AIConditions�N���X�̃C���X�^���X�𐶐�����
		s_aiConditions.reset(new AIConditions());
	}

	// AIConditions�N���X�̃C���X�^���X��Ԃ�
	return s_aiConditions.get();
}

void AIConditions::DestroyInstance()
{
	s_aiConditions.release();
}


AIConditions::AIConditions()
{

}


AIConditions::~AIConditions()
{

}

/// <summary>
/// �v���C���[�̏�ɂ��邩�ǂ���
/// </summary>
/// <param name="enemy">�G�I�u�W�F�N�g</param>
/// <param name="heightOffset">�I�t�Z�b�g</param>
/// <returns>����</returns>
bool AIConditions::IsAbovePlayer(Object* enemy, float heightOffset)
{
	// �v���C���[�����ݒ�Ȃ玸�s
	if (!m_player) return false;

	// �v���C���[�̃I�t�Z�b�g���W
	float playerOffset =
		m_player->GetTransform()->GetLocalPosition().y + heightOffset;
	// �G�̃I�t�Z�b�g���W
	float enemyHeight = enemy->GetTransform()->GetLocalPosition().y;

	// �v���C���[�̏�ɂ���ꍇtrue��Ԃ�
	return enemyHeight >= playerOffset;
}


/// <summary>
/// �v���C���[�̉��ɂ��邩�ǂ���
/// </summary>
/// <param name="enemy">�G�I�u�W�F�N�g</param>
/// <param name="heightOffset">�I�t�Z�b�g</param>
/// <returns>����</returns>
bool AIConditions::IsBelowPlayer(Object* enemy, float heightOffset)
{
	// �v���C���[�����ݒ�Ȃ玸�s
	if (!m_player) return false;

	// �v���C���[�̃I�t�Z�b�g���W
	float playerOffset =
		m_player->GetTransform()->GetLocalPosition().y + heightOffset;
	// �G�̃I�t�Z�b�g���W
	float enemyHeight = enemy->GetTransform()->GetLocalPosition().y;

	// �v���C���[�̉��ɂ���ꍇtrue��Ԃ�
	return enemyHeight <= playerOffset;
}

/// <summary>
/// �v���C���[�̎�����ɂ��邩�ǂ���
/// </summary>
/// <param name="enemy"></param>
/// <returns></returns>
bool AIConditions::IsPlayerVisible(Object* enemy)
{
	if (!m_player) return false;

	// �v���C���[����G�ւ̕����x�N�g�����v�Z
	DirectX::SimpleMath::Vector3 toTarget = enemy->GetTransform()->GetLocalPosition() - m_player->GetTransform()->GetLocalPosition();

	// �v���C���[�̑O���x�N�g��
	DirectX::SimpleMath::Vector3 forward = 
		DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward,
		m_player->GetTransform()->GetLocalRotation());

	// �P�ʃx�N�g���ɐ��K��
	toTarget.Normalize();
	forward.Normalize();

	// �����ƃ^�[�Q�b�g�����x�N�g���̊p�x��Dot�ςŔ�r
	float dot = forward.Dot(toTarget);
	return dot > 0.866f; // �� ����60�x�ȓ�
}

/// <summary>
/// �v���C���[�̈��͈͓��ɓG�����邩�ǂ����𔻒肷��
/// </summary>
/// <param name="enemy">�G�I�u�W�F�N�g</param>
/// <param name="offset">�v���C���[�ʒu�̕␳�i��F���������j</param>
/// <param name="range">�L���͈͂̔��a</param>
/// <returns>�͈͓��Ȃ� true�A�͈͊O�Ȃ� false</returns>
bool AIConditions::IsPlayerInRange(Object* enemy, DirectX::SimpleMath::Vector3 offset, float range)
{
	if (!m_player || !enemy) return false;

	// �v���C���[�ʒu�ɕ␳�I�t�Z�b�g�����Z�������W
	const DirectX::SimpleMath::Vector3& playerPosition = m_player->GetTransform()->GetLocalPosition() + offset;
	// �G�̌��݈ʒu
	const DirectX::SimpleMath::Vector3& enemyPosition = enemy->GetTransform()->GetLocalPosition();

	// �v���C���[�ƓG�̋�����2��i���������j���v�Z
	float distanceSquared = (playerPosition - enemyPosition).LengthSquared();
	// ���e�͈͂̔��a��2��i���������j���v�Z
	float rangeSquared = range * range;

	// �����̕������͈͂̕����ȉ��Ȃ�A�͈͓��Ɣ���
	return distanceSquared <= rangeSquared;
}

