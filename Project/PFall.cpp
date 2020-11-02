#include"pch.h"
#include"PFall.h"
#include"PRunning.h"
#include"PStanding.h"
#include<Keyboard.h>

//�ϐ��̏�����
std::unique_ptr<PIState> PFall::m_instance = nullptr;
//�萔�̏�����
const float PFall::FALL_DIS = -5.0f;

PFall::PFall()
{

}

//���N���X�̃C���X�^���X��Ԃ�
PIState* PFall::Get()
{
	if (m_instance == nullptr)
	{
		m_instance.reset(new PFall());
	}
	return m_instance.get();
}

//������
void PFall::Initialize(Player* player)
{
	this->m_player = player;
}

//�X�V
void PFall::Update(float elapsedTime)
{
	elapsedTime;
	//��������������Standing��
	if (this->m_player->GetPos().y < this->FALL_DIS)
	{
		this->m_player->SetPos(this->m_player->GetStartPos());
		this->m_player->ChangeState(PStanding::Get());
	}
}