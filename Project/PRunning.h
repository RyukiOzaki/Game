//プレイヤーの走りクラス
#pragma once
#include"PIState.h"
#include"PStanding.h"


class PRunning : PIState
{
private:
	static std::unique_ptr<PIState> m_instance;
	Player*						   m_player;
	float						   m_moveSpeed;

private:
	PRunning();

public:
	static PIState* Get();

public:
	void Initialize(Player* player)override;
	void Update(float elapsedTime)override;
};