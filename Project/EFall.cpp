#include"pch.h"
#include"EFall.h"
#include"EStanding.h"

//変数の初期化
std::unique_ptr<EIState> EFall::m_instance = nullptr;
//定数の初期化
const float EFall::FALL_DIS = -6.0f;

EFall::EFall()
{

}

//自クラスのインスタンスを生成し取得する
EIState* EFall::Get()
{
	if (m_instance == nullptr)
	{
		m_instance.reset(new EFall());
	}
	return m_instance.get();
}

//初期化
void EFall::Initialize(Enemy* enemy)
{
	this->m_enemy = enemy;
}

//更新
void EFall::Update(float elapsedTime)
{
	elapsedTime;
	//速度を重力だけにする
	this->m_enemy->SetVel(DirectX::SimpleMath::Vector3(0, this->m_enemy->GetVel().y, 0));
	//最低位置まで来たら
	if (this->m_enemy->GetPos().y < this->FALL_DIS)
	{
		//初期位置へ移動
		this->m_enemy->SetPos(this->m_enemy->GetStartPos());
		//stateの変更
		this->m_enemy->ChangeState(EStanding::Get());
	}
}