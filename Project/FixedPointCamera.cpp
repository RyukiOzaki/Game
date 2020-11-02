#include"pch.h"
#include"FixedPointCamera.h"

//’è”‚ÌéŒ¾
const DirectX::SimpleMath::Vector3 FixedPointCamera::EYE_POS =
					DirectX::SimpleMath::Vector3(0.f, 3.f, 10.f);

FixedPointCamera::FixedPointCamera(DirectX::SimpleMath::Vector3 targetPos)
	: m_eye(this->EYE_POS)
	, m_targetPos(targetPos)
	, m_up(DirectX::SimpleMath::Vector3(0.f, 1.f, 0.f))
{
	this->m_view = DirectX::SimpleMath::Matrix::CreateLookAt(this->m_eye, this->m_targetPos, this->m_up);
}

