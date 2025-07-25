// ============================================
// 
// ファイル名: KeyboardMessenger.cpp
// 概要: キーボードのメッセンジャー（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Game/Message/KeyboardMessenger.h"
#include "Framework/InputManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
KeyboardMessenger::KeyboardMessenger()
    :
    m_inputManager{},
    m_keyList{},
    m_isAttach{}
{
    // インスタンスを取得する
    m_inputManager = InputManager::GetInstance();
    // 初期化
    m_isAttach = false;
}

/// <summary>
/// アタッチする
/// </summary>
/// <param name="type">キーの押されたタイプ</param>
/// <param name="key">キー</param>
/// <param name="observer">オブジェクト</param>
void KeyboardMessenger::Attach(const KeyType& type, const DirectX::Keyboard::Keys& key, IObject* observer)
{
    // アタッチが許可されてなければ登録を行わない
    if (!m_isAttach || !observer) return;
	// 登録する
    m_keyList[type].emplace(key, observer);
}


/// <summary>
/// メッセージを送信する
/// </summary>
void KeyboardMessenger::Dispatch()
{
    // アタッチを行っている時は処理を行わない
    if (m_isAttach) return;

    for (const auto& [keyType, keyObservers] : m_keyList)
    {
        for (const auto& [key, observer] : keyObservers)
        {
            if (!observer) continue;

            bool isActive = false;
            switch (keyType)
            {
                case KeyType::ON_KEY:      isActive = m_inputManager->OnKey(key); break;    // キーが押され続けている
                case KeyType::ON_KEY_DOWN: isActive = m_inputManager->OnKeyDown(key); break;// キーが押された瞬間
                case KeyType::ON_KEY_UP:   isActive = m_inputManager->OnKeyUp(key); break;  // キーが離れた瞬間
            }

            // キーが押されていれば通知を送信
            if (isActive)
                observer->OnKeyPressed(keyType, key);
        }
    }
}

/// <summary>
/// アタッチ開始処理
/// </summary>
void KeyboardMessenger::Begin()
{
    // アタッチを許可
    m_isAttach = true;
    // リストの削除
    this->Clear();

}

/// <summary>
/// アタッチ終了処理
/// </summary>
void KeyboardMessenger::End()
{
    // アタッチ終了
    m_isAttach = false;
}

/// <summary>
/// 登録してあるものを全て削除する
/// </summary>
void KeyboardMessenger::Clear()
{
    // リストの削除
    m_keyList.clear();
}