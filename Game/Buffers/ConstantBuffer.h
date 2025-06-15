#pragma once
#include <wrl/client.h>
#include <cstring> // for std::memcmp
#include <type_traits>
#include "Game/Buffers.h"


// アップデートの種類
enum class UpdateStrategy
{
    MAP,
    UPDATE_SUB_RESOURCE,
};


template<typename T>
class ConstantBuffer {
    static_assert(std::is_trivially_copyable_v<T>, "ConstantBuffer<T>: T must be trivially copyable");

public:

    // デフォルトコンストラクタ
    ConstantBuffer() = default;


    /// <summary>
    /// 初期化処理
    /// </summary>
    /// <param name="device"></param>
    /// <returns></returns>
    void Initialize(ID3D11Device* device, UpdateStrategy strategy = UpdateStrategy::MAP)
    {
        // 更新モード設定
        m_updateStrategy = strategy;

        // 定数バッファ用のバッファオブジェクトを作成する
        D3D11_BUFFER_DESC bufferDesc{};
        bufferDesc.ByteWidth = static_cast<UINT>(sizeof(T));
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.Usage = (m_updateStrategy == UpdateStrategy::MAP) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
        bufferDesc.CPUAccessFlags = (m_updateStrategy == UpdateStrategy::MAP) ? D3D11_CPU_ACCESS_WRITE : 0;

        // バッファの作成
        device->CreateBuffer(&bufferDesc, nullptr, &m_buffer);
    }

    /// <summary>
    /// 値が変更された場合のみ更新
    /// </summary>
    /// <param name="context">コンテキスト</param>
    /// <param name="data">データ</param>
    void UpdateIfNeeded(ID3D11DeviceContext* context, const T& data) 
    {
        // 安全チェック
        if (!m_buffer) return; 

        // 値が前回と同じなら更新しない
        if (std::memcmp(&m_cachedData, &data, sizeof(T)) == 0) return;

        // 更新を行う
        this->Update(context, data);
    }

    /// <summary>
    /// 強制更新処理
    /// </summary>
    /// <param name="context">コンテキスト</param>
    /// <param name="data">データ</param>
    void Update(ID3D11DeviceContext* context, const T& data) 
    {
        // 安全チェック
        if (!m_buffer) return;

        // MAPの場合
        if (m_updateStrategy == UpdateStrategy::MAP)
        {
            // GPUが使用するリソースのメモリにCPUからアクセスする際に利用する構造体
            D3D11_MAPPED_SUBRESOURCE mappedResource{};

            // 定数バッファをマップする
            context->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

            // マップされたGPUメモリ領域にCPU側のデータをコピーする
            std::memcpy(mappedResource.pData, &data, sizeof(T));

            // マップ解除
            context->Unmap(m_buffer.Get(), 0);

            // データを更新
            m_cachedData = data;
        }
        // UPDATE_SUB_RESOURCEの場合
        else
        {
            // バッファの更新
            context->UpdateSubresource(m_buffer.Get(), 0, nullptr, &data, 0, 0);
        }
    }

    /// <summary>
    /// バッファを取得する
    /// </summary>
    /// <returns>バッファ</returns>
    ID3D11Buffer* GetBuffer() const noexcept 
    {
        return m_buffer.Get();
    }

private:

    // バッファ
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
    // バッファデータ
    T m_cachedData{};  
    // アップデートの種類
    UpdateStrategy m_updateStrategy;
};