#include "pch.h"
#include "Game/Factorys/WoodBoxFactory.h"
#include "Game/WoodBox/WoodBox.h"
#include "Game/Node/Root.h"

/// <summary>
/// �ؔ��I�u�W�F�N�g���쐬����
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
/// <param name="initialPosition">�������W</param>
/// <param name="initialRotation">������]�p</param>
/// <param name="initialScale">�����X�P�[��</param>
/// <returns></returns>
std::unique_ptr<IObject> WoodBoxFactory::CreateWoodBox(IObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition,
	const DirectX::SimpleMath::Vector3& initialRotation,
	const DirectX::SimpleMath::Vector3& initialScale)
{
	// ��]���N�H�[�^�j�I���ɕϊ�
	DirectX::SimpleMath::Quaternion rotation =
		WoodBoxFactory::ConvertToYawPitchRoll(initialRotation);

	// �C����錾����
	std::unique_ptr<WoodBox> playerBody;
	// Turret�N���X�̃C���X�^���X�𐶐�����
	playerBody.reset(new WoodBox(Root::GetInstance(), parent, IObject::ObjectID::WOOD_BOX, initialPosition, rotation, initialScale, Message::MessageID::NONE));
	// ����������
	playerBody->Initialize();
	// �v���C���[�N���X�̃C���X�^���X��Ԃ�
	return std::move(playerBody);
}

/// <summary>
/// ��]�x�N�g�����N�H�[�^�j�I���ɕϊ�����B
/// </summary>
/// <param name="rotation">��]��\���x�N�g���i�x���@�j</param>
/// <returns>�ϊ���̃N�H�[�^�j�I��</returns>
DirectX::SimpleMath::Quaternion WoodBoxFactory::ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation) {
	return DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(rotation.y),
		DirectX::XMConvertToRadians(rotation.x),
		DirectX::XMConvertToRadians(rotation.z)
	);
}