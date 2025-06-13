#pragma once

// �r�w�C�r�A�c���[�̌��ʌ^
enum class Result { SUCCESS, FAILURE, RUNNING };

class IBehaviorNode
{
public:
	// �f�X�g���N�^
	virtual ~IBehaviorNode() = default;
	// ���s����
	virtual Result Tick() = 0;
	// ���O���擾����
	virtual std::string GetName() const = 0;
};