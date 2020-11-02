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

//更新
void GameObjectManager::Update(float elapsedTime)
{
	DestroyObjects();
	if (!this->m_subList.empty())
	{
		AcceptObjects();
	}
	UpdateObjects(elapsedTime);
}

//描画
void GameObjectManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	for (GameObjectPtr& object : this->m_mainList)
	{
		object->Render(view, proj);
	}
}

//オブジェクトを追加
void GameObjectManager::Add(GameObjectPtr&& object)
{
	object->Initialize();
	this->m_subList.push_back(std::move(object));
}

//オブジェクトの更新
void GameObjectManager::UpdateObjects(float elapsedTime)
{
	for (GameObjectPtr& object : this->m_mainList)
	{
		object->Update(elapsedTime);
	}
}

//要素の移動
void GameObjectManager::AcceptObjects()
{
	//subList要素をmainListに移動
	this->m_mainList.splice(this->m_mainList.end(), this->m_subList);
}

//オブジェクトを破棄
void GameObjectManager::DestroyObjects()
{
	//条件一致する全ての要素を削除
	this->m_mainList.remove_if(std::mem_fn(&GameObject::IsInvalid));
}

//指定されたオブジェクトを見つける
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

//全てのオブジェクトの破棄
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
