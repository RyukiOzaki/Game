//プレイヤーの立つクラス
#pragma once
#include"PIState.h"
#include"PRunning.h"

class PRunning;

class PStanding : public PIState
{
private:
	static std::unique_ptr<PIState> m_instance;
	Player*						    m_player;

private:
	PStanding();

public:
	static PIState* Get();

public:
	void Initialize(Player* player)override;
	void Update(float elapsedTime)override;
};