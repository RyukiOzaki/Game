//エネミーの探知状態のクラス
#pragma once
#include"EIState.h"

class ESearch : public EIState
{
private:
	static std::unique_ptr<EIState> m_instance;
	Enemy* m_enemy;
	float m_startCount;
	static const float SEARCH_TIME;

private:
	ESearch();

public:
	static EIState* Get();
	//ラジアンを求める
	float CalculateRadian(DirectX::SimpleMath::Vector3 pos1, DirectX::SimpleMath::Vector3 pos2);

public:
	void Initialize(Enemy* enemy)override;
	void Update(float elapsedTime)override;
};