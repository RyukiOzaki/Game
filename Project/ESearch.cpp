#include"pch.h"
#include"ESearch.h"
#include"ERunning.h"
#include"GameObjectManager.h"
#include"GameContext.h"

//�ϐ��̏�����
std::unique_ptr<EIState> ESearch::m_instance = nullptr;
//�萔�̐錾
const float ESearch::SEARCH_TIME = 1.5f;

ESearch::ESearch()
	: m_startCount(0)
{

}

//���N���X�̃C���X�^���X�𐶐����擾����
EIState* ESearch::Get()
{
	if (m_instance == nullptr)
	{
		m_instance.reset(new ESearch());
	}
	return m_instance.get();
}

//������
void ESearch::Initialize(Enemy* enemy)
{
	this->m_enemy = enemy;
}

//�X�V
void ESearch::Update(float elapsedTime)
{
	this->m_startCount += elapsedTime;
	//SEARCH_TIME�b�������̂Ȃ�T�����n�߂�
	if (this->m_startCount >= this->SEARCH_TIME)
	{
		std::vector<GameObject*> target = GameContext::Get<GameObjectManager>()->Find("Fruits");
		for (std::vector<GameObject*>::iterator iter = target.begin(); iter != target.end(); iter++)
		{
			if ((*iter)->IsValid())
			{
				//��ԍŏ��ɂ݂����^�[�Q�b�g�ւ̌������擾
				float angle = this->CalculateRadian(this->m_enemy->GetPos(), (*iter)->GetPos());
				this->m_enemy->SetAngle(angle);
				//state�̕ύX
				this->m_enemy->ChangeState(ERunning::Get());
				break;
			}
		}
	}
}

//���W�A���p���v�Z����
float ESearch::CalculateRadian(DirectX::SimpleMath::Vector3 pos1, DirectX::SimpleMath::Vector3 pos2)
{
	return (atan2(pos2.z - pos1.z, pos2.x - pos1.x));
}