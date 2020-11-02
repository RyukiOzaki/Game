#include "pch.h"
#include "GameObjectManager.h"
#include "GameObject.h"

GameObjectManager::GameObjectManager()
	: m_mainList()
	, m_subList()
{
}

GameObjectManager::~GameObjectManager()
{
}

//�X�V
void GameObjectManager::Update(float elapsedTime)
{
	DestroyObjects();
	if (!this->m_subList.empty())
	{
		AcceptObjects();
	}
	UpdateObjects(elapsedTime);
}

//�`��
void GameObjectManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	for (GameObjectPtr& object : this->m_mainList)
	{
		object->Render(view, proj);
	}
}

//�I�u�W�F�N�g��ǉ�
void GameObjectManager::Add(GameObjectPtr&& object)
{
	object->Initialize();
	this->m_subList.push_back(std::move(object));
}

//�I�u�W�F�N�g�̍X�V
void GameObjectManager::UpdateObjects(float elapsedTime)
{
	for (GameObjectPtr& object : this->m_mainList)
	{
		object->Update(elapsedTime);
	}
}

//�v�f�̈ړ�
void GameObjectManager::AcceptObjects()
{
	//subList�v�f��mainList�Ɉړ�
	this->m_mainList.splice(this->m_mainList.end(), this->m_subList);
}

//�I�u�W�F�N�g��j��
void GameObjectManager::DestroyObjects()
{
	//������v����S�Ă̗v�f���폜
	this->m_mainList.remove_if(std::mem_fn(&GameObject::IsInvalid));
}

//�w�肳�ꂽ�I�u�W�F�N�g��������
std::vector<GameObject*> GameObjectManager::Find(std::string tagName)
{
	std::vector<GameObject*> objects;
	for (std::unique_ptr<GameObject>& obj : this->m_mainList)
	{
		if (obj->GetTagName() == tagName)
		{
			objects.push_back(obj.get());
		}
	}
	return objects;
}

//�S�ẴI�u�W�F�N�g�̔j��
void GameObjectManager::DeleteAll()
{
	for (std::unique_ptr<GameObject>& obj : this->m_mainList)
	{
		if (obj != nullptr)
		{
			obj->Invalidate();
		}
	}
}
