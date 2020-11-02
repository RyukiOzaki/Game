//プレイヤーの落下状態クラス
#pragma once
#include"PIState.h"

class PFall : PIState
{
private:
	static std::unique_ptr<PIState> m_instance;
	Player*						    m_player;
	float						    m_moveSpeed;
	static const float FALL_DIS;

private:
	PFall();

public:
	static PIState* Get();

public:
	void Initialize(Player* player)override;
	void Update(float elapsedTime)override;
};