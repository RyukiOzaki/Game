#include"pch.h"
#include"Score.h"

Score::Score()
	: m_score(0)
{

}

//スコアを増やす
void Score::AddScore(int score)
{
	this->m_score += score;
}