//エネミーの落下状態のクラス
#pragma once
#include"EIState.h"

class EFall : public EIState
{
private:
	static std::unique_ptr<EIState> m_instance;
	Enemy* m_enemy;
	static const float FALL_DIS;

private:
	EFall();

public:
	static EIState* Get();

public:
	void Initialize(Enemy* enemy)override;
	void Update(float elapsedTime)override;
};