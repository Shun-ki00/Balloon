// ============================================
// 
// ファイル名: IComposite.h
// 概要: 複数オブジェクトの構成・分離を定義する（インターフェース）
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IObject.h"

class IComposite
{
public:
	// オブジェクトを追加する
	virtual void Attach(std::unique_ptr<IObject> object) = 0;
	// オブジェクトを削除する
	virtual void Detach(std::unique_ptr<IObject> object)  = 0;
};

