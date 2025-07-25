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
/// <param name="key">�L�[</param>
/// <param name="observer">�I�u�W�F�N�g</param>
void KeyboardMessenger::Attach(const KeyType& type, const DirectX::Keyboard::Keys& key, IObject* observer)
{
    // �A�^�b�`��������ĂȂ���Γo�^���s��Ȃ�
    if (!m_isAttach || !observer) return;
	// �o�^����
    m_keyList[type].emplace(key, observer);
}


/// <summary>
/// ���b�Z�[�W�𑗐M����
/// </summary>
void KeyboardMessenger::Dispatch()
{
    // �A�^�b�`���s���Ă��鎞�͏������s��Ȃ�
    if (m_isAttach) return;

    for (const auto& [keyType, keyObservers] : m_keyList)
    {
        for (const auto& [key, observer] : keyObservers)
        {
            if (!observer) continue;

            bool isActive = false;
            switch (keyType)
            {
                case KeyType::ON_KEY:      isActive = m_inputManager->OnKey(key); break;    // �L�[�������ꑱ���Ă���
                case KeyType::ON_KEY_DOWN: isActive = m_inputManager->OnKeyDown(key); break;// �L�[�������ꂽ�u��
                case KeyType::ON_KEY_UP:   isActive = m_inputManager->OnKeyUp(key); break;  // �L�[�����ꂽ�u��
            }

            // �L�[��������Ă���Βʒm�𑗐M
            if (isActive)
                observer->OnKeyPressed(keyType, key);
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