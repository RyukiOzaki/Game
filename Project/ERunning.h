//�G�l�~�[�̈ړ���Ԃ̃N���X
#pragma once
#include"EIState.h"

class ERunning : public EIState
{
private:
	static std::unique_ptr<EIState>				m_instance;
	Enemy*										m_enemy;
	float										m_moveSpeed;

private:
	static const float MOVE_SPEED;

private:
	ERunning();

public:
	static EIState* Get();

public:
	void Initialize(Enemy* enemy)override;
	void Update(float elapsedTime)override;
};