#include"pch.h"
#include"ModelObject.h"
#include"GameContext.h"
#include<Effects.h>

ModelObject::ModelObject()
{
	this->m_deviceResources = GameContext().Get<DX::DeviceResources>();
}

ModelObject::~ModelObject()
{

}

//������
void ModelObject::Initialize()
{
	//�R�����X�e�[�g�̍쐬
	this->m_state = std::make_unique<DirectX::CommonStates>(this->m_deviceResources->GetD3DDevice());
	//�G�t�F�N�g�t�@�N�g���[�̐���
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(this->m_deviceResources->GetD3DDevice());
	//�p�X�̐ݒ�
	factory->SetDirectory(this->m_pathName);
	//���f���f�[�^�̓ǂݍ���
	this->m_model = DirectX::Model::CreateFromCMO(this->m_deviceResources->GetD3DDevice(), this->m_fillName, *factory);
	//�g���I������G�t�F�N�g�t�@�N�g���[�̔j��
	delete factory;
}

//�`��
void ModelObject::Render(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//�`��
	this->m_model->Draw(this->m_deviceResources->GetD3DDeviceContext(), *this->m_state, world, view, proj);
}

