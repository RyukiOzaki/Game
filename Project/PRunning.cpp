#include"pch.h"
#include"PRunning.h"
#include<Keyboard.h>

//�ϐ��̏�����
std::unique_ptr<PIState> PRunning::m_instance = nullptr;

PRunning::PRunning()
{

}

//���N���X�̃C���X�^���X��Ԃ�
PIState* PRunning::Get()
{
	if (m_instance == nullptr)
	{
		m_instance.reset(new PRunning());
	}
	return m_instance.get();
}

//������
void PRunning::Initialize(Player* player)
{
	this->m_player = player;
	this->m_moveSpeed = 0.1f;
}

//�X�V
void PRunning::Update(float elapsedTime)
{
	elapsedTime;
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();
	
	////�����Ă�������ɍ��킹�Ĉړ����x�����肷��
	this->m_player->SetVel(DirectX::SimpleMath::Vector3(cos(DirectX::XMConvertToRadians(this->m_player->GetRotation().y + 90.0f)),
		0,
		-sin(DirectX::XMConvertToRadians(this->m_player->GetRotation().y + 90.0f))) * this->m_moveSpeed);
	//�ړ�
	if (key.IsKeyDown(DirectX::Keyboard::Right))
	{
		this->m_player->SetPos(this->m_player->GetPos() + this->m_player->GetVel());
	}
	if (key.IsKeyDown(DirectX::Keyboard::Left))
	{
		this->m_player->SetPos(this->m_player->GetPos() + this->m_player->GetVel());
	}
	if (key.IsKeyDown(DirectX::Keyboard::Up))
	{
		this->m_player->SetPos(this->m_player->GetPos() + this->m_player->GetVel());
	}
	if (key.IsKeyDown(DirectX::Keyboard::Down))
	{
		this->m_player->SetPos(this->m_player->GetPos() + this->m_player->GetVel());
	}
	
	//�㉺���E�L�[����ŏ�Ԃ�Standing��
	if ((this->m_player->GetKeyboardStateTracker()->IsKeyReleased(DirectX::Keyboard::Keys::Up))
		|| (this->m_player->GetKeyboardStateTracker()->IsKeyReleased(DirectX::Keyboard::Keys::Down))
		|| (this->m_player->GetKeyboardStateTracker()->IsKeyReleased(DirectX::Keyboard::Keys::Left))
		|| (this->m_player->GetKeyboardStateTracker()->IsKeyReleased(DirectX::Keyboard::Keys::Right)))
	{
		this->m_player->SetVel(DirectX::SimpleMath::Vector3::Zero);
		this->m_player->ChangeState(PStanding::Get());
	}
}

