//ボックスコライダークラス
#pragma once
#include<simplemath.h>
#include"ICollider.h"

class BoxCollider : public ICollider
{
private:
	DirectX::SimpleMath::Vector3 m_center; //BOXの中心点
	DirectX::SimpleMath::Vector3 m_radius; //幅の半分の範囲

public:
	DirectX::SimpleMath::Vector3 GetCenter();
	DirectX::SimpleMath::Vector3 GetRadius();
	void SetCenter(DirectX::SimpleMath::Vector3 center);
	void SetRadius(DirectX::SimpleMath::Vector3 radius);
};

inline DirectX::SimpleMath::Vector3 BoxCollider::GetCenter()
{
	return this->m_center;
}

inline DirectX::SimpleMath::Vector3 BoxCollider::GetRadius()
{
	return this->m_radius;
}

inline void BoxCollider::SetCenter(DirectX::SimpleMath::Vector3 center)
{
	this->m_center = center;
}
inline void BoxCollider::SetRadius(DirectX::SimpleMath::Vector3 radius)
{
	this->m_radius = radius;
}