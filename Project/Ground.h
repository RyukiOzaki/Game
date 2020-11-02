#pragma once
#include<GeometricPrimitive.h>
#include"GameObject.h"

class Ground : public GameObject
{
private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	static const DirectX::SimpleMath::Vector3    SIZE;

public:
	void Initialize()override;
	void Update(float elapsedTime)override;
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)override;

public:
	Ground();
	~Ground() = default;
};

