#pragma once

class DebugRenderer
{

public:

	// �{�b�N�X�̓o�^
	void Attach(const DirectX::BoundingBox& box);
	// �X�t�B�A�̓o�^
	void Attach(const DirectX::BoundingSphere& sphere);

	// ���Z�b�g
	void Reset();

	// �`�揈��
	void Render(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitiveBatch);
	
private:
	//	�R���X�g���N�^
	DebugRenderer();
	//	�f�X�g���N�^
	~DebugRenderer() = default;
public:
	DebugRenderer(const DebugRenderer&) = delete;             // �R�s�[�֎~
	DebugRenderer& operator=(const DebugRenderer&) = delete;  // �R�s�[����֎~
	DebugRenderer(const DebugRenderer&&) = delete;            // ���[�u�֎~
	DebugRenderer& operator=(const DebugRenderer&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static DebugRenderer* GetInstance()
	{
		static DebugRenderer instance;
		return &instance;
	}

private:

	// �{�b�N�X
	std::vector<DirectX::BoundingBox> m_boxes;
	// �X�t�B�A
	std::vector<DirectX::BoundingSphere> m_spheres;

};