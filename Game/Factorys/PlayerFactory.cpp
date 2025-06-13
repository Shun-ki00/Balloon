#include "pch.h"
#include "Interface/IObject.h"
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Message/Message.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Message/KeyboardMessenger.h"
#include "Game/Node/root.h"

// �v���C���[�p�[�c
#include "Game/Player/Player.h"
#include "Game/Player/Body.h"
#include "Game/Player/Head.h"
#include "Game/Player/LeftArm.h"
#include "Game/Player/LeftFoot.h"
#include "Game/Player/RightArm.h"
#include "Game/Player/RightFoot.h"


// �v���C���[�̍쐬
std::unique_ptr<IObject> PlayerFactory::CreatePlayer(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale,
	const bool isFixed
)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		PlayerFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<Player> player;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	player.reset(new Player(Root::GetInstance(), parent , IObject::ObjectID::PLAYER , initialPosition, rotation , initialScale , Message::MessageID::PLAYER_IDLING));
	// ����������
	player->Initialize();

	// �L�[�{�[�h���b�Z���W���[�ɓo�^
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY, DirectX::Keyboard::Keys::Left, player.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY, DirectX::Keyboard::Keys::Right, player.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_DOWN, DirectX::Keyboard::Keys::Up, player.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_UP, DirectX::Keyboard::Keys::Up, player.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_UP, DirectX::Keyboard::Keys::Down, player.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_DOWN, DirectX::Keyboard::Keys::Down, player.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_DOWN, DirectX::Keyboard::Keys::Space, player.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_UP, DirectX::Keyboard::Keys::Space, player.get());
	KeyboardMessenger::GetInstance()->Attach(KeyType::ON_KEY_DOWN, DirectX::Keyboard::Keys::Z, player.get());

	// �I�u�W�F�N�g���b�Z���W���[�ɓo�^
	ObjectMessenger::GetInstance()->Register(IObject::ObjectID::PLAYER , player->GetObjectNumber(), player.get());

	// �Œ�ݒ�̏ꍇ
	if (isFixed) player->SetIsFixed(true);

	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(player);
}

// �v���C���[�̑̂��쐬
std::unique_ptr<IObject> PlayerFactory::CreatePlayerBody(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		PlayerFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<IObject> playerBody;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	playerBody.reset(new Body(Root::GetInstance(), parent, IObject::ObjectID::PLAYER_BODY, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	playerBody->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(playerBody);
}


// �v���C���[�̓����쐬
std::unique_ptr<IObject> PlayerFactory::CreatePlayerHead(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		PlayerFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<IObject> playerHead;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	playerHead.reset(new Head(Root::GetInstance(), parent, IObject::ObjectID::PLAYER_HEAD, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	playerHead->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(playerHead);
}


// �v���C���[�̍��r���쐬
std::unique_ptr<IObject> PlayerFactory::CreatePlayerLeftArm(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		PlayerFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<IObject> playerleftArm;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	playerleftArm.reset(new LeftArm(Root::GetInstance(), parent, IObject::ObjectID::PLAYER_LEFT_ARM, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	playerleftArm->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(playerleftArm);
}

// �v���C���[�̍������쐬
std::unique_ptr<IObject> PlayerFactory::CreatePlayerLeftFoot(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		PlayerFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<IObject> playerLeftFoot;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	playerLeftFoot.reset(new LeftFoot(Root::GetInstance(), parent, IObject::ObjectID::PLAYER_LEFT_FOOT, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	playerLeftFoot->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(playerLeftFoot);
}


// �v���C���[�̉E�r���쐬
std::unique_ptr<IObject> PlayerFactory::CreatePlayerRightArm(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		PlayerFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<IObject> playerRightArm;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	playerRightArm.reset(new RightArm(Root::GetInstance(), parent, IObject::ObjectID::PLAYER_RIGHT_ARM, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	playerRightArm->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(playerRightArm);
}

// �v���C���[�̉E�����쐬
std::unique_ptr<IObject> PlayerFactory::CreatePlayerRightFoot(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		PlayerFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<IObject> playerRightFoot;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	playerRightFoot.reset(new RightFoot(Root::GetInstance(), parent, IObject::ObjectID::PLAYER_RIGHT_FOOT, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	playerRightFoot->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(playerRightFoot);
}



/// <summary>
/// ��]�x�N�g�����N�H�[�^�j�I���ɕϊ�����B
/// </summary>
/// <param name="rotation">��]��\���x�N�g���i�x���@�j</param>
/// <returns>�ϊ���̃N�H�[�^�j�I��</returns>
DirectX::SimpleMath::Quaternion PlayerFactory::ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation) {
	return DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(rotation.y),
		DirectX::XMConvertToRadians(rotation.x),
		DirectX::XMConvertToRadians(rotation.z)
	);
}