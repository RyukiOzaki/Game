//•‰‚¯ƒNƒ‰ƒX
#pragma once
#include"IState.h"
#include"FixedPointCamera.h"
#include"Batch.h"
#include"NumDrawer.h"
#include"NextMessage.h"
#include<Keyboard.h>

class DefeatState : public IState
{
private:
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>        m_tracker;
	std::unique_ptr<FixedPointCamera>								m_camera;
	std::unique_ptr<Batch>											m_victory;
	std::unique_ptr<Batch>											m_apple;
	std::unique_ptr<Batch>											m_animal;
	std::unique_ptr<NumDrawer>										m_score;
	std::unique_ptr<NextMessage>									m_nextMessage;

private:
	static const DirectX::SimpleMath::Vector3						APPLE_POS;
	static const DirectX::SimpleMath::Vector3						ANIMAL_POS;
	static const DirectX::SimpleMath::Vector3						SCORE_POS;
	static const DirectX::SimpleMath::Vector3						MESSAGE_POS;
	static const float												SCORE_SIZE;
	static const float												ANIMAL_SIZE;
	static const float												APPLE_SIZE;

public:
	DefeatState();

public:
	~DefeatState();

public:
	void Initialize() override;
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& proj) override;
	void Finalize() override;
};