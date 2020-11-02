//è∞ÉNÉâÉX
#pragma once
#include<GeometricPrimitive.h>
#include"GameObject.h"
#include"BoxCollider.h"

class Floor : public GameObject
{
private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	static const DirectX::SimpleMath::Vector3    SIZE;
	static const DirectX::SimpleMath::Vector3    COLLIDER_SIZE;
	BoxCollider*								 m_boxCollider;

public:
	void Initialize()override;
	void Update(float elapsedTime)override;
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)override;

public:
	Floor();
	~Floor();

public:
	BoxCollider* GetBoxCollider();
};

inline BoxCollider* Floor::GetBoxCollider()
{
	return this->m_boxCollider;
}

