//エネミーの立つ状態のクラス
#pragma once
#include"EIState.h"

class EStanding : public EIState
{
private:
	static std::unique_ptr<EIState> m_instance;
	Enemy* m_enemy;
	float m_waitTime;
	float m_nowTime;

private:
	EStanding();

public:
	static EIState* Get();

public:
	void Initialize(Enemy* enemy)override;
	void Update(float elapsedTime)override;

private:
	float DetectWaitTime();
};

