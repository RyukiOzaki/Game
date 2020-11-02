#include"pch.h"
#include"Ground.h"
#include"GameContext.h"

//�萔�̏�����
const DirectX::SimpleMath::Vector3 Ground::SIZE = DirectX::SimpleMath::Vector3(25.0f, 1.0f, 14.0f);

Ground::Ground()
{
	this->m_tagName = "Ground";
}

//������
void Ground::Initialize()
{
	//pos�̐ݒ�
	this->m_pos = DirectX::SimpleMath::Vector3::Zero;
	//�R���e�L�X�g�̍쐬
	this->m_deviceResources = GameContext::Get<DX::DeviceResources>();
	//�W�I���g���b�N�v���~�e�B�u�̍쐬
	this->m_geometricPrimitive = DirectX::GeometricPrimitive::CreateBox(this->m_deviceResources->GetD3DDeviceContext(), this->SIZE);
}

//�X�V
void Ground::Update(float elapsedTime)
{
	elapsedTime;
}

//�`��
void Ground::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	this->m_world = DirectX::SimpleMath::Matrix::Identity;
	this->MatrixToVector();
	this->m_geometricPrimitive->Draw(this->m_world, view, proj, DirectX::Colors::White);
}


