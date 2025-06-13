#pragma once
#include "pch.h"
#include  "Game/Transform/Transform.h"

class ICamera
{
public:
	// Transform���擾����
	virtual Transform* GetTransform() const = 0;
	// �r���[�s����쐬����
	virtual DirectX::SimpleMath::Matrix GetViewMatrix() const = 0;

public:
	// ���z�f�X�g���N�^
	virtual ~ICamera() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;
	// �r���[�s��̍쐬
	virtual DirectX::SimpleMath::Matrix CalculateViewMatrix() = 0;
};