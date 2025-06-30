#include "pch.h"
#include "Interface/IObject.h"
#include "Game/Factorys/EnemyFactory.h"
#include "Game/Message/Message.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Node/Root.h"

// �G�p�[�c
#include "Game/Enemy/Enemy.h"
#include "Game/Player/Body.h"
#include "Game/Player/Head.h"
#include "Game/Player/LeftArm.h"
#include "Game/Player/LeftFoot.h"
#include "Game/Player/RightArm.h"
#include "Game/Player/RightFoot.h"


// �G�̍쐬
std::unique_ptr<IObject> EnemyFactory::CreateEnemy(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale, const bool& isFixed)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		EnemyFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<Enemy> enemy;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	enemy.reset(new Enemy(Root::GetInstance(), parent , IObject::ObjectID::ENEMY , initialPosition, rotation , initialScale , Message::MessageID::NONE));
	// ����������
	enemy->Initialize();
	// �Œ�ݒ�
	enemy->SetIsFixed(isFixed);

	// �I�u�W�F�N�g���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::ENEMY, enemy->GetObjectNumber(), enemy.get());

	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(enemy);
}

// �G�̑̂��쐬
std::unique_ptr<IObject> EnemyFactory::CreateEnemyBody(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		EnemyFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<IObject> enemyBody;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	enemyBody.reset(new Body(Root::GetInstance(), parent, IObject::ObjectID::ENEMY_BODY, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	enemyBody->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(enemyBody);
}


// �G�̓����쐬
std::unique_ptr<IObject> EnemyFactory::CreateEnemyHead(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		EnemyFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<IObject> enemyHead;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	enemyHead.reset(new Head(Root::GetInstance(), parent, IObject::ObjectID::ENEMY_HEAD, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	enemyHead->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(enemyHead);
}


// �G�̍��r���쐬
std::unique_ptr<IObject> EnemyFactory::CreateEnemyLeftArm(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		EnemyFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<IObject> enemyLeftArm;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	enemyLeftArm.reset(new LeftArm(Root::GetInstance(), parent, IObject::ObjectID::ENEMY_LEFT_ARM, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	enemyLeftArm->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(enemyLeftArm);
}

// �G�̍������쐬
std::unique_ptr<IObject> EnemyFactory::CreateEnemyLeftFoot(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		EnemyFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<IObject> enemyLeftFoot;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	enemyLeftFoot.reset(new LeftFoot(Root::GetInstance(), parent, IObject::ObjectID::ENEMY_LEFT_FOOT, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	enemyLeftFoot->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(enemyLeftFoot);
}


// �G�̉E�r���쐬
std::unique_ptr<IObject> EnemyFactory::CreateEnemyRightArm(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		EnemyFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<IObject> enemyRightArm;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	enemyRightArm.reset(new RightArm(Root::GetInstance(), parent, IObject::ObjectID::ENEMY_RIGHT_ARM, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	enemyRightArm->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(enemyRightArm);
}

// �G�̉E�����쐬
std::unique_ptr<IObject> EnemyFactory::CreateEnemyRightFoot(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		EnemyFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<IObject> enemyRightFoot;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	enemyRightFoot.reset(new RightFoot(Root::GetInstance(), parent, IObject::ObjectID::ENEMY_RIGHT_FOOT, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	enemyRightFoot->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(enemyRightFoot);
}



/// <summary>
/// ��]�x�N�g�����N�H�[�^�j�I���ɕϊ�����B
/// </summary>
/// <param name="rotation">��]��\���x�N�g���i�x���@�j</param>
/// <returns>�ϊ���̃N�H�[�^�j�I��</returns>
DirectX::SimpleMath::Quaternion EnemyFactory::ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation) {
	return DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(rotation.y),
		DirectX::XMConvertToRadians(rotation.x),
		DirectX::XMConvertToRadians(rotation.z)
	);
}