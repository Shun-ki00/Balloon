#pragma once

class Particle
{

public:

    // �l��ݒ肷��
    void SetParameters(
        const DirectX::SimpleMath::Vector3& position,
        const DirectX::SimpleMath::Vector3& velocity,
        const DirectX::SimpleMath::Vector3& acceleration,
        const float& lifetime,
        const float& startSize,
        const float& endSize,
        const DirectX::SimpleMath::Vector4& startColor,
        const DirectX::SimpleMath::Vector4& endColor
    );

    // ��Ԃ��擾
    bool GetIsActive() const { return m_isActive; }
    // ���_�f�[�^���擾
    DirectX::VertexPositionColorTexture GetVertexData() const { return m_inputData; }

public:

    // �R���X�g���N�^
	Particle();
    // �f�X�g���N�^
	~Particle() = default;

    // ����������
    void Initialize();
    // �X�V����
    void Update(const float& elapsedTime);
    
private:

    bool m_isActive;

    // ���_�f�[�^
    DirectX::VertexPositionColorTexture m_inputData;

    // ���W
    DirectX::SimpleMath::Vector3 m_position;
    // ��]�p
    float m_angle;

    // ���x
    DirectX::SimpleMath::Vector3 m_velocity;
    // �����x
    DirectX::SimpleMath::Vector3 m_acceleration;

    // �d�͒l
    float m_gravity;

    // ���C�t�^�C��
    float m_totalLifetime; // �ő����
    float m_currentLifetime; // �c�����

    // �T�C�Y���
    float m_startSize;
    float m_endSize;
    float m_currentSize;

    // �J���[���
    DirectX::SimpleMath::Vector4 m_startColor;
    DirectX::SimpleMath::Vector4 m_endColor;
    DirectX::SimpleMath::Vector4 m_currentColor;
};