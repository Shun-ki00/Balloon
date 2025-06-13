// ============================================
// 
// �t�@�C����: Tween.h
// �T�v: Tween.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once

class Transform;

class Tween
{
public:
    // �R�[���o�b�N�֐��^
    using Callback = std::function<void()>;  
public:
        // Yoyo	     �ړ���A�ŏ��̈ʒu�ɖ߂�悤�ɓ����܂�
        // Restart	 �ړ���A�ŏ��̈ʒu����Ăшړ����J�n���܂�
        // Increment �ړ���A���̈ʒu����Ăшړ����J�n���܂�
    enum class LoopType { None , Restart, Yoyo, Increment };
    // �C�[�W���O�̎��
    enum class EasingType {
        Linear,         // ���j�A��ԁi�f�t�H���g�j
        EaseInSine,
        EaseOutSine,
        EaseInOutSine,
        EaseInQuad,
        EaseOutQuad,
        EaseInOutQuad,
        EaseInCubic,
        EaseOutCubic,
        EaseInOutCubic,
        EaseInQuart,
        EaseOutQuart,
        EaseInOutQuart,
        EaseInQuint,
        EaseOutQuint,
        EaseInOutQuint,
        EaseInExpo,
        EaseOutExpo,
        EaseInOutExpo,
        EaseInCirc,
        EaseOutCirc,
        EaseInOutCirc,
        EaseInBack,
        EaseOutBack,
        EaseInOutBack,
        EaseInElastic,
        EaseOutElastic,
        EaseInOutElastic,
        EaseInBounce,
        EaseOutBounce,
        EaseInOutBounce
    };

    // �i�s��Ԃ��擾����
    bool GetIsActive() { return m_isActive; }
    // Transform��ݒ肷��
    void SetTransform(Transform* transform) { m_transform = transform; }

    // DOMove���\�b�h
    Tween& DOMove(const DirectX::SimpleMath::Vector3& end, float duration);
    Tween& DOMoveX(float endX, float duration);
    Tween& DOMoveY(float endY, float duration);
    Tween& DOMoveZ(float endZ, float duration);

    // DORotation���\�b�h
    Tween& DORotation(const DirectX::SimpleMath::Vector3& end, float duration);
    Tween& DORotationX(float endX, float duration);
    Tween& DORotationY(float endY, float duration);
    Tween& DORotationZ(float endZ, float duration);

    // DOScale���\�b�h
    Tween& DOScale(const DirectX::SimpleMath::Vector3& end, float duration);
    Tween& DOScaleX(float endX, float duration);
    Tween& DOScaleY(float endY, float duration);
    Tween& DOScaleZ(float endZ, float duration);

    // �x���ݒ�
    Tween& SetDelay(float delayTime);
    // ���[�v�ݒ�
    Tween& SetLoops(int count, Tween::LoopType type);
    // �C�[�W���O�ݒ�
    Tween& SetEase(Tween::EasingType ease);
    // �������̏�����ݒ�
    Tween& OnComplete(Callback callback);

    // �Đ�
    void Play();
    // ��~
    void Stop();
    // �X�V����
    bool Update(float deltaTime);
   
    // �R���X�g���N�^
    Tween();
    // �f�X�g���N�^
    ~Tween() = default;

    // �C�[�W���O�̓K��
    static float EasingFunction(EasingType type, float t);
    // ��]�x�N�g�����N�H�[�^�j�I���ɕϊ�����
    DirectX::SimpleMath::Quaternion ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation);
    // ���W�A����x���ɕϊ�����
    DirectX::SimpleMath::Vector3 ConvertToDegrees(const DirectX::SimpleMath::Vector3& radianVec);

private:

    // �^�[�Q�b�g��Transform
    Transform* m_transform;
    
    // �ړ�
    DirectX::SimpleMath::Vector3 m_startPosition;
    DirectX::SimpleMath::Vector3 m_endPosition;
    // ��]
    DirectX::SimpleMath::Quaternion m_startRotation;
    DirectX::SimpleMath::Quaternion m_endRotation;
    // �X�P�[��
    DirectX::SimpleMath::Vector3 m_startScale;
    DirectX::SimpleMath::Vector3 m_endScale;

    // �e�����̗L���t���O
    bool m_doMove;
    bool m_doRotation;
    bool m_doScale;
    // �i�s�����ǂ���
    bool m_isActive;

    // ����
    float m_duration;
    // �x������
    float m_delay;
    // ���[�v�J�E���g
    int m_loopCount;

    // ���[�v�^�C�v
    Tween::LoopType m_loopType;
    // �C�[�W���O�^�C�v
    Tween::EasingType m_easeType;

    // �������ɌĂяo���֐�
    Callback m_onComplete;

    // �o�ߎ���
    float m_elapsed;
};

