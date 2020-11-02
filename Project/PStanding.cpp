#include"pch.h"
#include"PStanding.h"
#include<Keyboard.h>

//�ϐ��̏�����
std::unique_ptr<PIState> PStanding::m_instance = nullptr;

PStanding::PStanding()
{

}

//���N���X�̃C���X�^���X��Ԃ�
PIState* PStanding::Get()
{
	if (m_instance == nullptr)
	{
		m_instance.reset(new PStanding());
	}
	return m_instance.get();
}

//������
void PStanding::Initialize(Player* player)
{
	this->m_player = player;
}

//�X�V
void PStanding::Update(float elapsedTime)
{
	elapsedTime;
	//�㉺�L�[���͂ŏ�Ԃ�Running��
	if ((this->m_player->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Up))
		|| (this->m_player->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Down))
		|| (this->m_player->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Left))
		|| (this->m_player->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Right)))
	{
		this->m_player->ChangeState(PRunning::Get());
	}
}
