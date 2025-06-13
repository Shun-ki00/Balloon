// ============================================
// 
// �t�@�C����: TweenManager.h
// �T�v: TweenManager.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Framework/Tween/Tween.h"

class Tween;
class CommonResources;


class TweenManager {

private:
	static constexpr int INITIAL_TWEEN_COUNT = 10;

private:
	//	�R���X�g���N�^
	TweenManager();
	// �f�X�g���N�^
	~TweenManager() = default;
public:
	TweenManager(const TweenManager&) = delete;             // �R�s�[�֎~
	TweenManager& operator=(const TweenManager&) = delete;  // �R�s�[����֎~
	TweenManager(const TweenManager&&) = delete;            // ���[�u�֎~
	TweenManager& operator=(const TweenManager&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static TweenManager* GetInstance()
	{
		static TweenManager instance;
		return &instance;
	}

public:
    // �X�V����
    void Update();
	// ��~����
	void Stop();
	// ��A�N�e�B�u��Tween���擾����
	Tween* GetTween();

private:
	// ���L���\�[�X
	CommonResources* m_commonResources;
    // tween���i�[
    std::vector<std::unique_ptr<Tween>> tweens;
};