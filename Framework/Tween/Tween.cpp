// ============================================
// 
// �t�@�C����: Tween.cpp
// �T�v: �I�u�W�F�N�g�̈ړ��E��]�E�X�P�[���ω����Ԃ���A�j���[�V��������������
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Framework/Tween/Tween.h"
#include "Game/Transform/Transform.h"
#include "Framework/Easing.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Tween::Tween()
    :
    m_transform(nullptr),
    m_onComplete(nullptr),
    m_startPosition{},
    m_endPosition{},
    m_startRotation{},
    m_endRotation{},
    m_startScale{},
    m_endScale{},
    m_isActive(false),
    m_doMove(false),
    m_doRotation(false),
    m_doScale(false),
    m_duration{},
    m_delay{},
    m_loopCount{},
    m_easeType(Tween::EasingType::Linear),
    m_loopType(Tween::LoopType::None),
    m_elapsed{}
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <returns></returns>
bool Tween::Update(float deltaTime)
{
    // �i�s���ł͂Ȃ��Ƃ��̓X�L�b�v
    if (!m_isActive) return false;
    // ���݂̎��Ԃ��X�V����
    m_elapsed += deltaTime;
    // �x��������ꍇ�͑ҋ@
    if (m_elapsed < m_delay) return false; 

    // Transform���r���Ŕj�����ꂽ��Tween���~����
    if (m_transform == nullptr)
    {
        this->Stop();
    }

    // �A�j���[�V�����̐i�s�x���v�Z�i0.0 �` 1.0 �ɐ��K���j
    float t = (m_elapsed - m_delay) / m_duration;
    // t �� 1.0 �ɃN�����v�i��Ԃ̏���𒴂��Ȃ��悤�ɂ���j
    if (t > 1.0f) t = 1.0f;

    // �C�[�W���O��K�p
    float easeT = EasingFunction(m_easeType, t);

    // �ړ����� (DoMove)
    if (m_doMove) 
        m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Lerp(m_startPosition, m_endPosition, easeT));
    // ��]���� (DoRotation)
    if (m_doRotation) 
        m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Slerp(m_startRotation, m_endRotation, easeT));
    // �X�P�[������ (DoScale)
    if (m_doScale) 
        m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::Lerp(m_startScale, m_endScale, easeT));

    // ���[�v����
    if (t >= 1.0f) 
    {
        // ���[�v���Ȃ��Ƃ�Tween���~�߂�
        if (m_loopType == Tween::LoopType::None)
        {
            // �A�j���[�V����������������R�[���o�b�N���Ăяo��
            if (m_onComplete)
            {
                m_onComplete();
            }
            this->Stop();
            return false;
        }
        // ���[�v�J�E���g���c���Ă��邩�`�F�b�N
        if (--m_loopCount <= 0)
        {
            // �A�j���[�V����������������R�[���o�b�N���Ăяo��
            if (m_onComplete)
            {
                m_onComplete();
            }
            this->Stop();
            return false;
        }

        DirectX::SimpleMath::Vector3    positionDelta;
        DirectX::SimpleMath::Quaternion rotationDelta;
        DirectX::SimpleMath::Vector3    scaleDelta;
    
        switch (m_loopType)
        {
            // �ړ���A�ŏ��̈ʒu����Ăшړ����J�n���܂�
            case Tween::LoopType::Restart:
                // ���Ԃ����Z�b�g
                m_elapsed = 0.0f;
                break;
            // �ړ���A�ŏ��̈ʒu�ɖ߂�悤�ɓ����܂�
            case Tween::LoopType::Yoyo:
                // �X�^�[�g�ƃG���h�����ւ���
                std::swap(m_startPosition, m_endPosition);
                std::swap(m_startRotation, m_endRotation);
                std::swap(m_startScale, m_endScale);
                // ���Ԃ����Z�b�g
                m_elapsed = 0.0f;
                break;
            // �ړ���A���̈ʒu����Ăшړ����J�n���܂�
            case Tween::LoopType::Increment:

                // �������v�Z
                positionDelta = m_endPosition - m_startPosition;
                m_startRotation.Inverse(m_startRotation);
                rotationDelta = m_endRotation * m_startRotation;
                scaleDelta    = m_endScale - m_startScale;

                // �X�^�[�g�n�_���G���h�ɐݒ�
                m_startPosition = m_endPosition;
                m_startRotation = m_endRotation;
                m_startScale    = m_endScale;
                // �G���h�n�_���X�V ������ǉ�
                m_endPosition += positionDelta;
                m_endRotation *= rotationDelta;
                m_endScale += scaleDelta;
                // ���Ԃ����Z�b�g
                m_elapsed = 0.0f;
                break;
            default:
                break;
        }
    }

    return m_isActive;
}

/// <summary>
/// �C�[�W���̓K��
/// </summary>
/// <param name="type"></param>
/// <param name="t"></param>
/// <returns></returns>
float Tween::EasingFunction(EasingType type, float t)
{
    using namespace easing;

    switch (type) {
        case EasingType::EaseInSine: return EaseInSine(t);
        case EasingType::EaseOutSine: return EaseOutSine(t);
        case EasingType::EaseInOutSine: return EaseInOutSine(t);
        case EasingType::EaseInQuad: return EaseInQuad(t);
        case EasingType::EaseOutQuad: return EaseOutQuad(t);
        case EasingType::EaseInOutQuad: return EaseInOutQuad(t);
        case EasingType::EaseInCubic: return EaseInCubic(t);
        case EasingType::EaseOutCubic: return EaseOutCubic(t);
        case EasingType::EaseInOutCubic: return EaseInOutCubic(t);
        case EasingType::EaseInQuart: return EaseInQuart(t);
        case EasingType::EaseOutQuart: return EaseOutQuart(t);
        case EasingType::EaseInOutQuart: return EaseInOutQuart(t);
        case EasingType::EaseInQuint: return EaseInQuint(t);
        case EasingType::EaseOutQuint: return EaseOutQuint(t);
        case EasingType::EaseInOutQuint: return EaseInOutQuint(t);
        case EasingType::EaseInExpo: return EaseInExpo(t);
        case EasingType::EaseOutExpo: return EaseOutExpo(t);
        case EasingType::EaseInOutExpo: return EaseInOutExpo(t);
        case EasingType::EaseInCirc: return EaseInCirc(t);
        case EasingType::EaseOutCirc: return EaseOutCirc(t);
        case EasingType::EaseInOutCirc: return EaseInOutCirc(t);
        case EasingType::EaseInBack: return EaseInBack(t);
        case EasingType::EaseOutBack: return EaseOutBack(t);
        case EasingType::EaseInOutBack: return EaseInOutBack(t);
        case EasingType::EaseInElastic: return EaseInElastic(t);
        case EasingType::EaseOutElastic: return EaseOutElastic(t);
        case EasingType::EaseInOutElastic: return EaseInOutElastic(t);
        case EasingType::EaseInBounce: return EaseInBounce(t);
        case EasingType::EaseOutBounce: return EaseOutBounce(t);
        case EasingType::EaseInOutBounce: return EaseInOutBounce(t);
        default: return t; // Linear
    }
}


void Tween::Play()
{
    m_isActive = true;
    m_elapsed = 0.0f;
}

/// <summary>
/// ��~����
/// </summary>
void Tween::Stop()
{
    // ��A�N�e�B�u�ɐݒ�
    m_isActive      = false;
    // Transform�̓o�^������
    m_transform     = nullptr;
    m_onComplete    = nullptr;
    // ���l�̃��Z�b�g
    m_doMove        = false;
    m_doRotation    = false;
    m_doScale       = false;
    m_startPosition = DirectX::SimpleMath::Vector3::Zero;
    m_endPosition   = DirectX::SimpleMath::Vector3::Zero;
    m_startRotation = DirectX::SimpleMath::Quaternion::Identity;
    m_endRotation   = DirectX::SimpleMath::Quaternion::Identity;
    m_startScale    = DirectX::SimpleMath::Vector3::Zero;
    m_endScale      = DirectX::SimpleMath::Vector3::Zero;
    m_duration      = 0.0f;
    m_delay         = 0.0f;
    m_loopCount     = 0;
    m_loopType      = Tween::LoopType::None;
    m_easeType      = Tween::EasingType::Linear;
}

/// <summary>
/// �w�肵�����W�ֈړ�����A�j���[�V������ݒ肷��B
/// </summary>
/// <param name="end">�ړ���̍��W</param>
/// <param name="duration">�ړ��ɂ����鎞��</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween &Tween::DOMove(const DirectX::SimpleMath::Vector3& end, float duration)
{
    m_startPosition = m_transform->GetLocalPosition();
    m_endPosition   = end;
    m_duration = duration;
    m_doMove = true;
    return *this;
}

/// <summary>
/// X�������̈ړ��A�j���[�V������ݒ肷��B
/// </summary>
/// <param name="endX">X���̈ړ�����W</param>
/// <param name="duration">�ړ��ɂ����鎞��</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween& Tween::DOMoveX(float endX, float duration)
{
    m_startPosition = m_transform->GetLocalPosition();
    m_endPosition = {endX,m_startPosition.y,m_startPosition.z};
    m_duration = duration;
    m_doMove = true;
    return *this;
}

/// <summary>
/// Y�������̈ړ��A�j���[�V������ݒ肷��B
/// </summary>
/// <param name="endY">Y���̈ړ�����W</param>
/// <param name="duration">�ړ��ɂ����鎞��</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween& Tween::DOMoveY(float endY, float duration)
{
    m_startPosition = m_transform->GetLocalPosition();
    m_endPosition = { m_startPosition.x,endY,m_startPosition.z };
    m_duration = duration;
    m_doMove = true;
    return *this;
}

/// <summary>
/// Z�������̈ړ��A�j���[�V������ݒ肷��B
/// </summary>
/// <param name="endZ">Z���̈ړ�����W</param>
/// <param name="duration">�ړ��ɂ����鎞��</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween& Tween::DOMoveZ(float endZ, float duration)
{
    m_startPosition = m_transform->GetLocalPosition();
    m_endPosition = { m_startPosition.x,m_startPosition.y,endZ };
    m_duration = duration;
    m_doMove = true;
    return *this;
}

/// <summary>
/// �w�肵����]�p�x�։�]����A�j���[�V������ݒ肷��B
/// </summary>
/// <param name="end">��]�̏I���p�x�i�x���@�j</param>
/// <param name="duration">��]�ɂ����鎞��</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween& Tween::DORotation(const DirectX::SimpleMath::Vector3& end, float duration)
{
    m_startRotation = m_transform->GetLocalRotation();
    // �N�H�[�^�j�I���ɕϊ�
    m_endRotation = this->ConvertToYawPitchRoll(end);
    m_duration = duration;
    m_doRotation = true;
    return *this;
}

/// <summary>
/// X���̉�]�A�j���[�V������ݒ肷��B
/// </summary>
/// <param name="endX">X���̉�]�I���p�x�i�x���@�j</param>
/// <param name="duration">��]�ɂ����鎞��</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween& Tween::DORotationX(float endX, float duration)
{
    m_startRotation = m_transform->GetLocalRotation();
    // �x���@�ɒ���
    DirectX::SimpleMath::Vector3 endRotation = this->ConvertToDegrees(m_startRotation.ToEuler());
    // X�̂ݏI���l��ύX
    endRotation.x = endX;
    // �N�H�[�^�j�I���ɕϊ�
    m_endRotation = this->ConvertToYawPitchRoll(endRotation);

    m_duration = duration;
    m_doRotation = true;
    return *this;
}

/// <summary>
/// Y���̉�]�A�j���[�V������ݒ肷��B
/// </summary>
/// <param name="endY">Y���̉�]�I���p�x�i�x���@�j</param>
/// <param name="duration">��]�ɂ����鎞��</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween& Tween::DORotationY(float endY, float duration)
{
    m_startRotation = m_transform->GetLocalRotation();
    // �x���@�ɒ���
    DirectX::SimpleMath::Vector3 endRotation = this->ConvertToDegrees(m_startRotation.ToEuler());
    // Y�̂ݏI���l��ύX
    endRotation.y = endY;
    // �N�H�[�^�j�I���ɕϊ�
    m_endRotation = this->ConvertToYawPitchRoll(endRotation);
    m_duration = duration;
    m_doRotation = true;
    return *this;
}

/// <summary>
/// Z���̉�]�A�j���[�V������ݒ肷��B
/// </summary>
/// <param name="endZ">Z���̉�]�I���p�x�i�x���@�j</param>
/// <param name="duration">��]�ɂ����鎞��</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween& Tween::DORotationZ(float endZ, float duration)
{
    m_startRotation = m_transform->GetLocalRotation();
    // �x���@�ɒ���
    DirectX::SimpleMath::Vector3 endRotation = this->ConvertToDegrees(m_startRotation.ToEuler());
    // Z�̂ݏI���l��ύX
    endRotation.z = endZ;
    // �N�H�[�^�j�I���ɕϊ�
    m_endRotation = this->ConvertToYawPitchRoll(endRotation);
    m_duration = duration;
    m_doRotation = true;
    return *this;
}


/// <summary>
/// �w�肵���X�P�[���֕ύX����A�j���[�V������ݒ肷��B
/// </summary>
/// <param name="end">�X�P�[���̏I���l</param>
/// <param name="duration">�X�P�[���ύX�ɂ����鎞��</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween& Tween::DOScale(const DirectX::SimpleMath::Vector3& end, float duration)
{
    m_startScale = m_transform->GetLocalScale();
    m_endScale = end;
    m_duration = duration;
    m_doScale = true;
    return *this;
}

/// <summary>
/// X���̃X�P�[���ύX�A�j���[�V������ݒ肷��B
/// </summary>
/// <param name="endX">X���̃X�P�[���I���l</param>
/// <param name="duration">�X�P�[���ύX�ɂ����鎞��</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween& Tween::DOScaleX(float endX, float duration)
{
    m_startScale = m_transform->GetLocalScale();
    m_endScale = { endX,m_startScale.y,m_startScale.z };
    m_duration = duration;
    m_doScale = true;
    return *this;
}

/// <summary>
/// Y���̃X�P�[���ύX�A�j���[�V������ݒ肷��B
/// </summary>
/// <param name="endY">Y���̃X�P�[���I���l</param>
/// <param name="duration">�X�P�[���ύX�ɂ����鎞��</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween& Tween::DOScaleY(float endY, float duration)
{
    m_startScale = m_transform->GetLocalScale();
    m_endScale = { m_startScale.x,endY,m_startScale.z };
    m_duration = duration;
    m_doScale = true;
    return *this;
}

/// <summary>
/// Z���̃X�P�[���ύX�A�j���[�V������ݒ肷��B
/// </summary>
/// <param name="endZ">Z���̃X�P�[���I���l</param>
/// <param name="duration">�X�P�[���ύX�ɂ����鎞��</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween& Tween::DOScaleZ(float endZ, float duration)
{
    m_startScale = m_transform->GetLocalScale();
    m_endScale = { m_startScale.x,m_startScale.y,endZ };
    m_duration = duration;
    m_doScale = true;
    return *this;
}

/// <summary>
/// �C�[�W���O�̎�ނ�ݒ肷��B
/// </summary>
/// <param name="ease">�C�[�W���O�̎��</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween& Tween::SetEase(Tween::EasingType ease)
{
    m_easeType = ease;
    return *this;
}

/// <summary>
/// ���[�v�񐔂ƃ��[�v�̎�ނ�ݒ肷��B
/// </summary>
/// <param name="count">���[�v��</param>
/// <param name="type">���[�v�̎��</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween& Tween::SetLoops(int count, Tween::LoopType type)
{
    m_loopCount = count;
    m_loopType = type;
    return *this;
}

/// <summary>
/// �x�����Ԃ�ݒ肷��B
/// </summary>
/// <param name="delayTime">�x������</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween &Tween::SetDelay(float delayTime)
{
    m_delay = delayTime;
    return *this;
}

/// <summary>
/// �A�j���[�V�����������̃R�[���o�b�N��ݒ肷��B
/// </summary>
/// <param name="callback">�������̃R�[���o�b�N�֐�</param>
/// <returns>���g��Tween�I�u�W�F�N�g</returns>
Tween& Tween::OnComplete(Callback callback)
{
    m_onComplete = callback;
    return *this;
}

/// <summary>
/// ��]�x�N�g�����N�H�[�^�j�I���ɕϊ�����B
/// </summary>
/// <param name="rotation">��]��\���x�N�g���i�x���@�j</param>
/// <returns>�ϊ���̃N�H�[�^�j�I��</returns>
DirectX::SimpleMath::Quaternion Tween::ConvertToYawPitchRoll(const DirectX::SimpleMath::Vector3& rotation) {
    return DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
        DirectX::XMConvertToRadians(rotation.y),
        DirectX::XMConvertToRadians(rotation.x),
        DirectX::XMConvertToRadians(rotation.z)
    );
}

/// <summary>
/// ���W�A���P�ʂ̃x�N�g����x���i�f�O���[�j�ɕϊ�����B
/// </summary>
/// <param name="radianVec">�ϊ��Ώۂ̃x�N�g���i���W�A���P�ʁj</param>
/// <returns>�ϊ���̃x�N�g���i�x���@�j</returns>
DirectX::SimpleMath::Vector3 Tween::ConvertToDegrees(const DirectX::SimpleMath::Vector3& radianVec)
{
    return {
        DirectX::XMConvertToDegrees(radianVec.x),
        DirectX::XMConvertToDegrees(radianVec.y),
        DirectX::XMConvertToDegrees(radianVec.z)
    };
}