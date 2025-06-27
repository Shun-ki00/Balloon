// ============================================
// 
// �t�@�C����: KeyboardMessenger.cpp
// �T�v: �L�[�{�[�h�̃��b�Z���W���[�i�V���O���g���j
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Game/Message/KeyboardMessenger.h"
#include "Framework/InputManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
KeyboardMessenger::KeyboardMessenger()
    :
    m_inputManager{},
    m_keyList{},
    m_isAttach{}
{
    // �C���X�^���X���擾����
    m_inputManager = InputManager::GetInstance();
    // ������
    m_isAttach = false;
}

/// <summary>
/// �A�^�b�`����
/// </summary>
/// <param name="type">�L�[�̉����ꂽ�^�C�v</param>
/// <param name="keys">�L�[</param>
/// <param name="observer">�I�u�W�F�N�g</param>
void KeyboardMessenger::Attach(const KeyType& type, const DirectX::Keyboard::Keys& keys, IObject* observer)
{
    // �A�^�b�`��������ĂȂ���Γo�^���s��Ȃ�
    if (!m_isAttach) return;

	// �o�^����
    m_keyList[type].emplace(keys, observer);
}


/// <summary>
/// ���b�Z�[�W�𑗐M����
/// </summary>
void KeyboardMessenger::Dispatch()
{
    // �A�^�b�`���s���Ă��鎞�͏������s��Ȃ�
    if (m_isAttach) return;

    for (const auto& [keyType, multimap] : m_keyList)
    {
        for (const auto& [key, observer] : multimap)
        {
            bool isActive = false;

            // ���͏�Ԃ��`�F�b�N
            switch (keyType)
            {
                case KeyType::ON_KEY: // �L�[�������ꑱ���Ă���
                    isActive = m_inputManager->OnKey(key);
                    break;
                case KeyType::ON_KEY_DOWN: // �L�[�������ꂽ�u��
                    isActive = m_inputManager->OnKeyDown(key);
                    break;
                case KeyType::ON_KEY_UP: // �L�[�����ꂽ�u��
                    isActive = m_inputManager->OnKeyUp(key);
                    break;
            }

            // �L�[��������Ă���Βʒm�𑗐M
            if (isActive)
            {
                observer->OnKeyPressed(keyType, key);
            }
        }
    }
}

/// <summary>
/// �A�^�b�`�J�n����
/// </summary>
void KeyboardMessenger::Begin()
{
    // �A�^�b�`������
    m_isAttach = true;
    // ���X�g�̍폜
    this->Clear();

}

/// <summary>
/// �A�^�b�`�I������
/// </summary>
void KeyboardMessenger::End()
{
    // �A�^�b�`�I��
    m_isAttach = false;
}

/// <summary>
/// �o�^���Ă�����̂�S�č폜����
/// </summary>
void KeyboardMessenger::Clear()
{
    // ���X�g�̍폜
    m_keyList.clear();
}