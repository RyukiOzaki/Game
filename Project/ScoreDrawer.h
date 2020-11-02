//スコア表示クラス
#pragma once
#include"NumDrawer.h"
#include<memory>
#include<simplemath.h>

class ScoreDrawer
{
private:
	std::unique_ptr<NumDrawer> m_playerScore;
	std::unique_ptr<NumDrawer> m_enemyScore;

private:
	static const DirectX::SimpleMath::Vector3 PLAYER_SCORE_POS;
	static const DirectX::SimpleMath::Vector3 ENEMY_SCORE_POS;

public:
	ScoreDrawer();
	~ScoreDrawer() = default;

public:
	void Update();
	void Render();
};