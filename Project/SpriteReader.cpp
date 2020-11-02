#include"pch.h"
#include"SpriteReader.h"
#include"GameContext.h"
#include"SpriteManager.h"

SpriteReader::SpriteReader()
{
}

SpriteReader::~SpriteReader()
{
}

//�ǂݍ���
void SpriteReader::Reading()
{
	//�^�C�g��
	std::unique_ptr<Sprite> title = std::make_unique<Sprite>(L"Resources/Sprites/title.png","Title");
	GameContext::Get<SpriteManager>()->Add(std::move(title));
	//����
	std::unique_ptr<Sprite> number = std::make_unique<Sprite>(L"Resources/Sprites/Number.png", "Number");
	GameContext::Get<SpriteManager>()->Add(std::move(number));
	//����
	std::unique_ptr<Sprite> animal1 = std::make_unique<Sprite>(L"Resources/Sprites/animal1.jpg", "Animal1");
	GameContext::Get<SpriteManager>()->Add(std::move(animal1));
	std::unique_ptr<Sprite> animal2 = std::make_unique<Sprite>(L"Resources/Sprites/animal2.jpg", "Animal2");
	GameContext::Get<SpriteManager>()->Add(std::move(animal2));
	//�^�C�}�[
	std::unique_ptr<Sprite> timer = std::make_unique<Sprite>(L"Resources/Sprites/timer.jpg", "Timer");
	GameContext::Get<SpriteManager>()->Add(std::move(timer));
	//����
	std::unique_ptr<Sprite> defeat = std::make_unique<Sprite>(L"Resources/Sprites/defeat.png", "Defeat");
	GameContext::Get<SpriteManager>()->Add(std::move(defeat));
	//����
	std::unique_ptr<Sprite> victory = std::make_unique<Sprite>(L"Resources/Sprites/victory.png", "Victory");
	GameContext::Get<SpriteManager>()->Add(std::move(victory));
	//���_
	std::unique_ptr<Sprite> tieGame = std::make_unique<Sprite>(L"Resources/Sprites/tieGame.png", "TieGame");
	GameContext::Get<SpriteManager>()->Add(std::move(tieGame));
	//�ь�
	std::unique_ptr<Sprite> apple = std::make_unique<Sprite>(L"Resources/Sprites/apple.jpg", "Apple");
	GameContext::Get<SpriteManager>()->Add(std::move(apple));
	//�ē�
	std::unique_ptr<Sprite> space = std::make_unique<Sprite>(L"Resources/Sprites/space.png", "Space");
	GameContext::Get<SpriteManager>()->Add(std::move(space));
	std::unique_ptr<Sprite> enter = std::make_unique<Sprite>(L"Resources/Sprites/enter.png", "Enter");
	GameContext::Get<SpriteManager>()->Add(std::move(enter));
}
