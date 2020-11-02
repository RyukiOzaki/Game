#include"pch.h"
#include"ERunning.h"
#include"EStanding.h"
#include"EFall.h"

//変数の初期化
std::unique_ptr<EIState> ERunning::m_instance = nullptr;
//定数の宣言
const float ERunning::MOVE_SPEED = 0.08f;

ERunning::ERunning()
	: m_moveSpeed(this->MOVE_SPEED)
{
	
}

//自クラスのインスタンスを生成し取得する
EIState* ERunning::Get()
{
	if (m_instance == nullptr)
	{
		m_instance.reset(new ERunning());
	}
	return m_instance.get();
}

//初期化
void ERunning::Initialize(Enemy* enemy)
{
	this->m_enemy = enemy;
}

//更新
void ERunning::Update(float elapsedTime)
{
	elapsedTime;
	//Searchでみつけたオブジェクトの方向へのベクトルを作成
	this->m_enemy->SetVel(DirectX::SimpleMath::Vector3(cos(this->m_enemy->GetAngle()),
		0.0f,
		sin(this->m_enemy->GetAngle()))
		* this->m_moveSpeed);
	if (this->m_enemy->CollisionWithFruits() == true)
	{
		//フルーツをとってので停止
		this->m_enemy->SetVel(DirectX::SimpleMath::Vector3::Zero);
		this->m_enemy->ChangeState(EStanding::Get());
	}
	if (this->m_enemy->CollisionWithFloor() == false)
	{
		//床から落ちたのでFallへ
		this->m_enemy->ChangeState(EFall::Get());
	}
}

