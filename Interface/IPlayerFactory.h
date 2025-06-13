#pragma once
#include "Interface/IObject.h"

class IPlayerFactory
{
	// �v���C���[�𐶐�����
	virtual std::unique_ptr<IObject> CreatePlayer(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// �v���C���[�̑̂𐶐�����
	virtual std::unique_ptr<IObject> CreatePlayerBody(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// �v���C���[�̓��𐶐�����
	virtual std::unique_ptr<IObject> CreatePlayerHead(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// �v���C���[�̍��r�𐶐�����
	virtual std::unique_ptr<IObject> CreatePlayerLeftArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// �v���C���[�̍����𐶐�����
	virtual std::unique_ptr<IObject> CreatePlayerLeftFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// �v���C���[�̉E�r�𐶐�����
	virtual std::unique_ptr<IObject> CreatePlayerRightArm(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;

	// �v���C���[�̉E���𐶐�����
	virtual std::unique_ptr<IObject> CreatePlayerRightFoot(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale) = 0;
};