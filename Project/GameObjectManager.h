//ゲームオブジェクトマネージャークラス
#pragma once
#include<list>
#include<memory>
#include<SimpleMath.h>
#include<vector>
#include"StepTimer.h"
class GameObject;

class GameObjectManager final
{
	using GameObjectPtr  = std::unique_ptr<GameObject>;
	using GameObjectList = std::list<GameObjectPtr>;

	private:
		GameObjectList m_mainList;
		GameObjectList m_subList;

	public:
		GameObjectManager();

	public:
		~GameObjectManager();

	public:
		void Update(float elapsedTime);
		void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
		void Add(GameObjectPtr&& object);
		std::vector<GameObject*> Find(std::string tagName);
		void DeleteAll();

	private:
		void UpdateObjects(float elapsedTime);
		void AcceptObjects();
		void DestroyObjects();
};
