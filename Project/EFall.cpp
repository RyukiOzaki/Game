#include"pch.h"
#include"EFall.h"
#include"EStanding.h"

//�ϐ��̏�����
std::unique_ptr<EIState> EFall::m_instance = nullptr;
//�萔�̏�����
const float EFall::FALL_DIS = -6.0f;

EFall::EFall()
{

}

//���N���X�̃C���X�^���X�𐶐����擾����
EIState* EFall::Get()
{
	if (m_instance == nullptr)
	{
		m_instance.reset(new EFall());
	}
	return m_instance.get();
}

//������
void EFall::Initialize(Enemy* enemy)
{
	this->m_enemy = enemy;
}

//�X�V
void EFall::Update(float elapsedTime)
{
	elapsedTime;
	//���x���d�͂����ɂ���
	this->m_enemy->SetVel(DirectX::SimpleMath::Vector3(0, this->m_enemy->GetVel().y, 0));
	//�Œ�ʒu�܂ŗ�����
	if (this->m_enemy->GetPos().y < this->FALL_DIS)
	{
		//�����ʒu�ֈړ�
		this->m_enemy->SetPos(this->m_enemy->GetStartPos());
		//state�̕ύX
		this->m_enemy->ChangeState(EStanding::Get());
	}
}