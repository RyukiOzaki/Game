//スコアクラス
#pragma once

class Score
{
private:
	int m_score;

public:
	int  GetScore();
	void AddScore(int score);

public:
	Score();
	~Score() = default;
};
 
inline int Score::GetScore()
{
	return this->m_score;
}