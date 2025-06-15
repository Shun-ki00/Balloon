#pragma once
#include <wrl/client.h>
#include <cstring> // for std::memcmp
#include <type_traits>
#include "Game/Buffers.h"


// �A�b�v�f�[�g�̎��
enum class UpdateStrategy
{
    MAP,
    UPDATE_SUB_RESOURCE,
};


template<typename T>
class ConstantBuffer {
    static_assert(std::is_trivially_copyable_v<T>, "ConstantBuffer<T>: T must be trivially copyable");

public:

    // �f�t�H���g�R���X�g���N�^
    ConstantBuffer() = default;


    /// <summary>
    /// ����������
    /// </summary>
    /// <param name="device"></param>
    /// <returns></returns>
    void Initialize(ID3D11Device* device, UpdateStrategy strategy = UpdateStrategy::MAP)
    {
        // �X�V���[�h�ݒ�
        m_updateStrategy = strategy;

        // �萔�o�b�t�@�p�̃o�b�t�@�I�u�W�F�N�g���쐬����
        D3D11_BUFFER_DESC bufferDesc{};
        bufferDesc.ByteWidth = static_cast<UINT>(sizeof(T));
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.Usage = (m_updateStrategy == UpdateStrategy::MAP) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
        bufferDesc.CPUAccessFlags = (m_updateStrategy == UpdateStrategy::MAP) ? D3D11_CPU_ACCESS_WRITE : 0;

        // �o�b�t�@�̍쐬
        device->CreateBuffer(&bufferDesc, nullptr, &m_buffer);
    }

    /// <summary>
    /// �l���ύX���ꂽ�ꍇ�̂ݍX�V
    /// </summary>
    /// <param name="context">�R���e�L�X�g</param>
    /// <param name="data">�f�[�^</param>
    void UpdateIfNeeded(ID3D11DeviceContext* context, const T& data) 
    {
        // ���S�`�F�b�N
        if (!m_buffer) return; 

        // �l���O��Ɠ����Ȃ�X�V���Ȃ�
        if (std::memcmp(&m_cachedData, &data, sizeof(T)) == 0) return;

        // �X�V���s��
        this->Update(context, data);
    }

    /// <summary>
    /// �����X�V����
    /// </summary>
    /// <param name="context">�R���e�L�X�g</param>
    /// <param name="data">�f�[�^</param>
    void Update(ID3D11DeviceContext* context, const T& data) 
    {
        // ���S�`�F�b�N
        if (!m_buffer) return;

        // MAP�̏ꍇ
        if (m_updateStrategy == UpdateStrategy::MAP)
        {
            // GPU���g�p���郊�\�[�X�̃�������CPU����A�N�Z�X����ۂɗ��p����\����
            D3D11_MAPPED_SUBRESOURCE mappedResource{};

            // �萔�o�b�t�@���}�b�v����
            context->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

            // �}�b�v���ꂽGPU�������̈��CPU���̃f�[�^���R�s�[����
            std::memcpy(mappedResource.pData, &data, sizeof(T));

            // �}�b�v����
            context->Unmap(m_buffer.Get(), 0);

            // �f�[�^���X�V
            m_cachedData = data;
        }
        // UPDATE_SUB_RESOURCE�̏ꍇ
        else
        {
            // �o�b�t�@�̍X�V
            context->UpdateSubresource(m_buffer.Get(), 0, nullptr, &data, 0, 0);
        }
    }

    /// <summary>
    /// �o�b�t�@���擾����
    /// </summary>
    /// <returns>�o�b�t�@</returns>
    ID3D11Buffer* GetBuffer() const noexcept 
    {
        return m_buffer.Get();
    }

private:

    // �o�b�t�@
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
    // �o�b�t�@�f�[�^
    T m_cachedData{};  
    // �A�b�v�f�[�g�̎��
    UpdateStrategy m_updateStrategy;
};