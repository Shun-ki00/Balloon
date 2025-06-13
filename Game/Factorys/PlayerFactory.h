#pragma once
#include "Interface/IObject.h"
#include "Interface/IPlayerFactory.h"

class PlayerFactory : public IPlayerFactory
{
public:
	// �v���C���[�𐶐�����
	static std::unique_ptr<IObject> CreatePlayer(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale,
		const bool isFixed = false
		);

	// �v���C���[�̑̂𐶐�����
	static std::unique_ptr<IObject> CreatePlayerBody(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �v���C���[�̓��𐶐�����
	static std::unique_ptr<IObject> CreatePlayerHead(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �v���C���[�̍��r�𐶐�����
	static std::unique_ptr<IObject> CreatePlayerLeftArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �v���C���[�̍����𐶐�����
	static std::unique_ptr<IObject> CreatePlayerLeftFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �v���C���[�̉E�r�𐶐�����
	static std::unique_ptr<IObject> CreatePlayerRightArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

	// �v���C���[�̉E���𐶐�����
	static std::unique_ptr<IObject> CreatePlayerRightFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

private:
	// ��]�x�N�g�����N�H�[�^�j�I���ɕϊ�����
	static DirectX::SimpleMath::Quaternion ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation);
};