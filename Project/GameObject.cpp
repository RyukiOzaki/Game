#include"pch.h"
#include"GameObject.h"


GameObject::GameObject()
	: m_isValid(true)
	, m_collider(nullptr)
	, m_tagName("GameObject")
	, m_pos(0.0f, 0.0f, 0.0f)
	, m_vel(0.0f, 0.0f, 0.0f)
	, m_rotation(0.0f, 0.0f, 0.0f)
	, m_scale(1.0f, 1.0f, 1.0f)
{
}

GameObject::~GameObject()
{
}

//������
void GameObject::Invalidate()
{
	m_isValid = false;
}

//�ړ��s��̐ݒ�
void GameObject::MatrixToVector()
{
	this->m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(this->m_pos);
}

//������
void GameObject::Destroy(GameObject * object)
{
	object->Invalidate();
}