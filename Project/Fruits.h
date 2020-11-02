//フルーツクラス
#pragma once
#include"GameObject.h"
#include"BoxCollider.h"
#include<GeometricPrimitive.h>

class Fruits : public GameObject
{
private:
	std::unique_ptr<DirectX::GeometricPrimitive>					m_geometricPrimitive;
	float															m_moveSpeed;
	BoxCollider*													m_boxCollider;
	static const float												GRAVITY;
	static const float												FALL_DIS;
	static const float												START_POS_Y;
	static const float												MAX_RAND_POS;
	static const float												MIN_RAND_POS;
	static const DirectX::SimpleMath::Vector3						COLLIDER_SIZE;

public:
	Fruits();
	~Fruits();

public:
	void Initialize()override;
	void Update(float elapsedTime)override;
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)override;
	void OnCollision();

public:
	BoxCollider* GetBoxCollider();
};

inline BoxCollider* Fruits::GetBoxCollider()
{
	return this->m_boxCollider;
}