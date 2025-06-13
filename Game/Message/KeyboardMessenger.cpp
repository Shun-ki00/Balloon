#include "pch.h"
#include "Game/Message/KeyboardMessenger.h"
#include "Framework/InputManager.h"


KeyboardMessenger::KeyboardMessenger()
{
    // インスタンスを取得する
    m_inputManager = InputManager::GetInstance();

    m_isAttach = false;
}

void KeyboardMessenger::Attach(const KeyType& type, const DirectX::Keyboard::Keys& keys, IObject* observer)
{
    // アタッチが許可されてなければ登録を行わない
    if (!m_isAttach) return;

	// 登録する
	m_observerList[type].emplace(keys, observer);
}



void KeyboardMessenger::Dispatch()
{
    // アタッチを行っている時は処理を行わない
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
    // アタッチを許可
    m_isAttach = true;
    // リストの削除
    this->RemoveObserver();

}

void KeyboardMessenger::End()
{
    // アタッチ終了
    m_isAttach = false;
}


void KeyboardMessenger::RemoveObserver()
{
    // リストの削除
    m_observerList.clear();
}