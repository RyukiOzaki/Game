//スフィアーコライダークラス
#pragma once
#include<simplemath.h>
#include"ICollider.h"

class SphereCollider : public ICollider
{
private:
	DirectX::SimpleMath::Vector3 m_center; //球の中心点
	float						 m_radius; //幅の半分の範囲

public:
	DirectX::SimpleMath::Vector3 GetCenter();
	float GetRadius();
	void SetCenter(DirectX::SimpleMath::Vector3 center);
	void SetRadius(float radius);
};

inline DirectX::SimpleMath::Vector3 SphereCollider::GetCenter()
{
	return this->m_center;
}

inline float SphereCollider::GetRadius()
{
	return this->m_radius;
}

inline void SphereCollider::SetCenter(DirectX::SimpleMath::Vector3 center)
{
	this->m_center = center;
}
inline void SphereCollider::SetRadius(float radius)
{
	this->m_radius = radius;
}