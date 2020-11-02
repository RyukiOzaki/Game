//”š•\¦ƒNƒ‰ƒX
#pragma once
#include"Batch.h"
#include<memory>

class NumDrawer
{
public:
	static const int DIGIT_NUM = 2;

private:
	int m_nowNum;
	std::unique_ptr<Batch>	m_nums[DIGIT_NUM];
	static const int		SIZE;
	static const float		FIRST_SCALE;
	int						m_startPos[DIGIT_NUM];
	int						m_endPos[DIGIT_NUM];
	float					m_scale;

public:
	NumDrawer(DirectX::SimpleMath::Vector3 pos, float scale = FIRST_SCALE);
	~NumDrawer() = default;

public:
	void Update();
	void Render();
	int  CalculateDigit(int num, int digit);
	void SetNowNum(int nowNum);
	
};

inline void NumDrawer::SetNowNum(int nowNum)
{
	this->m_nowNum = nowNum;
}

