#include"pch.h"
#include"ESearch.h"
#include"ERunning.h"
#include"GameObjectManager.h"
#include"GameContext.h"

//変数の初期化
std::unique_ptr<EIState> ESearch::m_instance = nullptr;
//定数の宣言
const float ESearch::SEARCH_TIME = 1.5f;

ESearch::ESearch()
	: m_startCount(0)
{

}

//自クラスのインスタンスを生成し取得する
EIState* ESearch::Get()
{
	if (m_instance == nullptr)
	{
		m_instance.reset(new ESearch());
	}
	return m_instance.get();
}

//初期化
void ESearch::Initialize(Enemy* enemy)
{
	this->m_enemy = enemy;
}

//更新
void ESearch::Update(float elapsedTime)
{
	this->m_startCount += elapsedTime;
	//SEARCH_TIME秒たったのなら探索し始める
	if (this->m_startCount >= this->SEARCH_TIME)
	{
		std::vector<GameObject*> target = GameContext::Get<GameObjectManager>()->Find("Fruits");
		for (std::vector<GameObject*>::iterator iter = target.begin(); iter != target.end(); iter++)
		{
			if ((*iter)->IsValid())
			{
				//一番最初にみつけたターゲットへの向きを取得
				float angle = this->CalculateRadian(this->m_enemy->GetPos(), (*iter)->GetPos());
				this->m_enemy->SetAngle(angle);
				//stateの変更
				this->m_enemy->ChangeState(ERunning::Get());
				break;
			}
		}
	}
}

//ラジアン角を計算する
float ESearch::CalculateRadian(DirectX::SimpleMath::Vector3 pos1, DirectX::SimpleMath::Vector3 pos2)
{
	return (atan2(pos2.z - pos1.z, pos2.x - pos1.x));
}