//プレイヤーのインターフェースクラス
#pragma once
#include<memory>
#include"StepTimer.h"
#include"Player.h"
#include"DebugFont.h"

class Player;
class PIState
{
public:
	virtual void Initialize(Player* player) = 0;
	virtual void Update(float elapsedTime) = 0;
};