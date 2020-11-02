#include"pch.h"
#include"ERunning.h"
#include"EStanding.h"
#include"EFall.h"

//�ϐ��̏�����
std::unique_ptr<EIState> ERunning::m_instance = nullptr;
//�萔�̐錾
const float ERunning::MOVE_SPEED = 0.08f;

ERunning::ERunning()
	: m_moveSpeed(this->MOVE_SPEED)
{
	
}

//���N���X�̃C���X�^���X�𐶐����擾����
EIState* ERunning::Get()
{
	if (m_instance == nullptr)
	{
		m_instance.reset(new ERunning());
	}
	return m_instance.get();
}

//������
void ERunning::Initialize(Enemy* enemy)
{
	this->m_enemy = enemy;
}

//�X�V
void ERunning::Update(float elapsedTime)
{
	elapsedTime;
	//Search�ł݂����I�u�W�F�N�g�̕����ւ̃x�N�g�����쐬
	this->m_enemy->SetVel(DirectX::SimpleMath::Vector3(cos(this->m_enemy->GetAngle()),
		0.0f,
		sin(this->m_enemy->GetAngle()))
		* this->m_moveSpeed);
	if (this->m_enemy->CollisionWithFruits() == true)
	{
		//�t���[�c���Ƃ��Ă̂Œ�~
		this->m_enemy->SetVel(DirectX::SimpleMath::Vector3::Zero);
		this->m_enemy->ChangeState(EStanding::Get());
	}
	if (this->m_enemy->CollisionWithFloor() == false)
	{
		//�����痎�����̂�Fall��
		this->m_enemy->ChangeState(EFall::Get());
	}
}

