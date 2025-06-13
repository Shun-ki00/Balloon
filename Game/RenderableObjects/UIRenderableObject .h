#pragma once
#include "Interface/IRenderableObject.h"
#include "Game/Buffers.h"
#include "Framework/Resources/ResourceKeys.h"

class Resources;

class UIRenderableObject : public IRenderableObject
{
public:

    // �A�N�e�B�u��Ԃ�ݒ�
    void SetIsActive(const bool& active) override { m_isAcitve = active; }
    // �A�N�e�B�u��Ԃ��擾
    bool GetIsActive() const override { return m_isAcitve; }

    // ���W��ݒ�
    void SetPosition(const DirectX::SimpleMath::Vector3& position) { 
        m_uiVertexBuffer.position = { position.x , position.y ,position.z, 1.0f}; }
    // ��]��ݒ�
    void SetRotate(const float& rotate) { m_uiVertexBuffer.rotate.z = rotate; }
    // �傫����ݒ�
    void SetScale(DirectX::SimpleMath::Vector2 scale) { 
        m_uiVertexBuffer.rotate.x = scale.x; m_uiVertexBuffer.rotate.y = scale.y; }
    // UV���W�̃I�t�Z�b�g��ݒ�
    void SetUvOffset(DirectX::SimpleMath::Vector2 offset) { 
        m_uiVertexBuffer.rect.x = offset.x; m_uiVertexBuffer.rect.y = offset.y; }
    // �e�N�X�`���̕�������ݒ�
    void SetUvScale(DirectX::SimpleMath::Vector2 scale) {
        m_uiVertexBuffer.rect.z = scale.x; m_uiVertexBuffer.rect.x = scale.y;
    }
    // �e�N�X�`���̃T�C�Y��ݒ�
    void SetTextureSize(DirectX::SimpleMath::Vector2 size) { m_uiVertexBuffer.size = size; }
    // �J���[�̐ݒ�
    void SetColor(DirectX::SimpleMath::Vector4 color) { m_uiVertexBuffer.color = color; }

    // ���[�����
    // ���[���摜���g�p���邩�ǂ�����ݒ�
    void SetUseRuleTexture(const float& useTexture) { m_uiVertexBuffer.rule.x = useTexture; }
    // ���[���摜�̐i�s�x��ݒ�
    void SetRuleProgress(const float& progress) { m_uiVertexBuffer.rule.y = progress; }
    // ���[���摜�̔��]��ݒ�
    void SetRuleInverse(const float& inverse) { m_uiVertexBuffer.rule.z = inverse; }

    // ���_�o�b�t�@�f�[�^���擾����
    UIVertexBuffer GetVertexBufferData() const { return m_uiVertexBuffer; }

    // �s�N�Z���V�F�[�_�[���擾����
    ID3D11PixelShader* GetPixelShader() const { return m_pixelShader; }

    // �e�N�X�`�����擾����
    ID3D11ShaderResourceView* GetTexture() const { return m_texture; }
    // ���[���摜���擾����
    ID3D11ShaderResourceView* GetRuleTexture() const { return m_ruleTexture; }

public:

    // �R���X�g���N�^
    UIRenderableObject();
    // �f�X�g���N�^
    ~UIRenderableObject() override = default;

    // �萔�o�b�t�@���X�V����
    void UpdateConstantBufferIfNeeded(ID3D11DeviceContext* context) {}
    // �萔�o�b�t�@���擾����
    ID3D11Buffer* GetConstantBuffer() const { return nullptr; }

    // ����������
    void Initialize(const UIVertexBuffer& vertexBuffer,TextureKeyID baseTexture, TextureKeyID ruleTexture, PS_ID psId);
    // �X�V����
    void Update(ID3D11DeviceContext* context, const DirectX::SimpleMath::Matrix& worldMatrix) override;
    // �`�揈��
    void Render(ID3D11DeviceContext* context, DirectX::CommonStates* commonStates,
        DirectX::SimpleMath::Matrix viewMatrix, DirectX::SimpleMath::Matrix projectionMatrix
    ) override;

private:

    // �A�N�e�B�u����
    bool m_isAcitve;

    // ���\�[�X
    Resources* m_resources;
    // �f�o�C�X
    ID3D11Device1* m_device;

    // �s�N�Z���V�F�[�_�[
    ID3D11PixelShader* m_pixelShader;

    // ���_�o�b�t�@
    UIVertexBuffer m_uiVertexBuffer;

    // ���C���e�N�X�`��
    ID3D11ShaderResourceView* m_texture;
    // ���[���摜
    ID3D11ShaderResourceView* m_ruleTexture;
};