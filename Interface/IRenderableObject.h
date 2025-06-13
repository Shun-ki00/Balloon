#pragma once


class IRenderableObject {

public:
    // �A�N�e�B�u��Ԃ�ݒ�
    virtual void SetIsActive(const bool& active) = 0;
    // �A�N�e�B�u��Ԃ��擾
    virtual bool GetIsActive() const = 0;

    // �萔�o�b�t�@���X�V����
    virtual void UpdateConstantBufferIfNeeded(ID3D11DeviceContext* context) = 0;
    // �萔�o�b�t�@���擾����
    virtual ID3D11Buffer* GetConstantBuffer() const = 0;

    // �X�V����
    virtual void Update(ID3D11DeviceContext* context, const DirectX::SimpleMath::Matrix& worldMatrix) = 0;
    // �`�揈��
    virtual void Render(ID3D11DeviceContext* context, DirectX::CommonStates* commonStates,
        DirectX::SimpleMath::Matrix viewMatrix, DirectX::SimpleMath::Matrix projectionMatrix
    ) = 0;

    virtual ~IRenderableObject() = default;
};