#pragma once
#include "Interface/IRenderableObject.h"
#include "Game/Buffers/ConstantBuffer.h"
#include "Game/Buffers.h"

class Resources;
class AmbientLight;

class WoodBoxRenderableObject : public IRenderableObject
{
public:

    // �A�N�e�B�u��Ԃ�ݒ�
    void SetIsActive(const bool& active) override { m_isAcitve = active; }
    // �A�N�e�B�u��Ԃ��擾
    bool GetIsActive() const override { return m_isAcitve; }

    // ���f�����擾����
    DirectX::Model* GetModel() const override { return m_model; }

    // ���[���h�s����擾����
    DirectX::SimpleMath::Matrix GetWorldMatrix() const override { return m_worldMatrix; }
    // ���[���h�s���ݒ肷��
    void SetWorldMatrix(const DirectX::SimpleMath::Matrix& worldMatrix) { m_worldMatrix = worldMatrix; }

    // �萔�o�b�t�@���擾����
    ID3D11Buffer* GetConstantBuffer() const override;

    // �萔�o�b�t�@�̃f�[�^���X�V����
    void SetConstantBufferData(const PBRLitConstantBuffer& constants) { m_constants = constants; }


    // ����������
    void Initialize(const PBRLitConstantBuffer& constants);
    // �X�V����
    void Update(ID3D11DeviceContext* context , const DirectX::SimpleMath::Matrix& worldMatrix) override;
    // �`����s��
    void Render(ID3D11DeviceContext* context, DirectX::CommonStates* commonStates ,
        DirectX::SimpleMath::Matrix viewMatrix , DirectX::SimpleMath::Matrix projectionMatrix,
        ID3D11ShaderResourceView* shadowMap = nullptr
        ) override;
    // �R���X�g���N�^
    WoodBoxRenderableObject(const bool &isActive ,DirectX::Model* model);
    // �f�X�g���N�^
    ~WoodBoxRenderableObject() override = default;

private:
    // �l���ύX���ꂽ�ꍇ�X�V�������s��
    void UpdateConstantBufferIfNeeded(ID3D11DeviceContext* context) override;

    void CreateLightBuffer();

private:

    // �A�N�e�B�u����
    bool m_isAcitve;
    
    // ���\�[�X
    Resources* m_resources;
    // �f�o�C�X
    ID3D11Device1* m_device;

    AmbientLight* m_ambientLight;

    // �C���v�b�g���C�A�E�g
    ID3D11InputLayout* m_inputLayout;
    // ���_�V�F�[�_�[
    ID3D11VertexShader* m_vertexShader;
    // �s�N�Z���V�F�[�_�[
    ID3D11PixelShader* m_pixelShader;
  
    // �萔�o�b�t�@�ɑ���f�[�^
    PBRLitConstantBuffer m_constants;
    // �萔�o�b�t�@
    std::unique_ptr<ConstantBuffer<PBRLitConstantBuffer>> m_constantBuffer;
     // ���C�g�p�̒萔�o�b�t�@
    std::unique_ptr<ConstantBuffer<DirectionalLightBuffer>> m_constantLightBuffer;

    // �T���v��
    Microsoft::WRL::ComPtr<ID3D11SamplerState> m_shadowMapSampler;

    // ���f��
    DirectX::Model* m_model;

    // ���C���e�N�X�`��
    ID3D11ShaderResourceView* m_baseMap;
    // �m�[�}���}�b�v
    ID3D11ShaderResourceView* m_normalMap;
    // ���}�b�v
    ID3D11ShaderResourceView* m_skyMap;

    // ���[���h�s��
    DirectX::SimpleMath::Matrix m_worldMatrix;
};