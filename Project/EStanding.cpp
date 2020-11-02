#include"pch.h"
#include"EStanding.h"
#include"ESearch.h"
#include<random>

//変数の初期化
std::unique_ptr<EIState> EStanding::m_instance = nullptr;

EStanding::EStanding()
	: m_waitTime(-1.0f)
	, m_nowTime(0.0f)
{

}

//自クラスのインスタンスを生成し取得する
EIState* EStanding::Get()
{
	if (m_instance == nullptr)
	{
		m_instance.reset(new EStanding());
	}
	return m_instance.get();
}

//初期化
void EStanding::Initialize(Enemy* enemy)
{
	this->m_enemy = enemy;
}

//更新
void EStanding::Update(float elapsedTime)
{
	elapsedTime;
	if (this->m_enemy->CollisionWithFloor() == true)
	{
		//次に行動し始めるまでの時間を乱数で決める
		if (this->m_waitTime < 0)
		{
			this->m_waitTime = this->DetectWaitTime();
		}
		else
		{
			this->m_nowTime++;
			if (this->m_nowTime >= this->m_waitTime)
			{
				//stateの変更
				this->m_enemy->ChangeState(ESearch::Get());
				//時間の初期化
				this->m_waitTime = -1.0f;
				this->m_nowTime = 0.0f;
			}
		}
	}
	
}

float EStanding::DetectWaitTime()
{
	//ランダムで0-60の値を返す
	std::random_device seed_generator;
	std::mt19937 engine(seed_generator());
	std::uniform_real_distribution<float> result(0.f, 60.f);
	return result(engine);
}