#include"pch.h"
#include"PStanding.h"
#include<Keyboard.h>

//変数の初期化
std::unique_ptr<PIState> PStanding::m_instance = nullptr;

PStanding::PStanding()
{

}

//自クラスのインスタンスを返す
PIState* PStanding::Get()
{
	if (m_instance == nullptr)
	{
		m_instance.reset(new PStanding());
	}
	return m_instance.get();
}

//初期化
void PStanding::Initialize(Player* player)
{
	this->m_player = player;
}

//更新
void PStanding::Update(float elapsedTime)
{
	elapsedTime;
	//上下キー入力で状態をRunningへ
	if ((this->m_player->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Up))
		|| (this->m_player->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Down))
		|| (this->m_player->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Left))
		|| (this->m_player->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Right)))
	{
		this->m_player->ChangeState(PRunning::Get());
	}
}
