//フルーツジェネレータークラス
#pragma once
#include"GameObject.h"

class FruitsGenerator : public GameObject
{
private:
	float m_interval;
	float m_elapsedTime;

private:
	static const float INTERVAL;

public:
	void Generate();

public:
	void Initialize()override;
	void Update(float elapsedTime)override;
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)override;
};

