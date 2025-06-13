#pragma once
#include "Game/Message/Message.h"
#include "Framework/InputManager.h"

class IObserver
{
public:
	// メッセージを受け取る
	virtual void OnMessegeAccepted(Message::MessageData messageData) = 0;
	// キーが押下げられたら時に呼び出される
	virtual void OnKeyPressed(KeyType type , const DirectX::Keyboard::Keys& key) = 0;
};