#include"pch.h"
#include"Fruits.h"
#include"FruitsGenerator.h"
#include"GameObjectManager.h"
#include"GameContext.h"

//定数の初期化
const float FruitsGenerator::INTERVAL = 0.7f;

//初期化
void FruitsGenerator::Initialize()
{
	this->m_interval = this->INTERVAL;
}

//更新
void FruitsGenerator::Update(float elapsedTime)
{
	this->m_elapsedTime += elapsedTime;
	if (this->m_elapsedTime > this->m_interval)
	{
		//TODO 数の制限かけるならここでif文
		this->Generate();
		elapsedTime = 0.0f;
		this->m_elapsedTime = 0.0f;
	}
}

//描画
void FruitsGenerator::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	view; proj;
}

//作成
void FruitsGenerator::Generate()
{
	std::unique_ptr<Fruits> fruits = std::make_unique<Fruits>();
	GameContext::Get<GameObjectManager>()->Add(std::move(fruits));
}