#pragma once
#include "Interface/IRenderableObject.h"
#include "Game/Buffers.h"
#include "Framework/Resources/ResourceKeys.h"

class Resources;

class UIRenderableObject : public IRenderableObject
{
public:

    // アクティブ状態を設定
    void SetIsActive(const bool& active) override { m_isAcitve = active; }
    // アクティブ状態を取得
    bool GetIsActive() const override { return m_isAcitve; }

    // 座標を設定
    void SetPosition(const DirectX::SimpleMath::Vector3& position) { 
        m_uiVertexBuffer.position = { position.x , position.y ,position.z, 1.0f}; }
    // 回転を設定
    void SetRotate(const float& rotate) { m_uiVertexBuffer.rotate.z = rotate; }
    // 大きさを設定
    void SetScale(DirectX::SimpleMath::Vector2 scale) { 
        m_uiVertexBuffer.rotate.x = scale.x; m_uiVertexBuffer.rotate.y = scale.y; }
    // UV座標のオフセットを設定
    void SetUvOffset(DirectX::SimpleMath::Vector2 offset) { 
        m_uiVertexBuffer.rect.x = offset.x; m_uiVertexBuffer.rect.y = offset.y; }
    // テクスチャの分割数を設定
    void SetUvScale(DirectX::SimpleMath::Vector2 scale) {
        m_uiVertexBuffer.rect.z = scale.x; m_uiVertexBuffer.rect.w = scale.y;
    }
    // テクスチャのサイズを設定
    void SetTextureSize(DirectX::SimpleMath::Vector2 size) { m_uiVertexBuffer.size = size; }
    // カラーの設定
    void SetColor(DirectX::SimpleMath::Vector4 color) { m_uiVertexBuffer.color = color; }

    // ルール情報
    // ルール画像を使用するかどうかを設定
    void SetUseRuleTexture(const float& useTexture) { m_uiVertexBuffer.rule.x = useTexture; }
    // ルール画像の進行度を設定
    void SetRuleProgress(const float& progress) { m_uiVertexBuffer.rule.y = progress; }
    // ルール画像の反転を設定
    void SetRuleInverse(const float& inverse) { m_uiVertexBuffer.rule.z = inverse; }

    // 頂点バッファデータを取得する
    UIVertexBuffer GetVertexBufferData() const { return m_uiVertexBuffer; }

    // ピクセルシェーダーを取得する
    ID3D11PixelShader* GetPixelShader() const { return m_pixelShader; }

    // テクスチャを取得する
    ID3D11ShaderResourceView* GetTexture() const { return m_texture; }
    // ルール画像を取得する
    ID3D11ShaderResourceView* GetRuleTexture() const { return m_ruleTexture; }

public:

    // コンストラクタ
    UIRenderableObject();
    // デストラクタ
    ~UIRenderableObject() override = default;

    // 定数バッファを更新する
    void UpdateConstantBufferIfNeeded(ID3D11DeviceContext* context) {}
    // 定数バッファを取得する
    ID3D11Buffer* GetConstantBuffer() const { return nullptr; }

    // 初期化処理
    void Initialize(const UIVertexBuffer& vertexBuffer,TextureKeyID baseTexture, TextureKeyID ruleTexture, PS_ID psId);
    // 更新処理
    void Update(ID3D11DeviceContext* context, const DirectX::SimpleMath::Matrix& worldMatrix) override;
    // 描画処理
    void Render(ID3D11DeviceContext* context, DirectX::CommonStates* commonStates,
        DirectX::SimpleMath::Matrix viewMatrix, DirectX::SimpleMath::Matrix projectionMatrix
    ) override;

private:

    // アクティブ処理
    bool m_isAcitve;

    // リソース
    Resources* m_resources;
    // デバイス
    ID3D11Device1* m_device;

    // ピクセルシェーダー
    ID3D11PixelShader* m_pixelShader;

    // 頂点バッファ
    UIVertexBuffer m_uiVertexBuffer;

    // メインテクスチャ
    ID3D11ShaderResourceView* m_texture;
    // ルール画像
    ID3D11ShaderResourceView* m_ruleTexture;
};