//スコアを管理するクラス
#pragma once

class ScoreManager
{
private:
	int m_playerScore;
	int m_enemyScore;
public:
	int GetPlayerScore();
	int GetEnemyScore();
	void SetPlayerScore(int score);
	void SetEnemyScore(int score);
};

inline int ScoreManager::GetPlayerScore()
{
	return this->m_playerScore;
}
inline int ScoreManager::GetEnemyScore()
{
	return this->m_enemyScore;
}
inline void ScoreManager::SetPlayerScore(int score)
{
	this->m_playerScore = score;
}
inline void ScoreManager::SetEnemyScore(int score)
{
	this->m_enemyScore = score;
}