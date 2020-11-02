#include"pch.h"
#include"NumDrawer.h"

//’è”‚Ì‰Šú‰»
const int NumDrawer::SIZE          = 24;
const float NumDrawer::FIRST_SCALE = 1.0f;

NumDrawer::NumDrawer(DirectX::SimpleMath::Vector3 pos, float scale)
	: m_nowNum(0)
	, m_scale(scale)
{
	for (int i = 0; i < this->DIGIT_NUM; i++)
	{
		this->m_startPos[i] = 0;
		this->m_endPos[i] = 0;
		this->m_nums[i] = std::make_unique<Batch>("Number");
		this->m_nums[i]->SetPos(DirectX::SimpleMath::Vector3(pos.x - (this->SIZE * this->m_scale) * i, pos.y, pos.z));
	}
}

//XV
void NumDrawer::Update()
{
	int digit = 1;
	for (int i = 0; i < this->DIGIT_NUM; i++)
	{
		this->m_startPos[i] = this->CalculateDigit(static_cast<int>(this->m_nowNum), digit) * this->SIZE;
		this->m_endPos[i] = this->m_startPos[i] + this->SIZE;
		digit *= 10;
	}
}

//•`‰æ
void NumDrawer::Render()
{
	for (int i = 0; i < this->DIGIT_NUM; i++)
	{
		RECT srcRect = { this->m_startPos[i],0,this->m_endPos[i],this->SIZE  };
		this->m_nums[i]->Render(&srcRect, this->m_scale);
	}
}

//w’è‚µ‚½Œ…‚ÌêŠ‚Ì”š‚ğ‹‚ß‚é
int NumDrawer::CalculateDigit(int num, int digit)
{
	int division = num / digit;
	return division % 10;
}