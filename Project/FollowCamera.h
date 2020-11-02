//’Ç]ƒJƒƒ‰ƒNƒ‰ƒX
#pragma once
#include<simplemath.h>

class FollowCamera
{
private:
	DirectX::SimpleMath::Vector3 m_targetPos;
	DirectX::SimpleMath::Vector3 m_eye;
	DirectX::SimpleMath::Vector3 m_up;
	DirectX::SimpleMath::Matrix  m_view;

public:
	static const DirectX::SimpleMath::Vector3 EYE_POS;

public:
	FollowCamera(DirectX::SimpleMath::Vector3 targetPos = DirectX::SimpleMath::Vector3::Zero);
	~FollowCamera() = default;

public:
	void Update(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 targetPos);

public:
	DirectX::SimpleMath::Matrix GetView();
	DirectX::SimpleMath::Vector3 GetEye();
	DirectX::SimpleMath::Vector3 GetUp();

public:
	void SetEye(DirectX::SimpleMath::Vector3 eye);
	void SetTargetPos(DirectX::SimpleMath::Vector3 targetPos);
};

inline DirectX::SimpleMath::Matrix FollowCamera::GetView()
{
	return this->m_view;
}

inline DirectX::SimpleMath::Vector3 FollowCamera::GetEye()
{
	return this->m_eye;
}

inline DirectX::SimpleMath::Vector3 FollowCamera::GetUp()
{
	return this->m_up;
}

inline void FollowCamera::SetEye(DirectX::SimpleMath::Vector3 eye)
{
	this->m_eye = eye;
	this->m_view = DirectX::SimpleMath::Matrix::CreateLookAt(this->m_eye, this->m_targetPos, this->m_up);
}

inline void FollowCamera::SetTargetPos(DirectX::SimpleMath::Vector3 targetPos)
{
	this->m_targetPos = targetPos;
}