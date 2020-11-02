#include"pch.h"
#include"PRunning.h"
#include<Keyboard.h>

//変数の初期化
std::unique_ptr<PIState> PRunning::m_instance = nullptr;

PRunning::PRunning()
{

}

//自クラスのインスタンスを返す
PIState* PRunning::Get()
{
	if (m_instance == nullptr)
	{
		m_instance.reset(new PRunning());
	}
	return m_instance.get();
}

//初期化
void PRunning::Initialize(Player* player)
{
	this->m_player = player;
	this->m_moveSpeed = 0.1f;
}

//更新
void PRunning::Update(float elapsedTime)
{
	elapsedTime;
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	
	////向いている方向に合わせて移動速度を決定する
	this->m_player->SetVel(DirectX::SimpleMath::Vector3(cos(DirectX::XMConvertToRadians(this->m_player->GetRotation().y + 90.0f)),
		0,
		-sin(DirectX::XMConvertToRadians(this->m_player->GetRotation().y + 90.0f))) * this->m_moveSpeed);
	//移動
	if (key.IsKeyDown(DirectX::Keyboard::Right))
	{
		this->m_player->SetPos(this->m_player->GetPos() + this->m_player->GetVel());
	}
	if (key.IsKeyDown(DirectX::Keyboard::Left))
	{
		this->m_player->SetPos(this->m_player->GetPos() + this->m_player->GetVel());
	}
	if (key.IsKeyDown(DirectX::Keyboard::Up))
	{
		this->m_player->SetPos(this->m_player->GetPos() + this->m_player->GetVel());
	}
	if (key.IsKeyDown(DirectX::Keyboard::Down))
	{
		this->m_player->SetPos(this->m_player->GetPos() + this->m_player->GetVel());
	}
	
	//上下左右キー解放で状態をStandingへ
	if ((this->m_player->GetKeyboardStateTracker()->IsKeyReleased(DirectX::Keyboard::Keys::Up))
		|| (this->m_player->GetKeyboardStateTracker()->IsKeyReleased(DirectX::Keyboard::Keys::Down))
		|| (this->m_player->GetKeyboardStateTracker()->IsKeyReleased(DirectX::Keyboard::Keys::Left))
		|| (this->m_player->GetKeyboardStateTracker()->IsKeyReleased(DirectX::Keyboard::Keys::Right)))
	{
		this->m_player->SetVel(DirectX::SimpleMath::Vector3::Zero);
		this->m_player->ChangeState(PStanding::Get());
	}
}

