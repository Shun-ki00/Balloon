#pragma once
#include "Interface/IRenderableObject.h"
#include "Game/Buffers/ConstantBuffer.h"
#include "Game/Buffers.h"

class Resources;
class AmbientLight;

class WoodBoxRenderableObject : public IRenderableObject
{
public:

    // アクティブ状態を設定
    void SetIsActive(const bool& active) override { m_isAcitve = active; }
    // アクティブ状態を取得
    bool GetIsActive() const override { return m_isAcitve; }

    // モデルを取得する
    DirectX::Model* GetModel() const override { return m_model; }

    // ワールド行列を取得する
    DirectX::SimpleMath::Matrix GetWorldMatrix() const override { return m_worldMatrix; }
    // ワールド行列を設定する
    void SetWorldMatrix(const DirectX::SimpleMath::Matrix& worldMatrix) { m_worldMatrix = worldMatrix; }

    // 定数バッファを取得する
    ID3D11Buffer* GetConstantBuffer() const override;

    // 定数バッファのデータを更新する
    void SetConstantBufferData(const PBRLitConstantBuffer& constants) { m_constants = constants; }


    // 初期化処理
    void Initialize(const PBRLitConstantBuffer& constants);
    // 更新処理
    void Update(ID3D11DeviceContext* context , const DirectX::SimpleMath::Matrix& worldMatrix) override;
    // 描画を行う
    void Render(ID3D11DeviceContext* context, DirectX::CommonStates* commonStates ,
        DirectX::SimpleMath::Matrix viewMatrix , DirectX::SimpleMath::Matrix projectionMatrix,
        ID3D11ShaderResourceView* shadowMap = nullptr
        ) override;
    // コンストラクタ
    WoodBoxRenderableObject(const bool &isActive ,DirectX::Model* model);
    // デストラクタ
    ~WoodBoxRenderableObject() override = default;

private:
    // 値が変更された場合更新処理を行う
    void UpdateConstantBufferIfNeeded(ID3D11DeviceContext* context) override;

    void CreateLightBuffer();

private:

    // アクティブ処理
    bool m_isAcitve;
    
    // リソース
    Resources* m_resources;
    // デバイス
    ID3D11Device1* m_device;

    AmbientLight* m_ambientLight;

    // インプットレイアウト
    ID3D11InputLayout* m_inputLayout;
    // 頂点シェーダー
    ID3D11VertexShader* m_vertexShader;
    // ピクセルシェーダー
    ID3D11PixelShader* m_pixelShader;
  
    // 定数バッファに送るデータ
    PBRLitConstantBuffer m_constants;
    // 定数バッファ
    std::unique_ptr<ConstantBuffer<PBRLitConstantBuffer>> m_constantBuffer;
     // ライト用の定数バッファ
    std::unique_ptr<ConstantBuffer<DirectionalLightBuffer>> m_constantLightBuffer;

    // サンプラ
    Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;

    // モデル
    DirectX::Model* m_model;

    // メインテクスチャ
    ID3D11ShaderResourceView* m_baseMap;
    // ノーマルマップ
    ID3D11ShaderResourceView* m_normalMap;
    // 環境マップ
    ID3D11ShaderResourceView* m_skyMap;

    // ワールド行列
    DirectX::SimpleMath::Matrix m_worldMatrix;
};