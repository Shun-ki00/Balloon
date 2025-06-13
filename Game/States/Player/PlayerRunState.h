#pragma once
#include "Interface/IState.h"

class Transform;
class Object;

class PlayerRunState : public IState
{
public:
	void SetIsForward(const bool& isForward) { m_isForward = isForward; }
	void SetIsBackward(const bool& isBackward) { m_isBackward = isBackward; }

public:
	// �R���X�g���N�^
	PlayerRunState(Object* object);
	// �f�X�g���N�^
	~PlayerRunState() = default;
	// ����������
	void Initialize() override;
	// ���O�X�V����
	void PreUpdate() override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// ����X�V����
	void PostUpdate() override;
	// �㏈�����s��
	void Finalize() override;

public:

	// �v���C���[�I�u�W�F�N�g
	Object* m_object;
	
	bool m_isForward;
	bool m_isBackward;
};