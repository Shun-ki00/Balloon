#include "pch.h"
#include "Game/Object/Object.h"

// オブジェクト番号
int Object::s_objectNumber = 0;

// オブジェクトをカウントアップする
int Object::CountUpNumber() { return s_objectNumber++; }

// 現在のオブジェクトのカウントを取得する
int Object::ResetNumber() { return s_objectNumber = 0; }


// コンストラクタ
Object::Object(const float& maxTurnRate, const float& maxSpeed, const float& maxForce, const float& mass)
	:
	m_currentState{},			// 現在の状態
	m_currentMessage{},		    // 現在のメッセージ
	m_maxTurnRate(maxTurnRate), // 回転するときの最大速度
	m_maxSpeed(maxSpeed),		// 最大移動速度
	m_maxForce(maxForce),		// 最大力
	m_mass(mass)				// 質量					
{
}

// デストラクタ
Object::~Object()
{
}

// 初期化する
void Object::Initialize()
{
}

// 更新する
void Object::Update(const float& elapsedTime)
{
	m_currentState->Update(elapsedTime);
}


// 後処理を行う
void Object::Finalize()
{
}