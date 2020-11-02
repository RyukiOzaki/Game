#include"pch.h"
#include"EStanding.h"
#include"ESearch.h"
#include<random>

//�ϐ��̏�����
std::unique_ptr<EIState> EStanding::m_instance = nullptr;

EStanding::EStanding()
	: m_waitTime(-1.0f)
	, m_nowTime(0.0f)
{

}

//���N���X�̃C���X�^���X�𐶐����擾����
EIState* EStanding::Get()
{
	if (m_instance == nullptr)
	{
		m_instance.reset(new EStanding());
	}
	return m_instance.get();
}

//������
void EStanding::Initialize(Enemy* enemy)
{
	this->m_enemy = enemy;
}

//�X�V
void EStanding::Update(float elapsedTime)
{
	elapsedTime;
	if (this->m_enemy->CollisionWithFloor() == true)
	{
		//���ɍs�����n�߂�܂ł̎��Ԃ𗐐��Ō��߂�
		if (this->m_waitTime < 0)
		{
			this->m_waitTime = this->DetectWaitTime();
		}
		else
		{
			this->m_nowTime++;
			if (this->m_nowTime >= this->m_waitTime)
			{
				//state�̕ύX
				this->m_enemy->ChangeState(ESearch::Get());
				//���Ԃ̏�����
				this->m_waitTime = -1.0f;
				this->m_nowTime = 0.0f;
			}
		}
	}
	
}

float EStanding::DetectWaitTime()
{
	//�����_����0-60�̒l��Ԃ�
	std::random_device seed_generator;
	std::mt19937 engine(seed_generator());
	std::uniform_real_distribution<float> result(0.f, 60.f);
	return result(engine);
}