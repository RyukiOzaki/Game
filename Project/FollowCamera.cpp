#include"pch.h"
#include"FollowCamera.h"

//’è”‚ÌéŒ¾
const DirectX::SimpleMath::Vector3 FollowCamera::EYE_POS =
DirectX::SimpleMath::Vector3(0.f, 3.f, 10.f);

FollowCamera::FollowCamera(DirectX::SimpleMath::Vector3 targetPos)
	: m_eye(this->EYE_POS)
	, m_targetPos(targetPos)
	, m_up(DirectX::SimpleMath::Vector3(0.f, 1.f, 0.f))
{
	this->m_view = DirectX::SimpleMath::Matrix::CreateLookAt(this->m_eye, this->m_targetPos, this->m_up);
}

//XV
void FollowCamera::Update(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 targetPos)
{
	this->SetEye(eye);
	this->SetTargetPos(targetPos);
	this->m_view = DirectX::SimpleMath::Matrix::CreateLookAt(this->m_eye, this->m_targetPos, this->m_up);
}