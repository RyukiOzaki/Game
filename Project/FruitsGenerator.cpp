#include"pch.h"
#include"Fruits.h"
#include"FruitsGenerator.h"
#include"GameObjectManager.h"
#include"GameContext.h"

//’è”‚Ì‰Šú‰»
const float FruitsGenerator::INTERVAL = 0.7f;

//‰Šú‰»
void FruitsGenerator::Initialize()
{
	this->m_interval = this->INTERVAL;
}

//XV
void FruitsGenerator::Update(float elapsedTime)
{
	this->m_elapsedTime += elapsedTime;
	if (this->m_elapsedTime > this->m_interval)
	{
		//TODO ”‚Ì§ŒÀ‚©‚¯‚é‚È‚ç‚±‚±‚Åif•¶
		this->Generate();
		elapsedTime = 0.0f;
		this->m_elapsedTime = 0.0f;
	}
}

//•`‰æ
void FruitsGenerator::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	view; proj;
}

//ì¬
void FruitsGenerator::Generate()
{
	std::unique_ptr<Fruits> fruits = std::make_unique<Fruits>();
	GameContext::Get<GameObjectManager>()->Add(std::move(fruits));
}