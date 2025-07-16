#include "pch.h"
#include "Framework/DebugRenderer.h"
#include "Framework/CommonResources.h"
#include "Framework/Microsoft/DebugDraw.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
DebugRenderer::DebugRenderer()
{
}

/// <summary>
/// �`��
/// </summary>
void DebugRenderer::Render(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitiveBatch)
{
    // �{�b�N�X�̕`�揈��
    for (const auto& box : m_boxes)
    {
        DX::Draw(primitiveBatch, box);
    }

    // �X�t�B�A�̕`�揈��
    for (const auto& sphere : m_spheres)
    {
        DX::Draw(primitiveBatch, sphere);
    }

   // ���Z�b�g����
   this->Reset();
}


/// <summary>
/// �{�b�N�X���A�^�b�`����
/// </summary>
/// <param name="box">�{�b�N�X</param>
void DebugRenderer::Attach(const DirectX::BoundingBox& box)
{
    m_boxes.push_back(box);
}

/// <summary>
/// �X�t�B�A���A�^�b�`����
/// </summary>
/// <param name="sphere">�X�t�B�A</param>
void DebugRenderer::Attach(const DirectX::BoundingSphere& sphere)
{
    m_spheres.push_back(sphere);
}

/// <summary>
/// ���Z�b�g����
/// </summary>
void DebugRenderer::Reset()
{
    m_boxes.clear();
    m_spheres.clear();
}