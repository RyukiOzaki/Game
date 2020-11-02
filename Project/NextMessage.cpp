#include"pch.h"
#include"NextMessage.h"

//’è”‚Ì‰Šú‰»
const int NextMessage::BLANK_TIME = 20;

NextMessage::NextMessage(std::string tagName, DirectX::SimpleMath::Vector3 cameraPos, DirectX::SimpleMath::Vector3 up, DirectX::SimpleMath::Vector3 pos, float scale)
	: m_time(0)
	, m_isIndicate(1)
{
	this->m_nextMessage = std::make_unique<SpriteDrawer>(scale);
	this->m_nextMessage->Initialize(tagName, pos);
	this->m_nextMessage->SetBillBoard(cameraPos, up);
}

//XV
void NextMessage::Update()
{
	this->m_time++;
	if (this->m_time % this->BLANK_TIME == 0)
	{
		this->m_isIndicate *= (-1);
	}
}

//•`‰æ
void NextMessage::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	if (this->m_isIndicate == 1)
	{
		this->m_nextMessage->Render(view, proj);
	}
}