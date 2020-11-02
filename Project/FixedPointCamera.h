//ŒÅ’èƒJƒƒ‰ƒNƒ‰ƒX
#pragma once
#include<simplemath.h>

class FixedPointCamera
{
private:
	DirectX::SimpleMath::Vector3 m_targetPos;
	DirectX::SimpleMath::Vector3 m_eye;
	DirectX::SimpleMath::Vector3 m_up;
	DirectX::SimpleMath::Matrix  m_view;

private:
	static const DirectX::SimpleMath::Vector3 EYE_POS;

public:
	FixedPointCamera(DirectX::SimpleMath::Vector3 targetPos = DirectX::SimpleMath::Vector3::Zero);
	~FixedPointCamera() = default;
	
public:
	DirectX::SimpleMath::Matrix GetView();
	DirectX::SimpleMath::Vector3 GetEye();
	DirectX::SimpleMath::Vector3 GetUp();

public:
	void SetEye(DirectX::SimpleMath::Vector3 eye);

};

inline DirectX::SimpleMath::Matrix FixedPointCamera::GetView()
{
	return this->m_view;
}

inline DirectX::SimpleMath::Vector3 FixedPointCamera::GetEye()
{
	return this->m_eye;
}

inline DirectX::SimpleMath::Vector3 FixedPointCamera::GetUp()
{
	return this->m_up;
}

inline void FixedPointCamera::SetEye(DirectX::SimpleMath::Vector3 eye)
{
	this->m_eye = eye;
	this->m_view = DirectX::SimpleMath::Matrix::CreateLookAt(this->m_eye, this->m_targetPos, this->m_up);
}