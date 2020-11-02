#include"pch.h"
#include"Fruits.h"
#include"FruitsGenerator.h"
#include"GameObjectManager.h"
#include"GameContext.h"

//�萔�̏�����
const float FruitsGenerator::INTERVAL = 0.7f;

//������
void FruitsGenerator::Initialize()
{
	this->m_interval = this->INTERVAL;
}

//�X�V
void FruitsGenerator::Update(float elapsedTime)
{
	this->m_elapsedTime += elapsedTime;
	if (this->m_elapsedTime > this->m_interval)
	{
		//TODO ���̐���������Ȃ炱����if��
		this->Generate();
		elapsedTime = 0.0f;
		this->m_elapsedTime = 0.0f;
	}
}

//�`��
void FruitsGenerator::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	view; proj;
}

//�쐬
void FruitsGenerator::Generate()
{
	std::unique_ptr<Fruits> fruits = std::make_unique<Fruits>();
	GameContext::Get<GameObjectManager>()->Add(std::move(fruits));
}