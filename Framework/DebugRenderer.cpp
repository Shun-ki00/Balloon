#include "pch.h"
#include "Framework/DebugRenderer.h"
#include "Framework/CommonResources.h"
#include "Framework/Microsoft/DebugDraw.h"

/// <summary>
/// コンストラクタ
/// </summary>
DebugRenderer::DebugRenderer()
{
}

/// <summary>
/// 描画
/// </summary>
void DebugRenderer::Render(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitiveBatch)
{
    // ボックスの描画処理
    for (const auto& box : m_boxes)
    {
        DX::Draw(primitiveBatch, box);
    }

    // スフィアの描画処理
    for (const auto& sphere : m_spheres)
    {
        DX::Draw(primitiveBatch, sphere);
    }

   // リセット処理
   this->Reset();
}


/// <summary>
/// ボックスをアタッチする
/// </summary>
/// <param name="box">ボックス</param>
void DebugRenderer::Attach(const DirectX::BoundingBox& box)
{
    m_boxes.push_back(box);
}

/// <summary>
/// スフィアをアタッチする
/// </summary>
/// <param name="sphere">スフィア</param>
void DebugRenderer::Attach(const DirectX::BoundingSphere& sphere)
{
    m_spheres.push_back(sphere);
}

/// <summary>
/// リセット処理
/// </summary>
void DebugRenderer::Reset()
{
    m_boxes.clear();
    m_spheres.clear();
}