#include"pch.h"
#include"Score.h"

Score::Score()
	: m_score(0)
{

}

//�X�R�A�𑝂₷
void Score::AddScore(int score)
{
	this->m_score += score;
}