#include"pch.h"
#include"PFall.h"
#include"PRunning.h"
#include"PStanding.h"
#include<Keyboard.h>

//変数の初期化
std::unique_ptr<PIState> PFall::m_instance = nullptr;
//定数の初期化
const float PFall::FALL_DIS = -5.0f;

PFall::PFall()
{

}

//自クラスのインスタンスを返す
PIState* PFall::Get()
{
	if (m_instance == nullptr)
	{
		m_instance.reset(new PFall());
	}
	return m_instance.get();
}

//初期化
void PFall::Initialize(Player* player)
{
	this->m_player = player;
}

//更新
void PFall::Update(float elapsedTime)
{
	elapsedTime;
	//落下しきったらStandingへ
	if (this->m_player->GetPos().y < this->FALL_DIS)
	{
		this->m_player->SetPos(this->m_player->GetStartPos());
		this->m_player->ChangeState(PStanding::Get());
	}
}