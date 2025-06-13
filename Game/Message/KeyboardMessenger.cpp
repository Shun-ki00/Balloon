#include "pch.h"
#include "Game/Message/KeyboardMessenger.h"
#include "Framework/InputManager.h"


KeyboardMessenger::KeyboardMessenger()
{
    // �C���X�^���X���擾����
    m_inputManager = InputManager::GetInstance();

    m_isAttach = false;
}

void KeyboardMessenger::Attach(const KeyType& type, const DirectX::Keyboard::Keys& keys, IObject* observer)
{
    // �A�^�b�`��������ĂȂ���Γo�^���s��Ȃ�
    if (!m_isAttach) return;

	// �o�^����
	m_observerList[type].emplace(keys, observer);
}



void KeyboardMessenger::Dispatch()
{
    // �A�^�b�`���s���Ă��鎞�͏������s��Ȃ�
    if (m_isAttach) return;

    for (const auto& [keyType, multimap] : m_observerList)
    {
        for (const auto& [key, observer] : multimap)
        {
            bool isActive = false;

            switch (keyType)
            {
                case KeyType::ON_KEY:
                    isActive = m_inputManager->OnKey(key);
                    break;
                case KeyType::ON_KEY_DOWN:
                    isActive = m_inputManager->OnKeyDown(key);
                    break;
                case KeyType::ON_KEY_UP:
                    isActive = m_inputManager->OnKeyUp(key);
                    break;
            }

            if (isActive)
            {
                observer->OnKeyPressed(keyType, key);
            }
        }
    }
}

void KeyboardMessenger::Begin()
{
    // �A�^�b�`������
    m_isAttach = true;
    // ���X�g�̍폜
    this->RemoveObserver();

}

void KeyboardMessenger::End()
{
    // �A�^�b�`�I��
    m_isAttach = false;
}


void KeyboardMessenger::RemoveObserver()
{
    // ���X�g�̍폜
    m_observerList.clear();
}