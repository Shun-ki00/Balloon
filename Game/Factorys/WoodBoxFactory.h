#pragma once
#include "Interface/IObject.h"

class WoodBoxFactory
{
public:

	// �ؔ��I�u�W�F�N�g���쐬����
	static std::unique_ptr<IObject> CreateWoodBox(IObject* parent,
		const DirectX::SimpleMath::Vector3& initialPosition,
		const DirectX::SimpleMath::Vector3& initialRotation,
		const DirectX::SimpleMath::Vector3& initialScale);

private:
	// ��]�x�N�g�����N�H�[�^�j�I���ɕϊ�����
	static DirectX::SimpleMath::Quaternion ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation);

};