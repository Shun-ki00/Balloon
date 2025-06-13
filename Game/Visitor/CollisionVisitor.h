#pragma once
#include "Interface/ICollisionVisitor.h"

class CollisionVisitor : public ICollisionVisitor
{

public:
	// �Փˏ����r�W�^�[���J�n����
	void StartPrepareCollision(IObject* object) override;
	// �ċA�I�ɏՓˏ����r�W�^�[���Ăяo��
	void PrepareCollision(IObject* object,
		const DirectX::SimpleMath::Vector3& position, const float& radius) override;
	// �ċA�I��DetectCollision�֐����Ăяo��
	void DetectCollision(IObject* object, IObject* object1) override;

	// ���E�{�b�N�X��`�悷��
	void DebugDraw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitiveBatch) override;

private:
	//	�R���X�g���N�^
	CollisionVisitor();
	//	�f�X�g���N�^
	~CollisionVisitor() = default;
public:
	CollisionVisitor(const CollisionVisitor&) = delete;             // �R�s�[�֎~
	CollisionVisitor& operator=(const CollisionVisitor&) = delete;  // �R�s�[����֎~
	CollisionVisitor(const CollisionVisitor&&) = delete;            // ���[�u�֎~
	CollisionVisitor& operator=(const CollisionVisitor&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static CollisionVisitor* GetInstance()
	{
		static CollisionVisitor instance;
		return &instance;
	}


private:

	// �u�C���v�z��o�E���f�B���O�{�b�N�X
	std::unordered_map<int, DirectX::BoundingSphere> m_boundingSphere;

	std::unordered_map<IObject* ,std::unordered_map<bool, DirectX::BoundingSphere>> m_worldBoundingSpheres;
};