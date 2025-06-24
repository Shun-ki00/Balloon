#include "pch.h"
#include "Game/SteeringBehavior/SteeringBehavior.h"
#include "Interface/ISteeringBehavior.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SteeringBehavior::SteeringBehavior()
{

}

/// <summary>
/// ����������
/// </summary>
void SteeringBehavior::Initialize()
{

}

/// <summary>
/// �v�Z�������s��
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�v�Z����</returns>
DirectX::SimpleMath::Vector3 SteeringBehavior::Calculate(const float& elapsedTime)
{
	// �����X�e�A�����O�x�N�g��
	DirectX::SimpleMath::Vector3 steeringForce = DirectX::SimpleMath::Vector3::Zero;

	// �r�w�C�r�A���ׂĂ𑖍�
	for (const auto& [flag, behavior] : m_behaviors)
	{
		// �Ώۃr�w�C�r�A�̃r�b�g��ON���m�F
		if ((m_flags & flag) == flag && behavior)
		{
			// �e�r�w�C�r�A�̗͂����Z
			steeringForce += behavior->Calculate();
		}
	}

	return steeringForce;
}

/// <summary>
/// �X�e�A�����O�r�w�C�r�A��ǉ�����
/// </summary>
/// <param name="flag">�t���O�̎��</param>
/// <param name="steeringBehavior">�X�e�A�����O�r�w�C�r�A</param>
void SteeringBehavior::Attach(BEHAVIOR_TYPE flag, std::unique_ptr<ISteeringBehavior> steeringBehavior)
{
	// �X�e�A�����O�r�w�C�r�A��ǉ�����
	m_behaviors[flag] = std::move(steeringBehavior);

	// �r�b�g�t���O��ON�ɂ���
	m_flags |= flag;
}

/// <summary>
/// �X�e�A�����O�r�w�C�r�A���擾����
/// </summary>
/// <param name="flags">�t���O</param>
/// <returns>�X�e�A�����O�r�w�C�r�A</returns>
ISteeringBehavior* SteeringBehavior::GetSteeringBehavior(BEHAVIOR_TYPE flags)
{
	// ����
	auto it = m_behaviors.find(flags);

	// �X�e�A�����O�r�w�C�r�A��������ΕԂ�
	if (it != m_behaviors.end())
		return it->second.get();

	// ������Ȃ��ꍇ��nullptr��Ԃ�
	return nullptr;
}

/// <summary>
/// �X�e�A�����O�r�w�C�r�A��L���ɂ���
/// </summary>
/// <param name="flags">�t���O</param>
void SteeringBehavior::On(BEHAVIOR_TYPE flag)
{
	// �r�b�g�𗧂Ă�
	m_flags |= flag;
}

/// <summary>
/// �X�e�A�����O�r�w�C�r�A�𖳌��ɂ���
/// </summary>
/// <param name="flags">�t���O</param>
void SteeringBehavior::Off(BEHAVIOR_TYPE flag)
{
	// �r�b�g�𗎂Ƃ�
	m_flags ^= flag;
}