#include"pch.h"
#include"GameStateManager.h"
#include"IState.h"
#include<cassert>

GameStateManager::GameStateManager()
	: m_stateFactories()
	, m_activeState(nullptr)
	, m_nextStateName()
{
}

GameStateManager::~GameStateManager()
{
}

//開始ステートを設定
void GameStateManager::SetStartState(const std::string& stateName)
{
	RequestState(stateName);
}

//更新
void GameStateManager::Update(float elapsedTime)
{
	//次のステートへのリクエストがあるならば次のステートへ
	if (!this->m_nextStateName.empty())
	{
		ChangeState();
	}
	assert(this->m_activeState && "There is no active state.");
	this->m_activeState->Update(elapsedTime);
}

//描画
void GameStateManager::Render(const DirectX::SimpleMath::Matrix& proj)
{
	assert(this->m_activeState && "There is no active state.");
	this->m_activeState->Render(proj);
}

//ステートの変更要請
void GameStateManager::RequestState(const std::string& stateName)
{
	assert(this->m_stateFactories.count(stateName) == 1 && "A GameState with this name is not registered.");

	this->m_nextStateName = stateName;
}

//ステートの変更
void GameStateManager::ChangeState()
{
	if (this->m_activeState)
	{
		//終了処理
		this->m_activeState->Finalize();
	}
	//次のステートに変更
	this->m_activeState = this->m_stateFactories[this->m_nextStateName]();
	//変更したステートの初期化
	this->m_activeState->Initialize();	
	//保存していたステートのリセット
	this->m_nextStateName.clear();
}

//終了処理
void GameStateManager::Finalize()
{
	this->m_activeState->Finalize();
}