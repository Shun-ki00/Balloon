#include "pch.h"
#include "Game/RenderableObjects/UIRenderableObject .h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ResourceKeys.h"


UIRenderableObject::UIRenderableObject()
{
	// インスタンスを取得する
	m_resources = Resources::GetInstance();
	m_isAcitve = true;
}


void UIRenderableObject::Initialize(const UIVertexBuffer& vertexBuffer ,
	TextureKeyID baseTexture, TextureKeyID ruleTexture, PS_ID psId)
{
	// テクスチャを取得する
	m_texture = m_resources->GetTextureResources()->GetTexture(baseTexture);
	m_ruleTexture = m_resources->GetTextureResources()->GetTexture(ruleTexture);
	m_pixelShader = m_resources->GetShaderResources()->GetPixelShader(psId);

	// 初期頂点バッファデータ
	m_uiVertexBuffer = vertexBuffer;
}

void UIRenderableObject::Update(ID3D11DeviceContext* context, const DirectX::SimpleMath::Matrix& worldMatrix)
{
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(worldMatrix);
}

void UIRenderableObject::Render(ID3D11DeviceContext* context, DirectX::CommonStates* commonStates,
	DirectX::SimpleMath::Matrix viewMatrix, DirectX::SimpleMath::Matrix projectionMatrix
)
{
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(commonStates);
	UNREFERENCED_PARAMETER(viewMatrix);
	UNREFERENCED_PARAMETER(projectionMatrix);
}

