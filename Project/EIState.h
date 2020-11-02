//�G�̏�Ԃ̃C���^�[�t�F�[�X�N���X
#pragma once
#include<memory>
#include"StepTimer.h"
#include"Enemy.h"
#include"DebugFont.h"

class Enemy;
class EIState
{
public:
	virtual void Initialize(Enemy* enemy) = 0;
	virtual void Update(float elapsedTime) = 0;
};