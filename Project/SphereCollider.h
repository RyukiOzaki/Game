//�X�t�B�A�[�R���C�_�[�N���X
#pragma once
#include<simplemath.h>
#include"ICollider.h"

class SphereCollider : public ICollider
{
private:
	DirectX::SimpleMath::Vector3 m_center; //���̒��S�_
	float						 m_radius; //���̔����͈̔�

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