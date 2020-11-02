#include"pch.h"
#include"ScoreDrawer.h"
#include"GameContext.h"
#include"ScoreManager.h"

//’è”‚Ì‰Šú‰»
const DirectX::SimpleMath::Vector3 ScoreDrawer::PLAYER_SCORE_POS =
							DirectX::SimpleMath::Vector3(150.0f,75.0f,0.0f);
const DirectX::SimpleMath::Vector3 ScoreDrawer::ENEMY_SCORE_POS = 
							DirectX::SimpleMath::Vector3(150.0f, 150.0f, 0.0f);

ScoreDrawer::ScoreDrawer()
{
	this->m_playerScore = std::make_unique<NumDrawer>(this->PLAYER_SCORE_POS);
	this->m_playerScore->SetNowNum(0);
	this->m_enemyScore  = std::make_unique<NumDrawer>(this->ENEMY_SCORE_POS);
	this->m_enemyScore->SetNowNum(0);
}

//XV
void ScoreDrawer::Update()
{
	this->m_playerScore->SetNowNum(GameContext::Get<ScoreManager>()->GetPlayerScore());
	this->m_enemyScore->SetNowNum(GameContext::Get<ScoreManager>()->GetEnemyScore());
	this->m_playerScore->Update();
	this->m_enemyScore->Update();
}

//•`‰æ
void ScoreDrawer::Render()
{
	this->m_playerScore->Render();
	this->m_enemyScore->Render();
}
