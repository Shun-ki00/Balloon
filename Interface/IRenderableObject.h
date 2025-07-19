#pragma once


class IRenderableObject {

public:
    // アクティブ状態を設定
    virtual void SetIsActive(const bool& active) = 0;
    // アクティブ状態を取得
    virtual bool GetIsActive() const = 0;

    // モデルを取得する
    virtual DirectX::Model* GetModel() const = 0;

    // ワールド行列を取得する
    virtual DirectX::SimpleMath::Matrix GetWorldMatrix() const = 0;

    // 定数バッファを更新する
    virtual void UpdateConstantBufferIfNeeded(ID3D11DeviceContext* context) = 0;
    // 定数バッファを取得する
    virtual ID3D11Buffer* GetConstantBuffer() const = 0;

    // 更新処理
    virtual void Update(ID3D11DeviceContext* context, const DirectX::SimpleMath::Matrix& worldMatrix) = 0;
    // 描画処理
    virtual void Render(ID3D11DeviceContext* context, DirectX::CommonStates* commonStates,
        DirectX::SimpleMath::Matrix viewMatrix, DirectX::SimpleMath::Matrix projectionMatrix,
        ID3D11ShaderResourceView* shadowMap = nullptr
    ) = 0;

    virtual ~IRenderableObject() = default;
};