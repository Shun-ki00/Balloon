#include "pch.h"
#include "Game/Visitor/CollisionVisitor.h"
#include "Interface/ICollision.h"
#include "Game/Message/ObjectMessenger.h"
#include "Framework/Microsoft/DebugDraw.h"

CollisionVisitor::CollisionVisitor()
{

}

/// <summary>
/// �Փ˔���̏�������
/// </summary>
/// <param name="object">�I�u�W�F�N�g</param>
void CollisionVisitor::StartPrepareCollision(IObject* object)
{
	dynamic_cast<ICollision*>(object)->PrepareCollision(this);
}


/// <summary>
///	���E����o�^����
/// </summary>
/// <param name="object">�I�u�W�F�N�g</param>
/// <param name="boundingSphere">�X�t�B�A</param>
void CollisionVisitor::PrepareCollision(IObject* object, DirectX::BoundingSphere* boundingSphere)
{
	// �I�u�W�F�N�g�ԍ��Ƌ��E�X�t�B�A���}�b�v�Ɋi�[����
	m_boundingSphere.insert({ object->GetObjectNumber() , boundingSphere });
}



void CollisionVisitor::DetectCollision(IObject* object, IObject* object1)
{
	DirectX::BoundingSphere worldBoundingSphere;
	DirectX::BoundingSphere worldBoundingSphere1;

	// �ǂ��炩����A�N�e�B�u�̏ꍇ������s��Ȃ�
	if (!object->GetIsActive() || !object1->GetIsActive())
		return;

	// ���i�ԍ����狫�E�{�b�N�X����������
	auto it = m_boundingSphere.find(object->GetObjectNumber());

	worldBoundingSphere.Center =
		DirectX::SimpleMath::Vector3::Transform(it->second->Center, object->GetTransform()->GetWorldMatrix());

	worldBoundingSphere.Radius = it->second->Radius;

	// ���i�ԍ����狫�E�{�b�N�X����������
	it = m_boundingSphere.find(object1->GetObjectNumber());

	worldBoundingSphere1.Center =
		DirectX::SimpleMath::Vector3::Transform(it->second->Center, object1->GetTransform()->GetWorldMatrix());

	      
	worldBoundingSphere1.Radius = it->second->Radius;

	// �����蔻����s��
	if (worldBoundingSphere.Intersects(worldBoundingSphere1))
	{
		// �Փ˂����ꍇ,���b�Z�[�W�𑗂� �Փˑ���̔ԍ����ꏏ�ɑ���
		ObjectMessenger::GetInstance()->Dispatch(object->GetObjectID(), object->GetObjectNumber(),
			{ Message::MessageID::ON_COLLISION , object1->GetObjectNumber() });

		// object ���̍X�V
  		m_worldBoundingSpheres[object][true] = worldBoundingSphere;
		m_worldBoundingSpheres[object].erase(false);

		// object1 ���̍X�V
		m_worldBoundingSpheres[object1][true] = worldBoundingSphere1;
		m_worldBoundingSpheres[object1].erase(false);
	}
	else
	{
		if (m_worldBoundingSpheres.find(object) == m_worldBoundingSpheres.end())
		{
			m_worldBoundingSpheres[object].insert({ false, worldBoundingSphere });
		}

		m_worldBoundingSpheres[object1].insert({ false, worldBoundingSphere1 });
	}

}

/// <summary>
/// ���E���̕`��
/// </summary>
/// <param name="primitiveBatch"></param>
void CollisionVisitor::DebugDraw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitiveBatch)
{
	for (const auto& [object, result] : m_worldBoundingSpheres)
	{
		for (const auto& [collisionResult, sphere] : result)
		{
			if (collisionResult)
				DX::Draw(primitiveBatch, sphere, DirectX::Colors::Yellow);
			else
				DX::Draw(primitiveBatch, sphere, DirectX::Colors::Green);
		}
	}

	m_worldBoundingSpheres.clear();
}