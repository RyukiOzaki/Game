//プレイステートクラス
#pragma once
#include"IState.h"
#include"FollowCamera.h"
#include"NumDrawer.h"
#include"ScoreDrawer.h"
#include"SpriteDrawer.h"
#include"Batch.h"
#include<Keyboard.h>

class Game;

class PlayState : public IState
{
private:
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>        m_tracker;
	std::unique_ptr<FollowCamera>									m_followCamera;
	std::unique_ptr<NumDrawer>										m_timeDrawer;
	std::unique_ptr<ScoreDrawer>									m_scoreDrawer;
	std::unique_ptr<Batch>											m_timerDrawer;
	std::unique_ptr<Batch>											m_pAnimalDrawer;
	std::unique_ptr<Batch>											m_eAnimalDrawer;
	std::unique_ptr<Batch>											m_pAppleDrawer;
	std::unique_ptr<Batch>											m_eAppleDrawer;
	//試合時間
	int																m_gameCount;
	static const int												MAX_GAME_COUNT;
	static const DirectX::SimpleMath::Vector3						TIME_POS;
	//UI
	static const DirectX::SimpleMath::Vector3						TIMER_POS;
	static const DirectX::SimpleMath::Vector3						P_ANIMAL_POS;
	static const DirectX::SimpleMath::Vector3						E_ANIMAL_POS;
	static const DirectX::SimpleMath::Vector3						P_APPLE_POS;
	static const DirectX::SimpleMath::Vector3						E_APPLE_POS;
	static const float												TIMER_SIZE;
	static const float												ANIMAL_SIZE;
	static const float												APPLE_SIZE;
	static const int												SOUND_NUM;

public:
	PlayState();
	~PlayState();

public:
	void Initialize() override;
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& proj) override;
	void Finalize() override;

public:
	void WinJudgment();
	void UIRender();
	void ResetUI();
	void InitializeUI();
};