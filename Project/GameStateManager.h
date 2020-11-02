//ゲームステートマネージャークラス
#pragma once
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <simplemath.h>
#include "StepTimer.h"

class IState;


class GameStateManager 
{
	private:
		using GameStatePtr         = std::unique_ptr<IState>;
		using GameStateFactory     = std::function<GameStatePtr()>;
		using GameStateFactoryList = std::unordered_map<std::string, GameStateFactory>;

	private:
		GameStateFactoryList m_stateFactories;
		GameStatePtr         m_activeState;
		std::string          m_nextStateName;

	private:
		template<typename State>
		static GameStatePtr CreateState();

	public:
		GameStateManager();
		~GameStateManager();

	public:
		template<typename State>
		void RegisterState(const std::string& stateName);
		void SetStartState(const std::string& stateName);
		void Update(float elapsedTime);
		void Render(const DirectX::SimpleMath::Matrix& proj);
		void RequestState(const std::string& stateName);
		void Finalize();

	private:
		void ChangeState();
};

template<typename State>
GameStateManager::GameStatePtr GameStateManager::CreateState()
{
	return std::make_unique<State>();
}

template<typename State>
void GameStateManager::RegisterState(const std::string& stateName)
{
	this->m_stateFactories.insert(std::make_pair(stateName, CreateState<State>));
}
